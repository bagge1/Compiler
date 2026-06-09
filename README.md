# C+- IR Back-End & Bytecode Interpreter

This document covers the **back half** of the C+- compiler: the **Intermediate Representation
(IR)** that lowers the Abstract Syntax Tree (AST) into three-address code (TAC) / a control-flow
graph (CFG) and finally into a portable **bytecode text file**, plus the standalone **stack-based
bytecode interpreter** that executes that file.

It is built as a *reference guide for a live code defense*. Sections 1–2 give you the "story" to
tell; Section 3 is an exhaustive per-function lookup table; Section 4 pre-loads the hard questions.

> Scope note: This README documents only [interpreter.cc](interpreter.cc),
> [interpreter.hh](interpreter.hh), [ir.cc](ir.cc), and [ir.hh](ir.hh). The lexer, parser, symbol
> table, and semantic analyzer are the *front end* and are out of scope here.

---

## Table of Contents

1. [Architecture & High-Level Design](#1-architecture--high-level-design)
2. [Component Breakdown (IR & Interpreter)](#2-component-breakdown-ir--interpreter)
3. [Comprehensive Function Dictionary](#3-comprehensive-function-dictionary)
4. [Anticipated Presentation Questions](#4-anticipated-presentation-questions)
5. [Appendix: Bytecode Format & Opcode Reference](#appendix-bytecode-format--opcode-reference)

---

## 1. Architecture & High-Level Design

### The big picture: two decoupled programs joined by a file

The system is split into **two separate executables** that never share memory or call each other
directly. They communicate through one artifact: a **bytecode text file** (`bytecode.txt`,
identified by the magic header `CPMBC`).

```
        ┌──────────────────────── COMPILER (one process) ───────────────────────┐
        │                                                                        │
  AST   │   ir.cc / ir.hh                                                        │
 (Node* │  ┌──────────────┐   generateExpression / generateStatement            │
  root) │  │ generate_ir  │── + generateMethod build per-method ───┐            │
 ───────┼─▶│  (lowering)  │   Basic Blocks of TAC + CFG edges        │            │
        │  └──────────────┘                                          ▼            │
        │                                              ┌───────────────────────┐  │
        │                                              │  In-memory IR:        │  │
        │                                              │  methods → blocks →   │  │
        │                                              │  TACinstructions      │  │
        │                                              └───────────┬───────────┘  │
        │             printTAC()   writeCFG()                      │              │
        │             (debug text) (Graphviz .dot)                 ▼              │
        │                                              ┌───────────────────────┐  │
        │                                              │ generateByteCode /    │  │
        │                                              │ emitByteCode          │  │
        │                                              │ TAC → stack opcodes   │  │
        │                                              └───────────┬───────────┘  │
        └──────────────────────────────────────────────────────────┼────────────┘
                                                                     ▼
                                                          ╔════════════════════╗
                                                          ║   bytecode.txt     ║   ← the contract
                                                          ║   header "CPMBC"   ║
                                                          ╚═════════╤══════════╝
                                                                    ▼
        ┌──────────────────── INTERPRETER (separate process) ───────────────────┐
        │   interpreter.cc / interpreter.hh                                      │
        │   ┌──────────┐   parse text into Method{code,labels,params}            │
        │   │  load()  │──────────────────────────────────┐                      │
        │   └──────────┘                                   ▼                      │
        │                                       ┌───────────────────────┐        │
        │                                       │   run()               │        │
        │                                       │   stack-based VM       │── stdout
        │                                       │   (fetch-decode-exec)  │        │
        │                                       └───────────────────────┘        │
        └────────────────────────────────────────────────────────────────────────┘
```

### How the two halves interact

1. **The IR is a *register/temp-based* representation.** `generate_ir` walks the AST and produces
   three-address instructions of the shape `op arg1 arg2 -> result`, where `result` is usually a
   fresh temporary like `t0`, `t1`. These instructions are grouped into **basic blocks**
   (straight-line code with one entry / one exit) connected by **CFG edges** (`successors` /
   `predecessors`). This form is easy to *generate from a tree* and easy to *visualize*.

2. **`emitByteCode` lowers that temp-based TAC into a *stack-based* opcode stream.** A TAC line like
   `ADD t0 t1 -> t2` becomes three stack ops: push `t0`, push `t1`, `ADD`, then `STORE t2`.
   Temporaries and source variables both become **named locals** addressed by string keys.

3. **The interpreter is a stack machine.** `load` re-parses the text file into in-memory `Method`
   objects (instruction list + label→index map + parameter list). `run` then executes a classic
   **fetch–decode–execute** loop over an operand stack (`stack<Value>`) and a call stack of
   `Frame`s.

### Core design decisions & their motivation

| Decision | What it means | Why (motivation) |
|----------|---------------|------------------|
| **Compiler and interpreter are separate executables** | The IR emits a file; the interpreter reads a file. No linking between them. | Clean separation of concerns — mirrors the real-world `javac → .class → JVM` model. You can inspect, hand-edit, or diff the bytecode, and the VM is testable in isolation. |
| **A *text* bytecode format with a `CPMBC` magic header** | Bytecode is human-readable lines, not packed binary. | Trivial to debug and demo during a defense (you can open it in an editor). The header acts as a sanity/format marker. *Note: this is a reasoned estimate of intent, not stated in code.* |
| **Two IR levels: temp-based TAC → stack bytecode** | TAC is generated first, then flattened. | TAC is the natural output of a recursive AST walk and is the standard substrate for a CFG and optimization. The stack form is the simplest possible thing to *interpret*. Each representation is good at one job. |
| **Basic blocks + explicit CFG edges** | Code is segmented into blocks with predecessor/successor links. | Required for the Graphviz CFG visualization and is the canonical structure for any future dataflow optimization. |
| **Name-addressed locals & temps (`map<string,Value>`)** | No register allocation; everything is a named slot. | Maximum simplicity — the IR can mint unlimited temps (`newTemp`) without worrying about a fixed register file. Trade-off: map lookups by string are slow, but correctness/clarity wins for a teaching compiler. |
| **`Value` as a "fat" tagged struct (not a true union)** | One struct holds an enum tag plus *all* possible fields (`i`, `f`, `b`, `arr`, `obj`). | Avoids manual union lifetime management; `shared_ptr` members give automatic memory management for arrays/objects. Trade-off: each `Value` is larger than necessary. |
| **Dynamic method dispatch via `class + "::" + name`** | A method call looks up `methods[obj->cls + "::" + methodName]` at runtime. | Lets one flat global method map serve all classes, and dispatch follows the *runtime* object's class. Simple and uniform. |

---

## 2. Component Breakdown (IR & Interpreter)

### 2.1 The IR module — [ir.cc](ir.cc) / [ir.hh](ir.hh)

**Primary responsibility:** Translate a semantically-valid AST into lower-level forms and emit them.
It has three output products driven from the same in-memory IR:

- **`printTAC()`** — a textual dump of the three-address code (debugging).
- **`writeCFG()`** — a Graphviz `.dot` control-flow graph (visualization).
- **`generateByteCode()`** — the executable `bytecode.txt` consumed by the interpreter (the real product).

It is implemented as the `IntermediateRepresentation` class, which carries all generation state
(counters, the method list, and the "cursor" context: current block, current method, current class).

**Key data structures (declared in [ir.hh](ir.hh)):**

| Struct / class | Purpose |
|----------------|---------|
| `TACinstructions` | One three-address instruction: `{op, arg1, arg2, result}`. The atom of the IR. |
| `BasicBlock` | A labelled run of straight-line `TACinstructions` plus `successors` / `predecessors` (the CFG edges). |
| `MethodIR` | One method: its `name`, ordered `params`, and its list of `basicBlocks`. |
| `IntermediateRepresentation` | The generator/driver class holding all state and the public API. |
| `ByteCode` | **Empty class** — leftover scaffolding, currently unused. |

### 2.2 The Interpreter module — [interpreter.cc](interpreter.cc) / [interpreter.hh](interpreter.hh)

**Primary responsibility:** Load and execute the bytecode file on a **stack-based virtual machine**.
Two phases:

- **`load()`** — parse the `bytecode.txt` lines into a `map<string, Method>` (one entry per method,
  with its instruction vector, label→index map, and parameter names).
- **`run()`** — the VM loop. Maintains an operand stack of `Value`s, a current `Frame`, and a call
  stack of saved frames; dispatches each opcode by string comparison.

**Key data structures (declared in [interpreter.hh](interpreter.hh)):**

| Struct | Purpose |
|--------|---------|
| `Value` | A runtime tagged value: `tag ∈ {INT, FLOAT, BOOL, ARRAY, OBJ}` plus fields `i`, `f`, `b`, `arr` (`shared_ptr<vector<Value>>`), `obj` (`shared_ptr<Obj>`). |
| `Obj` | A heap object instance: its class name `cls` and a `map<string,Value>` of `fields`. |
| `Instr` | One decoded bytecode instruction: an `op` string and a vector of string `args`. |
| `Method` | A loaded method: `name`, `argc`, ordered `params`, `code` (vector of `Instr`), and `labels` (label → instruction index). |
| `Frame` | A call-frame: pointer to the executing `Method`, the program counter `pc`, and `locals` (`map<string,Value>`). |

---

## 3. Comprehensive Function Dictionary

Every function in the four files is listed below, grouped by file/class. Signatures are given as
they appear in the source.

### 3.1 [interpreter.cc](interpreter.cc) — value helpers

| Function Signature | What it does | Why it does it (motivation / design choice) |
|---|---|---|
| `Value makeInt(long v)` | Builds a `Value` tagged `INT` holding `v`. | Factory helper so integer results are constructed in one consistent place rather than ad-hoc each time. |
| `Value makeBool(bool v)` | Builds a `Value` tagged `BOOL` holding `v`. | Same factory rationale for booleans; comparison/logic ops all funnel through it. |
| `static double asDouble(const Value& v)` | Returns `v.f` if `FLOAT`, else `double(v.i)`. | Single coercion point so mixed int/float arithmetic and all comparisons can work in `double`. `static` = file-local (internal linkage). |
| `static Value numOp(const Value& a, const Value& b, char op)` | Applies one of `+ - * / ^` to two values; promotes to `FLOAT` if *either* operand is float, otherwise does `long` integer math. | Centralizes arithmetic + the int/float promotion rule. The `^` case uses `pow()` for both paths. One function covers five opcodes, keeping `run` thin. |
| `static Value cmpOp(const Value& a, const Value& b, const string& op)` | Compares two values (`LT/GT/LEQ/GEQ/EQ/NE`) as doubles, returns a `BOOL`. | Comparisons always yield a boolean and can mix int/float, so converting both to `double` and dispatching on the op string is the simplest uniform implementation. |
| `static void printValue(const Value& v)` | Prints a `Value` to `stdout`: float as `f`, bool as `"true"/"false"`, otherwise the integer `i`. | Implements the `PRINT` opcode's formatting. Type-aware output is needed because the VM is dynamically typed. |
| `void load(const string& path, map<string, Method>& methods)` | Reads the bytecode file line-by-line and fills `methods`: recognizes `method … argc`, `params …`, `end`, label lines (`name:`), and instruction lines. | The interpreter's *front end* — turns flat text into structured `Method`s. Resolving labels to `code.size()` here means jumps are O(1) index lookups at run time, not string scans. |
| `void run(map<string, Method>& methods)` | The VM. Starts in `main`, runs a fetch-decode-execute loop over an operand stack + call stack, dispatching every opcode. Halts on `HALT` or a top-level `RETURN`. | The heart of execution. A flat `if/else if` opcode dispatch keeps the VM simple and readable at the cost of string-compare overhead per instruction. |
| `int main(int argc, char** argv)` | Entry point: requires a bytecode-file argument, calls `load` then `run`. | Standard CLI driver wiring for the interpreter executable. |

### 3.2 [ir.cc](ir.cc) — `IntermediateRepresentation` lifecycle & helpers

| Function Signature | What it does | Why it does it (motivation / design choice) |
|---|---|---|
| `IntermediateRepresentation::IntermediateRepresentation()` | Default constructor (empty body). | All members have in-class initializers, so no explicit setup is needed. |
| `IntermediateRepresentation::~IntermediateRepresentation()` | Destructor: deletes every `BasicBlock` then every `MethodIR`. | The IR owns its blocks/methods via raw `new`, so it must free them by hand to avoid leaks. |
| `string newTemp()` | Returns `"t" + tempCounter++` (e.g. `t0`, `t1`). | Mints unique temporaries for intermediate expression results — the backbone of three-address code generation. |
| `string newLabel()` | Returns the current `labelCounter++` as a string (e.g. `0`, `1`). | Supplies unique label numbers. (`newBlock` prefixes `"BB"`.) *Note: the header comment says it returns `L0, L1…`, but the code returns a bare number — minor doc drift.* |
| `BasicBlock* newBlock()` | Allocates a `BasicBlock` labelled `"BB" + newLabel()` and registers it on the current method. | Creates CFG nodes on demand as control-flow statements are lowered. |
| `bool isTerminated(BasicBlock* block)` | True if the block's last instruction is `GOTO` or `RETURN`. | Prevents appending a redundant/illegal second jump after a block already ends in a branch — keeps the CFG well-formed. |
| `void emit(string op, string arg1, string arg2, string result)` | Appends a `TACinstructions` to the **current** block. | One choke-point for adding IR, so every generator method just calls `emit(...)`. |
| `void addEdge(BasicBlock* from, BasicBlock* to)` | Records a CFG edge both ways (`from.successors`, `to.predecessors`). | Maintains the bidirectional graph that the Graphviz output and any future dataflow analysis need. |
| `void setCurrentBlock(BasicBlock* block)` | Sets `currentBlock`. | Tiny setter so control-flow code can "move the cursor" to whichever block subsequent `emit`s land in. |

### 3.3 [ir.cc](ir.cc) — `IntermediateRepresentation` generation

| Function Signature | What it does | Why it does it (motivation / design choice) |
|---|---|---|
| `string generateExpression(Node* node)` | Recursively lowers an expression node and **returns the name/temp holding its value**. Handles literals, IDs (incl. implicit field reads via `GET_FIELD this`), binary ops, `Not`, array literals/access/`length`, and method/constructor calls. | Returning a "where the result lives" string is the essence of TAC generation: parents consume children's result names as their `arg1`/`arg2`. The implicit field-access case is what makes bare field names work inside methods. |
| `void generateStatement(Node* node)` | Lowers a statement node: declarations, assignments (var / field / array element), `read`/`print`/`return`, blocks, `if`, `if/else`, `for`, `break`, `continue`. Builds the CFG for control flow. | The structural counterpart to `generateExpression`. It owns block creation and edge wiring for every control-flow construct. Falls through to `generateExpression` for expression-statements. |
| `void generateMethod(Node* node)` | Resets per-method state, names the method (`main` / `name` / `Class::name`), creates `MethodIR` + entry block, binds parameters into `params`, appends implicit `this` for class methods, then lowers the body. | Establishes the per-method context that every other generator relies on. Appending `this` last is the convention the call ABI depends on (see Q3 in §4). |
| `void generate_ir(Node* node)` | Top-level driver. **Pass 1:** collect all class names and class field names. **Pass 2:** generate `main`, then every class method (with `currentClass` set), and any top-level statement block. | The two-pass split lets expression generation know whether an identifier is a field or a constructor *before* it generates code that references it. |

### 3.4 [ir.cc](ir.cc) — output / emission

| Function Signature | What it does | Why it does it (motivation / design choice) |
|---|---|---|
| `void writeCFG(string filename = "IR_tree.dot")` | Opens the file, writes the Graphviz `digraph` wrapper, and delegates the body to `generateDot`. | Public entry for CFG visualization; keeps the boilerplate (`digraph { … }`) separate from node rendering. |
| `void generateDot(std::ofstream& out)` | Emits each block as a Graphviz box node (label = its instructions) and each successor edge as `A->B`. | Produces a visual CFG — invaluable for explaining control flow during a defense. |
| `void printTAC()` | Prints all methods → blocks → instructions to `stdout` in readable `op arg1 arg2 -> result` form. | A quick textual inspection of the IR without rendering a graph. |
| `static bool isInt(const string& s)` | True if `s` is non-empty and consists only of digits / `-`. | Lets `emitLoad` decide at emit-time whether a TAC operand string is an integer literal vs. a variable. `static` = file-local. |
| `static bool isFloat(const string& s)` | True if `s` contains `.` and the part before the `.` is an integer. | Distinguishes float literals from ints/variables when choosing the push opcode. |
| `void emitLoad(std::ofstream& out, const string& s)` | Emits the right "push operand" opcode for `s`: `PUSH_INT` / `PUSH_FLOAT` / `PUSH_BOOL` for literals, else `LOAD <var>`. | The bridge from temp-based operands to a stack machine: before any stack op can run, its operands must be pushed. Detecting literal vs. variable by *string shape* avoids carrying type metadata into the bytecode. |
| `void generateByteCode(string filename = "bytecode.txt")` | Writes the full bytecode file: `CPMBC` header, then per method a `method`/`params` header, each block's label + lowered instructions, a trailing `HALT` (for `main`) or `RETURN`, and `end`. | The real deliverable — the file the interpreter runs. The trailing `HALT`/`RETURN` guarantees every method terminates even if the source didn't end with a return. |
| `void emitByteCode(std::ofstream& out, TACinstructions& in)` | Translates **one** TAC instruction into one-or-more stack opcodes (e.g. `IF_FALSE`→push+`JMP_FALSE`; `ASSIGN`→push+`STORE`; binary ops fall to the default: push both, op, `STORE result`). | The core TAC→stack lowering. Centralizing it per-opcode keeps `generateByteCode` a simple loop and makes the instruction-set mapping easy to audit. |

> [interpreter.hh](interpreter.hh) and [ir.hh](ir.hh) declare **structs and one class interface only**
> — they contain no free-function definitions. Their types are catalogued in §2.1 / §2.2.

---

## 4. Anticipated Presentation Questions

These are the spots reviewers most often probe, with ready defenses.

### Q1. Why two representations — TAC *and* stack bytecode? Isn't that redundant?

**Defense:** They serve different consumers. **TAC** (`op arg1 arg2 -> result`) is the natural output
of a recursive descent over the AST — each subexpression hands its parent a result name — and it is
the standard substrate for a CFG and for any later optimization (it's also what `printTAC`/`writeCFG`
visualize). **Stack bytecode** is the simplest thing to *execute*: no operand addressing, just
push/op/store. `emitByteCode` is the single, auditable place that flattens one into the other.
Keeping them separate means each form stays good at exactly one job.

### Q2. The interpreter dispatches opcodes with a giant `if/else if` chain on strings. Why not a jump table / enum?

**Defense:** It's a deliberate simplicity-vs-speed trade-off for a teaching VM. String dispatch keeps
the bytecode human-readable and the VM loop trivially understandable — you can read `run()` top to
bottom and see every opcode. The cost is a string compare per instruction; for the program sizes this
runs, that's irrelevant. A production VM would intern opcodes to an enum and use a switch or computed
goto. *Note: the "for teaching simplicity" rationale is a reasoned estimate of intent.*

### Q3. Walk us through a method call. How do arguments and the receiver (`this`) line up?

**Defense:** It's a small calling convention that the IR and VM agree on:
- In the IR (`generateExpression`, `CallMethod`), each argument is emitted as a `PARAM`, then the
  **receiver is emitted last** as an extra `PARAM "this"`, and `CALL name (argc+1)` is emitted.
- `generateMethod` likewise appends `"this"` as the **last** entry of the method's `params`.
- In the VM (`run`, `CALL`): every `PARAM` does `args.push_back(pop())`, so `args.back()` is the
  receiver. The callee is resolved dynamically as `methods[self.obj->cls + "::" + name]`, a new
  `Frame` is created, and `params[k]` is bound to `args[args.size()-argc+k]`. Because both sides put
  `this` last and use the same count, the positions line up exactly. The old frame is pushed on the
  call stack; `RETURN` pops it back and pushes the return value.

The key insight to state plainly: **dispatch is dynamic** — it keys off the runtime object's `cls`,
not a static type.

### Q4. `Value` carries `i`, `f`, `b`, `arr`, and `obj` all at once. Why not a real `union`?

**Defense:** A real `union` containing `std::shared_ptr` members requires manual construction/
destruction (placement new, explicit destructor calls) because the smart pointers have non-trivial
lifetimes. A plain tagged struct sidesteps all of that: the `shared_ptr`s manage array/object memory
automatically (reference counting, no manual `free`), and copying a `Value` "just works." The only
cost is that each `Value` is a few words larger than strictly necessary — a non-issue here. It trades
a little memory for correctness and zero manual memory management.

### Q5. How are labels, jumps, and basic blocks reconciled between the CFG and the linear bytecode?

**Defense:** In the IR, control flow targets **block labels** (`BB0`, `BB1`, …) via `GOTO`/`IF_FALSE`,
and `addEdge` records the CFG edges. `generateByteCode` then emits the blocks **in creation order**,
writing each block's label as a `name:` line. The interpreter's `load` records `labels[name] =
code.size()`, so at run time `JMP`/`JMP_FALSE` resolve to an O(1) instruction index. Because blocks
are laid out contiguously, an `IF_FALSE`/`GOTO` to the very next block is often a redundant
fall-through jump — it's kept anyway so the lowering stays uniform and the CFG stays explicit, and
`isTerminated` prevents emitting a *second* terminator on an already-closed block.

### Q6. How does the IR know that a bare identifier is a field, a constructor, or a local?

**Defense:** That's what the **two-pass** `generate_ir` buys us. Pass 1 records every class name
(`classNames`) and every class's fields (`classFields`). Then in `generateExpression`: a bare `ID`
that is *not* a known local/param but *is* a field of the current class is lowered to
`GET_FIELD this <name>`; a `CallMethod` whose name is in `classNames` becomes `NEW_OBJECT` (a
constructor) rather than a `CALL`. Collecting this metadata before generation means the code never
references a symbol whose kind it hasn't yet resolved.

### Q7. (Likely follow-up) What are the known limitations / things you'd harden next?

**Defense — be candid:** There's no array-bounds or null-object checking in the VM; `printValue`
doesn't format `ARRAY`/`OBJ` values; the `ByteCode` class is empty leftover scaffolding; integer `^`
goes through floating-point `pow` then truncates; and operand type-detection in `emitLoad` is by
string shape rather than carried type info. None affect correctness on valid programs, and each is a
clear, scoped next step rather than a design flaw.

---

## Appendix: Bytecode Format & Opcode Reference

### File layout (produced by `generateByteCode`, parsed by `load`)

```
CPMBC                       ← magic header (skipped by load)
method <name> <numParams>   ← begins a method
params <p0> <p1> ...        ← parameter names in order (this is last for class methods)
<label>:                    ← a basic-block label (recorded as an instruction index)
  <opcode> [args...]        ← zero or more instructions
  ...
HALT | RETURN               ← trailing terminator (HALT for main, RETURN otherwise)
end                         ← ends the method
```

### Stack-machine opcodes understood by `run()`

| Category | Opcodes |
|----------|---------|
| Push literals | `PUSH_INT`, `PUSH_FLOAT`, `PUSH_BOOL` |
| Locals | `LOAD <name>`, `STORE <name>` |
| Arithmetic | `ADD`, `SUB`, `MUL`, `DIV`, `POW` |
| Comparison | `LT`, `GT`, `LEQ`, `GEQ`, `EQ`, `NE` |
| Boolean | `AND`, `OR`, `NOT` |
| Control flow | `JMP <label>`, `JMP_FALSE <label>` |
| I/O | `PRINT`, `READ [type]` |
| Calls | `PARAM`, `CALL <name> <argc>`, `RETURN`, `HALT` |
| Objects | `NEW_OBJECT <class>`, `GET_FIELD <name>`, `SET_FIELD <name>` |
| Arrays | `NEW_ARRAY`, `ARRAY_LOAD`, `ARRAY_STORE`, `ARRAY_LEN` |

### TAC opcodes produced by the IR (before lowering)

`ADD SUB MUL DIV POW · AND OR NOT · LT GT LEQ GEQ EQ NE · ASSIGN · GOTO IF_FALSE ·
PRINT READ RETURN · PARAM CALL · NEW_OBJECT GET_FIELD SET_FIELD · NEW_ARRAY ARRAY_LOAD
ARRAY_STORE ARRAY_LEN`

Each is mapped to its stack-opcode sequence by `emitByteCode` (binary ops use the default
"push arg1, push arg2, op, STORE result" path).


| Opcode | Operands | Effect |
|---|---|---|
| `PUSH_INT` / `PUSH_FLOAT` / `PUSH_BOOL` | literal | push a constant |
| `LOAD` | name | push the value of a local/param |
| `STORE` | name | pop and store into a local |
| `ADD` `SUB` `MUL` `DIV` `POW` | — | pop 2, push result |
| `AND` `OR` `NOT` | — | boolean ops |
| `LT` `GT` `LEQ` `GEQ` `EQ` `NE` | — | pop 2, push bool |
| `JMP` | label | set pc to label |
| `JMP_FALSE` | label | pop; if false, set pc to label |
| `PARAM` | — | mark top of stack as the next call argument |
| `CALL` | name, argc | call method; resolved at run time as `(receiver's class)::name`, receiver is the trailing arg (decision #7) |
| `NEW_OBJECT` | className | construct (tag object with its class), push reference |
| `GET_FIELD` / `SET_FIELD` | fieldName | object field read/write |
| `NEW_ARRAY` | — / size | allocate array, push reference |
| `ARRAY_LOAD` / `ARRAY_STORE` | — | indexed read/write (array + index on stack) |
| `ARRAY_LEN` | — | push array length |
| `PRINT` | — | print top of stack |
| `READ` | type | read a token from stdin as `type` (int/float/boolean), push it |
| `RETURN` | — | pop frame, push return value into caller |
| `HALT` | — | stop (end of `main`) |