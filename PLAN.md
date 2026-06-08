# Assignment 3 — Back-end Implementation Plan (IR → Bytecode → Interpreter)

> **Target: Option 1** — Task 1 (TAC IR + CFG), Task 2.1 (stack-based bytecode generation),
> Task 3.1 (bytecode interpreter). This is *your own* implementation.
>
> **On the reference project ([`filips/`](filips/)):** Filip's code is here as *background reading only* —
> a worked example of one Option-1 backend you can consult when a concept is unclear. It is **not** a
> template to copy, and this plan does **not** merge his code into yours. His design makes choices that
> differ from yours on purpose:
> - he uses polymorphic `Expression*` objects; **you** use string-quadruple `TACinstructions`.
> - he encodes control flow as `true_end`/`false_end` block pointers; **you** use labels + a
>   `successors`/`predecessors` CFG.
> - he flattens every variable into integer slots; **you** can key locals by name.
>
> Because the models differ, you cannot drop his `ir.cpp` in and compile it — and you shouldn't want to.
> When this plan points at a Filip file, it means *"if you're stuck on this idea, here's one way it was
> done — adapt the idea, not the code."* Your design below is grounded entirely in **your** existing
> skeleton ([ir.hh](ir.hh), [ir.cc](ir.cc)) and **your** AST ([parser.yy](parser.yy)).
>
> **Sources reviewed:** the assignment ([assignment_3.pdf](assignment_3.pdf)); your project
> ([ir.hh](ir.hh), [ir.cc](ir.cc), [parser.yy](parser.yy), [Node.h](Node.h),
> [symboltable.hh](symboltable.hh), [semanalysis.hh](semanalysis.hh), [main.cc](main.cc),
> [Makefile](Makefile), [test_files/valid/](test_files/valid/)).

---

## 1. What the assignment requires (and what your skeleton already commits to)

From [assignment_3.pdf](assignment_3.pdf):

- **Task 1 — IR:** three-address code (TAC) instructions, basic blocks, and a control-flow graph;
  plus a `.dot` file visualizing the CFG.
- **Task 2.1 — Bytecode:** traverse the IR from `main()`, translate each TAC instruction to bytecode,
  handle control flow with jumps, don't re-emit already-visited blocks. Output a **readable text
  bytecode file** (or binary + pretty-printer). You may pick any documented instruction set — a
  Java-like **stack machine** is the natural fit for your TAC.
- **Task 3.1 — Interpreter:** a **separate program** that parses the bytecode file, keeps a **data
  stack** and an **activation (call) stack**, and executes sequentially or via jumps.
- **Grading:** minimum = IR for all valid programs + pretty-printed CFG + working bytecode/interpreter
  for [test_files/valid/test1.cpm](test_files/valid/test1.cpm). Higher grades = full language,
  recursion, complex control flow.

**Your IR design — already sketched in [ir.hh](ir.hh) — is the conventional textbook model.** Keep it:

```
TACinstructions { string op, arg1, arg2, result; }        // a quadruple
BasicBlock      { string label;
                  vector<TACinstructions> instructions;
                  vector<BasicBlock*> successors, predecessors; }
MethodIR        { string name; vector<BasicBlock*> basicBlocks; }
```

This maps cleanly onto the three required artifacts:

| Required artifact | Your representation |
|---|---|
| TAC instruction | one `TACinstructions` quadruple, e.g. `{ "ADD", "t0", "t1", "t2" }` = `t2 := t0 + t1` |
| Basic block | one `BasicBlock`; expressions append instructions to `currentBlock` |
| CFG | `successors`/`predecessors` edges, maintained via `addEdge`; emitted as `.dot` by `writeCFG` |
| Jumps | explicit TAC ops (`GOTO label`, `IF_FALSE cond label`) **plus** a CFG edge for the same target |

> **Why this is a clean, independent design.** It is the standard compiler-construction approach
> (quadruples + labeled blocks + an explicit edge list). Control flow lives in *labels + edges*, so
> your bytecode jumps can be ordinary `JMP label` / `JMP_FALSE label` instructions resolved to
> instruction offsets — simpler than Filip's "follow the block's true/false pointer" scheme, and
> entirely your own.

### Design decisions (settled 2026-06-08)

These were chosen deliberately; every stage below assumes them. Each notes the rejected alternative and
why, so the reasoning survives.

1. **`generateExpression` returns the *place* of its result (a string).** ✅ *Decided.* Your stub already
   returns `string`. Each expression lowers to TAC in `currentBlock` and returns the name holding its
   value: a temp (`t0`), a variable name, or a literal token (e.g. `5`, `3.14`). *(Rejected: richer value
   objects — more machinery than your string-quadruple TAC needs.)*
2. **Bytecode = a readable text file, flat instruction list per method, with label-keyed jumps.**
   ✅ *Decided.* Jumps name labels; the interpreter builds a `label → instruction-index` map at load time
   and jumps by setting the program counter. *(Rejected: baking numeric offsets into the file — shifts on
   every edit, harder to emit/hand-trace; and a binary format + pretty-printer — more work for no benefit
   here.)*
3. **Interpreter locals are keyed by name, not integer slots.** ✅ *Decided.* Each call frame holds a
   `map<string, Value>` (or `unordered_map`). Your TAC operands are already names, so this avoids a whole
   slot-allocation pass. A deliberate divergence from Filip. *(Rejected: integer slots — faster lookups,
   but needs a slot-allocation pass; a possible later optimization, not a requirement.)*
4. **Type info during IR comes from a small local map, not the stateful symbol table.** ✅ *Decided.* As
   you walk declarations you already see each variable's type; record `varName → typeString` per method,
   and gather class names from the `Class` nodes up front. Enough to resolve method calls and constructions
   without driving `enterScope`/`exitScope` in lockstep (see Stage 2's class/field handling). *(Rejected: reusing the stateful
   symbol table — order-sensitive and needs scope bookkeeping.)*
5. **`LengthOf` keeps its current parser shape — Option A.** ✅ *Decided.* Do **not** change the grammar.
   Read the array's name from `node->value` and emit `ARRAY_LEN`; this matches what semantic analysis
   already does ([semanalysis.cc:237](semanalysis.cc#L237)) and is correct for every test file (operands
   are plain IDs). *(Rejected: Option B — attach the operand as a child; strictly more general but would
   force edits to already-graded semantic analysis with no test-visible gain. See §6.2.)*
6. **Numeric result types follow your existing semantic analysis.** ✅ *Decided.* Per
   [semanalysis.cc:254-263](semanalysis.cc#L254-L263): a numeric op yields `float` if either operand is
   float, else `int`. So at runtime `int / int` is **truncating integer division** (test4's
   `(n / i) * i = n` relies on this) and `int ^ int → int` (test1's `2 ^ (4*2)`); a float operand promotes
   to float division. Keep codegen and the interpreter consistent with this. (See §6.9.)

---

## Progress snapshot (updated 2026-06-08)

What the current [ir.cc](ir.cc)/[ir.hh](ir.hh) already do, and what is left. **Stage 6 has been
dissolved** — its work was core language, not a separable "higher grade" add-on, so each subgoal now
lives in the stage that owns that layer (IR generation → Stages 2–3, bytecode → Stage 4, interpreter →
Stage 5).

**Done (in [ir.cc](ir.cc)/[ir.hh](ir.hh)):**
- All IR data structures and helpers: `newTemp`, `newLabel`, `newBlock`, `emit`, `addEdge`,
  `setCurrentBlock`, `writeCFG`/`generateDot`, `printTAC` ([ir.cc:22-42](ir.cc#L22-L42),
  [ir.cc:302-369](ir.cc#L302-L369)).
- `generateExpression` for literals/IDs/booleans, all binary ops, `Not`, `ArrayAccess` (read),
  `LengthOf`, and both `CallMethod` forms ([ir.cc:44-128](ir.cc#L44-L128)).
- `generateStatement` for declarations, `AssignVariable`/`Assign` (incl. array-store write),
  `Read`/`Print`/`Return`, nested `StatementBlock`, and **all** control flow —
  `IfStatement`, `IfElseStatement`, `ForStatement`, `Break`, `Continue`
  ([ir.cc:130-274](ir.cc#L130-L274)).
- `generate_ir` collects `classNames` and walks `Main method` + each `Class`'s `Method`s
  ([ir.cc:313-330](ir.cc#L313-L330)); `varTypes`/`classNames` members exist ([ir.hh:48-49](ir.hh#L48-L49)).

**Update (2026-06-08, later):** all of Stage 2 — including the full-language work folded in from the old
Stage 6 — is now **done and verified**. All three bugs below are fixed (parser-side rename + regenerate for
#1, child index fix for #2, dead line removed for #3); `Array`→`NEW_ARRAY`/`ARRAY_STORE` and the
classes/fields/parameters/`this` resolution are implemented and confirmed against `test1`–`test8`. See the
checked-off items in §3 Stage 2 for the verified TAC output (e.g. `Counter::inc` → `GET_FIELD this value`/
`SET_FIELD this value`).

**What's left:**
- **Stage 4** (bytecode generation/serialization) and **Stage 5** (interpreter) — not started; both now
  include the call/object/array opcodes formerly parked in the old Stage 6.

> ✅ **Three bugs — fixed.** (Originally found reviewing [ir.cc](ir.cc) against [parser.yy](parser.yy);
> kept here for the record.)
> 1. **`ForStatement` init was silently dropped.** The code checked `"Initialization"` but the grammar
>    emitted the misspelled `"Initilization"` — fixed by correcting the spelling in `parser.yy` (both
>    `for_init` rules) and regenerating `parser.tab.cc`; `ir.cc` already used the correct spelling.
> 2. **`CallMethod` (2-child) iterated the wrong child for args.** Was `children.front()->children` (the
>    receiver); fixed to `children.back()->children` (the `Arguments` node).
> 3. **Stray `varTypes` write in `Assign`.** Removed the line that wrote a garbage `varTypes[""]` entry —
>    type tracking now happens only in the declaration cases (`AssignVariable`/`Variable`), as intended.

---

## 2. Your AST reference (build this table before writing any traversal)

These are facts about **your** parser ([parser.yy](parser.yy)) — the foundation of the traversal.
Confirm each against the grammar as you implement; the gotchas in §6 expand on the ⚠ rows.

| Your node `type` | Shape / where data lives |
|---|---|
| `Addition` `Subtraction` `Multiplication` `Division` `PowerOf` `And` `Or` `LessThan` `GreaterThan` `LessOrEqual` `GreaterOrEqual` `EqualTo` `NotEqualTo` | 2 children (lhs, rhs); operator lexeme in `value` ([parser.yy:185-252](parser.yy#L185-L252)) |
| `Not` | 1 child; `value` empty |
| `ArrayAccess` | 2 children (array expr, index expr); `value` empty |
| `Array` | 2 children (baseType node, `Arguments`) — array literal/creation |
| `LengthOf` | ⚠ **0 children**; operand's `value` string copied into this node's `value` ([parser.yy:259-262](parser.yy#L259-L262)) |
| `CallMethod` (2 children: objExpr, `Arguments`) | `obj.method(args)`; `value` = method name |
| `CallMethod` (1 child: `Arguments`) | `name(args)` — ⚠ self-call **or** object construction; `value` = name |
| `int` `float` | literal in `value` |
| `true` `false` | ⚠ truth is in `type`; `value` is **empty** ([parser.yy:286-287](parser.yy#L286-L287)) |
| `ID` | name in `value` |
| `Variable` `VolatileVariable` | `value` = name; 1 child = type node |
| `AssignVariable` `AssignVolatileVariable` | `value` = name; 2 children (type node, init expr) |
| `Assign` | 2 children (lhs expr, rhs expr); `value` empty |
| `Print` `Read` `Return` | 1 child |
| `Break` `Continue` | no children |
| `IfStatement` | children: `Condition`→[expr], then optional then-statement (raw, **may be a bare statement, not a block**) |
| `IfElseStatement` | children: `Condition`→[expr], `ThenBody`, `ElseBody` — ⚠ a **separate node type**, not folded into `IfStatement` |
| `ForStatement` | ⚠ **variable child set** in order `Initilization?`, `Condition?`, `Update`, `LoopBody` — init/cond may be absent, so **dispatch by child `type`, not index** ([parser.yy:448-467](parser.yy#L448-L467)) |
| `StatementBlock` `EmptyStatementBlock` | flat statement list (`StatementList` is transient, won't appear as a block child) |
| `Main method` | 1 child = the body `StatementBlock` (the `: int` return type is dropped) ([parser.yy:74-78](parser.yy#L74-L78)) |
| `Method` | children: `Parameters`, `ReturnType`, `StatementBlock` ([parser.yy:167-183](parser.yy#L167-L183)) |
| `Parameter` | `value` = name; 1 child = type node (`Parameters` holds these; `value` `"None"` if empty) |
| `Class` | `value` = class name; children = fields (`Variable`/`VolatileVariable`) and `Method`s in source order |
| root `Program` | usually globals (`Variable`…) + `Class`… + `Main method`; ⚠ the bare `stmtBl` program form gives a single `StatementBlock` child and **no `Main method`** ([parser.yy:53-71](parser.yy#L53-L71)) |

**Wrapper nodes to unwrap** before reaching real exprs/bodies: `Condition`, `ThenBody`, `ElseBody`,
`LoopBody`, `Initilization`, `Update`, `ReturnType`. Your [ir.cc:191-204](ir.cc#L191-L204) already
finds `Main method`/`Class` by `type` — correct for your flattened root.

---

## 3. Step-by-step implementation plan

Each stage builds on **your** skeleton's method signatures
([ir.hh:45-69](ir.hh#L45-L69)): `newTemp`, `newLabel`, `emit`, `generateExpression` (returns the
result place), `generateStatement`, `generateMethod`, `generate_ir`, `addEdge`, `setCurrentBlock`,
`printTAC`, `writeCFG`, `generateDot`.

> *Filip pointers in this section are optional.* Read them only if a concept is unclear, and remember
> his model differs (no labels, polymorphic nodes, integer slots) — take the idea, write your own code.

### Stage 0 — Build wiring & scaffolding

**Goal:** the (still empty) IR compiles and runs in the pipeline before any logic exists.

- [X] Add `ir.cc` to the `compiler` recipe (sources + link line) in [Makefile](Makefile).
- [X] Add a separate **`interpreter:`** target — its own binary, **not** linked with the parser/lexer.
      *What this means:* your `compiler` recipe links the parser, lexer, `main.cc`, symbol table, semantic
      analysis and `ir.cc` together — that program turns source → `bytecode.txt`. The **interpreter is a
      different program** that only reads `bytecode.txt` at runtime; it never touches the grammar. So its
      recipe lists *only its own files*, and you build it on its own with `make interpreter`. Mirror the
      style of the existing `compiler:` rule ([Makefile:1-2](Makefile#L1-L2)) but with no parser objects:

      ```makefile
      interpreter: interpreter.cc interpreter.hh
      	g++ -g -w -o interpreter interpreter.cc -std=c++14
      ```
      *(The recipe line must be indented with a real TAB, like your other rules.)*
- [X] Add an **`IR_tree:`** dot target (`dot -Tpdf IR_tree.dot -o IR_tree.pdf`); extend `clean` to remove
      `bytecode.txt`, `IR_tree.*`, and the `interpreter` binary. This is exactly the shape of your existing
      `tree:` / `clean` rules ([Makefile:9-13](Makefile#L9-L13)):

      ```makefile
      IR_tree:
      	dot -Tpdf IR_tree.dot -o IR_tree.pdf
      ```
      Then append `bytecode.txt IR_tree.dot IR_tree.pdf interpreter` to the `rm -f …` line in `clean`.
- [X] In [main.cc](main.cc), uncomment the IR object ([main.cc:29](main.cc#L29)) and the three calls
      ([main.cc:84-86](main.cc#L84-L86)), placing them after `semanalyzer.analyze()`. Note `writeCFG` takes
      a `string&` ([ir.hh:69](ir.hh#L69)), so you must pass a **variable**, not a string literal:

      ```cpp
      IntermediateRepresentation ir;        // uncomment at line 29 (global, like st/semanalyzer)
      // ... inside the try block, after semanalyzer.analyze():
      ir.generate_ir(root);
      ir.printTAC();
      string cfgFile = "IR_tree.dot";
      ir.writeCFG(cfgFile);                  // string& → needs an lvalue, not "IR_tree.dot"
      ```
- [X] Confirm `make` builds and `./compiler test_files/valid/test1.cpm` links and runs. Because the IR
      methods are still empty bodies, expect **no IR output yet** — at this stage you are only proving the
      new code compiles and links cleanly into the pipeline.

### Stage 1 — Flesh out the IR data structures

**Goal:** make `TACinstructions` / `BasicBlock` / `MethodIR` usable; implement the helpers and the CFG
printer. No AST walking yet.

**Files:** [ir.hh](ir.hh), [ir.cc](ir.cc).

- [X] Decide and **document your TAC instruction vocabulary** as `op` strings — you already have the
      binary-op map in [ir.cc:48-53](ir.cc#L48-L53) (`ADD SUB MUL DIV POW AND OR LT GT LEQ GEQ EQ NE`).
      The remaining ops are all in use across [ir.cc](ir.cc) (`NOT ASSIGN PRINT READ RETURN GOTO IF_FALSE
      PARAM CALL ARRAY_LOAD ARRAY_STORE ARRAY_LEN NEW_OBJECT`); the human-facing table is §4. Still missing
      from emitted code: `NEW_ARRAY`, `GET_FIELD`, `SET_FIELD` (added in Stage 2's array/field work).
      Add: `NOT`, `ASSIGN` (copy), `PRINT`, `READ`, `RETURN`, `GOTO`, `IF_FALSE`, `PARAM`, `CALL`,
      `NEW_ARRAY`, `ARRAY_LOAD`, `ARRAY_STORE`, `ARRAY_LEN`, `NEW_OBJECT`, `GET_FIELD`, `SET_FIELD`.

      *"Document" does **not** mean a separate code file.* A TAC `op` is just a string you hand to
      `emit(...)`; there is no enum to maintain for TAC (the **interpreter's bytecode** does get an enum —
      Stage 5 — but that's a different layer). So:
      - **For the assignment's "document your instruction set" requirement:** the §4 table *is* that
        document — reproduce it in your hand-in report / README. That's the human-facing spec.
      - **In code:** just use these exact strings consistently. To stop them drifting, optionally drop a
        reference comment near the top of [ir.cc](ir.cc):

      ```cpp
      // TAC op vocabulary (strings passed to emit):
      //   ADD SUB MUL DIV POW   AND OR NOT   LT GT LEQ GEQ EQ NE
      //   ASSIGN PRINT READ RETURN   GOTO IF_FALSE   PARAM CALL
      //   NEW_ARRAY ARRAY_LOAD ARRAY_STORE ARRAY_LEN   NEW_OBJECT GET_FIELD SET_FIELD
      ```
- [X] Implement `newTemp` (`t0,t1,…`), `newLabel`, and a `newBlock()` helper that allocates a
      `BasicBlock`, pushes it onto `currentMethod->basicBlocks`, and returns it. **As built**
      ([ir.cc:22-37](ir.cc#L22-L37)) `newBlock()` takes **no argument** — it always names the block
      `"BB" + newLabel()`, so *every* block (entry, then/else/join, loop cond/body/after) shares one `BB`
      counter and is unique. This is simpler than the plan's earlier `"L"`-prefixed jump-target idea: there
      is **one** label namespace and jump TAC just carries the target block's `->label` (e.g. `BB3`). `new
      Block` is declared private in [ir.hh:70](ir.hh#L70):

      ```cpp
      BasicBlock* IntermediateRepresentation::newBlock() {
          BasicBlock* b = new BasicBlock{"BB" + newLabel()};
          currentMethod->basicBlocks.push_back(b);
          return b;
      }
      ```
      `generateMethod` and every control-flow case call the bare `newBlock()` — no hand-rolled block
      creation remains. *(Cleanup note: `blockCounter` in [ir.hh:39](ir.hh#L39) is now dead — `newBlock`
      uses `labelCounter` via `newLabel`. Drop it, or none of the code references it.)*
- [X] Implement `addEdge` (**done** at [ir.cc:302-306](ir.cc#L302-L306)). The real task is *discipline*:
      call it **every** time you emit a `GOTO`/`IF_FALSE` or fall through to the next block, so the CFG
      edges and the jump TAC never disagree. The current control-flow cases already pair every
      `emit("GOTO"/"IF_FALSE", …)` with an `addEdge` — keep that invariant for any new branch you add.
- [X] Implement `writeCFG`/`generateDot`: one `.dot` node per block (its label + instructions as the node
      text), one edge per `successors` entry. *(Satisfies "pretty-printed CFG".)* This is the same pattern
      as `Node::generate_tree` ([Node.h:33-56](Node.h#L33-L56)) — open a stream, write `digraph { … }`,
      walk and emit nodes + edges:

      ```cpp
      void IntermediateRepresentation::writeCFG(string& filename) {
          std::ofstream out(filename);
          out << "digraph CFG {\n  node [shape=box];\n";
          generateDot(out);
          out << "}\n";
      }

      void IntermediateRepresentation::generateDot(std::ofstream& out) {
          for (MethodIR* m : methods)
              for (BasicBlock* b : m->basicBlocks) {
                  out << "  " << b->label << " [label=\"" << b->label << ":\\n";
                  for (auto& in : b->instructions)             // dump each quadruple as a line
                      out << in.op << " " << in.arg1 << " " << in.arg2 << " -> " << in.result << "\\n";
                  out << "\"];\n";
                  for (BasicBlock* s : b->successors)           // one edge per successor
                      out << "  " << b->label << " -> " << s->label << ";\n";
              }
      }
      ```

### Stage 2 — AST → IR for straight-line code (the `test1.cpm` minimum)

**Goal:** TAC + a single-block CFG for arithmetic, var decl/assign, print, return — i.e. exactly
[test_files/valid/test1.cpm](test_files/valid/test1.cpm) and [test_files/valid/test2.cpm](test_files/valid/test2.cpm).

**Files:** [ir.cc](ir.cc) — fill in `generateExpression` and the simple cases of `generateStatement`.

- [X] **Factors** ([ir.cc:43-57](ir.cc#L43-L57)): the base cases. They emit **no** TAC — each just
      *returns the place* (a name or literal) the parent will use as an operand. Note `children` is a
      `std::list`, and booleans read `type` (your `value` is empty):

      ```cpp
      if (type == "int" || type == "float") return node->value;  // literal text, e.g. "5", "3.14"
      if (type == "ID")                      return node->value;  // the variable's name
      if (type == "true")                    return "true";       // truth is in type, not value
      if (type == "false")                   return "false";
      ```
- [X] **Binary ops:** recurse into both children to get their places, `newTemp()`, emit the op, return the
      temp. Your `TAC_ops` map ([ir.cc:59-64](ir.cc#L59-L64)) already turns the node type into the op
      string. Use `front()`/`back()` since children is a list:

      ```cpp
      auto it = TAC_ops.find(type);
      if (it != TAC_ops.end()) {
          string lhs = generateExpression(node->children.front());
          string rhs = generateExpression(node->children.back());
          string t = newTemp();
          emit(it->second, lhs, rhs, t);    // e.g.  ADD t0 t1 -> t2
          return t;
      }
      ```
- [X] **`Not`:** the unary version of the same shape:

      ```cpp
      if (type == "Not") {
          string c = generateExpression(node->children.front());
          string t = newTemp();
          emit("NOT", c, "", t);
          return t;
      }
      ```
- [X] **Statements** (in `generateStatement`). A declaration with no initializer emits nothing; the
      assigning forms evaluate their init/rhs expression and copy it into the target name. `AssignVariable`
      children are `[type node, init expr]`, so the initializer is `children.back()`; `Assign` children are
      `[lhs, rhs]`. **Also fill in the `StatementBlock` case** (currently empty at
      [ir.cc:136-138](ir.cc#L136-L138)) — nested if/for bodies arrive here as a block:

      ```cpp
      if (type == "Variable" || type == "VolatileVariable") return;   // declaration only, no code

      if (type == "AssignVariable" || type == "AssignVolatileVariable") {
          string place = generateExpression(node->children.back());   // the init expr
          emit("ASSIGN", place, "", node->value);                     // name := place
          return;
      }
      if (type == "Assign") {                                         // children: [lhs, rhs]
          string rhs = generateExpression(node->children.back());
          emit("ASSIGN", rhs, "", node->children.front()->value);     // plain-ID lhs; array-store case below
          return;
      }
      if (type == "Print")  { emit("PRINT",  generateExpression(node->children.front()), "", ""); return; }
      if (type == "Read")   { emit("READ",   node->children.front()->value, "", ""); return; }  // into a var
      if (type == "Return") { emit("RETURN", generateExpression(node->children.front()), "", ""); return; }

      if (type == "StatementBlock" || type == "StatementList") {      // nested block → recurse children
          for (Node* s : node->children) generateStatement(s);
          return;
      }
      ```
- [X] In `generateMethod` ([ir.cc:276-300](ir.cc#L276-L300)) the body loop is **already written**
      ([ir.cc:290-298](ir.cc#L290-L298)): it finds the `StatementBlock` child and dispatches each statement
      through `generateStatement`. `Main method`'s single child is that block (per §2). **Parameter
      handling** (the empty loop at [ir.cc:291-293](ir.cc#L291-L293)) is **still to do** — now part of the
      "Classes, fields, methods & parameters" bullet below, not a separate stage.
- [X] Implement `printTAC`: for each method, for each block, print the label, then one line per quadruple:

      ```cpp
      void IntermediateRepresentation::printTAC() {
          for (MethodIR* m : methods) {
              cout << m->name << ":\n";
              for (BasicBlock* b : m->basicBlocks) {
                  cout << b->label << ":\n";
                  for (auto& in : b->instructions)
                      cout << "  " << in.op << " " << in.arg1 << " " << in.arg2 << " -> " << in.result << "\n";
              }
          }
      }
      ```
- [X] **Verify:** `./compiler test_files/valid/test1.cpm` prints TAC and writes `IR_tree.dot`;
      `make IR_tree` renders it. For test1 you should see a single block of `MUL/ADD/SUB/POW/DIV` temps, an
      `ASSIGN … -> result`, a `PRINT result`, and `RETURN 0`.

#### Stage 2 (continued) — full-language expressions & statements *(folded in from the old Stage 6)*

These are still per-statement / per-expression lowering — the same two functions — so they belong here,
not in a separate "higher grade" stage. The type/class context they rely on is decision #4's two members.

- [X] **Type/class context (decision #4):** `classNames` (a `set<string>`) and `varTypes`
      (`unordered_map<string,string>`) are members in [ir.hh:48-49](ir.hh#L48-L49). `generate_ir` fills
      `classNames` up front ([ir.cc:315-317](ir.cc#L315-L317)); the declaration cases record
      `varTypes[name] = typeNode->value`. ⚠ See bug #3 — the `Assign` case writes a spurious `varTypes[""]`
      and must be cleaned up.
- [X] **`ArrayAccess` (read):** done at [ir.cc:85-91](ir.cc#L85-L91) — recurse array + index, `newTemp`,
      `emit("ARRAY_LOAD", arr, idx, t)`, return the temp.
- [X] **Array store (write):** done in the `Assign` case at [ir.cc:149-152](ir.cc#L149-L152) — when the lhs
      is an `ArrayAccess`, `emit("ARRAY_STORE", arr, idx, rhs)` (all three quadruple fields).
- [X] **`LengthOf`:** the Option-A one-liner (§1.5) at [ir.cc:121-125](ir.cc#L121-L125) —
      `emit("ARRAY_LEN", node->value, "", t)`.
- [X] **`CallMethod` (both forms):** done at [ir.cc:97-119](ir.cc#L97-L119). One-child form disambiguates
      construction (`NEW_OBJECT`) vs self-call (`CALL`) via `classNames`; two-child form passes the receiver
      as an implicit trailing `this` arg.
- [X] **`Array` literal / creation (`NEW_ARRAY`):** done at [ir.cc:93-105](ir.cc#L93-L105). The node is
      `[baseType, Arguments]` — count the element expressions, `emit("NEW_ARRAY", count, "", t)`, then loop
      and `emit("ARRAY_STORE", t, index, value)` for each element to populate it. Verified against
      [test5.cpm:2](test_files/valid/test5.cpm#L2)'s 14-element float literal: `NEW_ARRAY 14 -> t0` followed
      by `ARRAY_STORE t0 0 -> 5.0`, `ARRAY_STORE t0 1 -> 6.0`, … in order.
- [X] **Classes, fields, methods & parameters.** All four tasks done:
      1. **Fields collected per class** — `classFields` (`unordered_map<string, set<string>>`,
         [ir.hh:51](ir.hh#L51)) is filled in the `generate_ir` class loop ([ir.cc:324-333](ir.cc#L324-L333)),
         mirroring `classNames`.
      2. **`currentClass`** ([ir.hh:47](ir.hh#L47)) is set to the class name before lowering each of its
         methods, and cleared (`""`) for `Main method` ([ir.cc:346-358](ir.cc#L346-L358)).
      3. **Parameters bound** ([ir.cc:308-313](ir.cc#L308-L313)): each `Parameter` records
         `varTypes[name] = type`; an implicit `varTypes["this"] = currentClass` is added for class methods
         (the grammar has no `this` keyword, so this is the lowering's own convention — the receiver arrives
         as a trailing `PARAM`/`CALL` argc+1, per the `CallMethod` 2-child case).
      4. **Bare names resolve to fields**: `generateExpression`'s `ID` case ([ir.cc:61-68](ir.cc#L61-L68))
         emits `GET_FIELD this <name> -> t` when the name isn't a known local/param but is a field of
         `currentClass`; `generateStatement`'s `Assign` case ([ir.cc:171-178](ir.cc#L171-L178)) mirrors this
         with `SET_FIELD this <name> <value>`. **A local always shadows a field** (checks `varTypes` first).
- [X] **Verify (full-language IR):** ran all of `test1`–`test8` — all compile and produce IR with no errors.
      `test8`'s `Counter` class confirms field resolution end-to-end: `init` → `SET_FIELD this value -> v`;
      `inc` (`value := value + 1`) → `GET_FIELD this value -> t5` / `ADD t5 1 -> t6` / `SET_FIELD this value
      -> t6`; `get` (`return value`) → `GET_FIELD this value -> t7` / `RETURN t7`. `main` shows `NEW_ARRAY`/
      `ARRAY_STORE`, `NEW_OBJECT Calculator`/`NEW_OBJECT Counter`, and `CALL sumArray 2` with the receiver
      passed as the trailing `PARAM` — all correctly wired. No bare `LOAD`/`ASSIGN` leaks through for field
      names.

### Stage 3 — Control flow (if / if-else / for / break / continue)

**Goal:** split the block graph at branches/loops, wiring labels **and** `successors`/`predecessors`.

**Files:** [ir.cc](ir.cc) — the control-flow cases of `generateStatement`.

**Status: all of Stage 3 is implemented** ([ir.cc:179-273](ir.cc#L179-L273)). The snippets below match the
code, with one naming difference: the code calls the bare **`newBlock()`** (every block is `BB`-prefixed —
see Stage 1), so where the snippets write `newBlock("L" + newLabel())` the real code is just `newBlock()`.
Jump TAC carries the target block's `->label` (e.g. `BB4`) either way.

General pattern with your model: at a branch, `newBlock()` the targets, emit the jump TAC
(`IF_FALSE cond Lfalse`, `GOTO Ljoin`), call `addEdge` for each possible successor, then `setCurrentBlock`
and recurse the appropriate sub-statements into each block.

The rule held throughout: **emit the jump TAC and call `addEdge` together**, so labels and edges never
drift apart. The label that goes into the jump is just the target block's `->label`.

- [X] **`IfStatement`** (no else, [ir.cc:179-195](ir.cc#L179-L195)): children are `[Condition,
      then-statement]`; the then-statement may be a bare statement or a `StatementBlock` (your
      `generateStatement` handles both):

      ```cpp
      if (type == "IfStatement") {
          string cond = generateExpression(node->children.front()->children.front()); // unwrap Condition
          BasicBlock* thenBlk = newBlock("L" + newLabel());
          BasicBlock* joinBlk = newBlock("L" + newLabel());

          emit("IF_FALSE", cond, "", joinBlk->label);   // false → skip the body
          addEdge(currentBlock, thenBlk);
          addEdge(currentBlock, joinBlk);

          setCurrentBlock(thenBlk);
          generateStatement(node->children.back());     // the then-statement
          emit("GOTO", "", "", joinBlk->label);
          addEdge(currentBlock, joinBlk);                // currentBlock = where the body ended

          setCurrentBlock(joinBlk);
          return;
      }
      ```
- [X] **`IfElseStatement`** (its own node, children `[Condition, ThenBody, ElseBody]` — unwrap each):

      ```cpp
      if (type == "IfElseStatement") {
          auto it = node->children.begin();
          Node* condW = *it++; Node* thenW = *it++; Node* elseW = *it;
          string cond = generateExpression(condW->children.front());

          BasicBlock* thenBlk = newBlock("L" + newLabel());
          BasicBlock* elseBlk = newBlock("L" + newLabel());
          BasicBlock* joinBlk = newBlock("L" + newLabel());

          emit("IF_FALSE", cond, "", elseBlk->label);
          addEdge(currentBlock, thenBlk); addEdge(currentBlock, elseBlk);

          setCurrentBlock(thenBlk);
          generateStatement(thenW->children.front());    // unwrap ThenBody
          emit("GOTO", "", "", joinBlk->label); addEdge(currentBlock, joinBlk);

          setCurrentBlock(elseBlk);
          generateStatement(elseW->children.front());    // unwrap ElseBody
          emit("GOTO", "", "", joinBlk->label); addEdge(currentBlock, joinBlk);

          setCurrentBlock(joinBlk);
          return;
      }
      ```
- [X] **`ForStatement`** ([ir.cc:227-259](ir.cc#L227-L259)): **dispatch children by `type`** (init/cond
      optional — never index by position). `Initilization` runs once in the current block; the condition
      guards the loop in its own block. ⚠ **Bug #1 lives here:** the code checks `"Initialization"`, but the
      grammar emits `"Initilization"` ([parser.yy:342](parser.yy#L342)) — fix the spelling or every loop's
      init is dropped:

      ```cpp
      if (type == "ForStatement") {
          Node *init=nullptr,*cond=nullptr,*update=nullptr,*body=nullptr;
          for (Node* ch : node->children) {                       // variable child set
              if      (ch->type == "Initilization") init   = ch->children.front();
              else if (ch->type == "Condition")     cond   = ch->children.front();
              else if (ch->type == "Update")        update = ch->children.front();
              else if (ch->type == "LoopBody")      body   = ch->children.front();
          }
          if (init) generateStatement(init);

          BasicBlock* condBlk  = newBlock("L" + newLabel());
          BasicBlock* bodyBlk  = newBlock("L" + newLabel());
          BasicBlock* afterBlk = newBlock("L" + newLabel());

          emit("GOTO", "", "", condBlk->label); addEdge(currentBlock, condBlk);

          setCurrentBlock(condBlk);
          if (cond) emit("IF_FALSE", generateExpression(cond), "", afterBlk->label);
          addEdge(condBlk, bodyBlk); addEdge(condBlk, afterBlk);

          loopBlocks.push({afterBlk, condBlk});                   // {break target, continue target}
          setCurrentBlock(bodyBlk);
          if (body)   generateStatement(body);
          if (update) generateStatement(update);                  // update at the body's bottom
          emit("GOTO", "", "", condBlk->label); addEdge(currentBlock, condBlk);
          loopBlocks.pop();

          setCurrentBlock(afterBlk);
          return;
      }
      ```
- [X] **`Break`/`Continue`:** keep `stack<pair<BasicBlock*,BasicBlock*>> loopBlocks;` as a private member
      (pushed/popped by `ForStatement` above). Each jumps to the loop's after-block / cond-block:

      ```cpp
      if (type == "Break")    { auto t = loopBlocks.top().first;  emit("GOTO","","",t->label); addEdge(currentBlock,t); return; }
      if (type == "Continue") { auto t = loopBlocks.top().second; emit("GOTO","","",t->label); addEdge(currentBlock,t); return; }
      ```
- [X] **Verify:** the `.dot` for [test_files/valid/test3.cpm](test_files/valid/test3.cpm) (for-loop) and
      [test_files/valid/test4.cpm](test_files/valid/test4.cpm) (for + if) shows correct branch edges and a
      single join per branch (cond→body, cond→after, body→cond back-edge; the `if` inside test4 adds a
      then/join diamond).

### Stage 4 — Bytecode generation & serialization

**Goal:** lower the CFG to your stack-bytecode instruction set and write a readable `bytecode.txt`.

**Files:** [ir.cc](ir.cc) (a new `generateByteCode` + `emitBytecode`); see §4 for the instruction set.

- [ ] **Lowering rule (post-order = stack pushes):** each TAC quadruple `{op,arg1,arg2,result}` becomes
      *load arg1 → load arg2 → emit op → store result*. "Load an operand" = push it: a literal pushes with
      `PUSH_INT/FLOAT/BOOL`, a name (variable/temp) pushes with `LOAD name`. A helper decides which:

      ```cpp
      // "is this operand a literal, and which kind?" — drives PUSH vs LOAD
      static bool isInt(const string& s)   { return !s.empty() && s.find_first_not_of("-0123456789")==string::npos; }
      static bool isFloat(const string& s) { return s.find('.') != string::npos && isInt(s.substr(0, s.find('.'))); }

      void emitLoad(std::ofstream& out, const string& a) {
          if (a.empty()) return;
          if (isInt(a))               out << "PUSH_INT "   << a << "\n";
          else if (isFloat(a))        out << "PUSH_FLOAT " << a << "\n";
          else if (a=="true"||a=="false") out << "PUSH_BOOL " << a << "\n";
          else                        out << "LOAD " << a << "\n";   // a variable or temp
      }
      ```
      Then lower each quadruple. The binary-op names (`ADD`,`SUB`,…,`LT`,…) are **identical** in TAC and
      bytecode, so they need no mapping; only a few ops have special shapes:

      ```cpp
      for (auto& in : b->instructions) {
          const string& op = in.op;
          if      (op == "GOTO")     { out << "JMP " << in.result << "\n"; }
          else if (op == "IF_FALSE") { emitLoad(out, in.arg1); out << "JMP_FALSE " << in.result << "\n"; }
          else if (op == "ASSIGN")   { emitLoad(out, in.arg1); out << "STORE " << in.result << "\n"; }
          else if (op == "PRINT")    { emitLoad(out, in.arg1); out << "PRINT\n"; }
          else if (op == "READ")     { out << "READ\nSTORE " << in.arg1 << "\n"; }
          else if (op == "RETURN")   { emitLoad(out, in.arg1); out << "RETURN\n"; }
          else if (op == "NOT")      { emitLoad(out, in.arg1); out << "NOT\nSTORE " << in.result << "\n"; }
          else { emitLoad(out, in.arg1); emitLoad(out, in.arg2); out << op << "\nSTORE " << in.result << "\n"; }
      }
      ```
- [ ] **Lower the call/object/array ops too** (folded in from the old Stage 6 — they're just more quadruple
      shapes). The IR already emits these, so the bytecode writer must handle them:

      ```cpp
      else if (op == "PARAM")       { emitLoad(out, in.arg1); out << "PARAM\n"; }
      else if (op == "CALL")        { out << "CALL " << in.arg1 << " " << in.arg2 << "\nSTORE " << in.result << "\n"; }
      else if (op == "NEW_OBJECT")  { out << "NEW_OBJECT " << in.arg1 << "\nSTORE " << in.result << "\n"; }
      else if (op == "NEW_ARRAY")   { emitLoad(out, in.arg1); out << "NEW_ARRAY\nSTORE " << in.result << "\n"; }
      else if (op == "ARRAY_LOAD")  { emitLoad(out, in.arg1); emitLoad(out, in.arg2); out << "ARRAY_LOAD\nSTORE " << in.result << "\n"; }
      else if (op == "ARRAY_STORE") { emitLoad(out, in.arg1); emitLoad(out, in.arg2); emitLoad(out, in.result); out << "ARRAY_STORE\n"; }
      else if (op == "ARRAY_LEN")   { emitLoad(out, in.arg1); out << "ARRAY_LEN\nSTORE " << in.result << "\n"; }
      else if (op == "GET_FIELD")   { emitLoad(out, in.arg1); out << "GET_FIELD " << in.arg2 << "\nSTORE " << in.result << "\n"; }
      else if (op == "SET_FIELD")   { emitLoad(out, in.arg1); emitLoad(out, in.result); out << "SET_FIELD " << in.arg2 << "\n"; }
      ```
      (Field/`this` operand layout depends on how Stage 2's field bullet emits `GET_FIELD`/`SET_FIELD`; keep
      the writer and that emit in sync.) `RETURN` already lowers above; emit `HALT` only at the end of `main`.
- [ ] Walk the blocks **in creation order** (`method->basicBlocks`), printing a `label:` marker then the
      lowered instructions for each. Iterating that vector visits every block **exactly once**, which
      satisfies the "don't re-emit a block" requirement without a separate visited set (you'd only need a
      visited set if you instead did a DFS from the entry block). The `GOTO`/`IF_FALSE` you already emitted
      carry the labels, so control flow is preserved; just make sure `main` ends in a `HALT`.
- [ ] **`emitBytecode`:** wrap the walk in the §4 text format — a header line, a `method <name> <argc>`
      line per method, the labelled instructions, and a terminator. For a tiny `x := 2 + 3  print(x)`:

      ```text
      CPMBC v1            <- header (your magic string)
      method main 0       <- name + arg count
      BB0:
      PUSH_INT 2
      PUSH_INT 3
      ADD
      STORE t0
      LOAD t0
      STORE x
      LOAD x
      PRINT
      PUSH_INT 0
      RETURN
      HALT
      end                 <- terminator
      ```
- [ ] **Verify:** `bytecode.txt` for `test1.cpm` is hand-traceable and matches the TAC line-for-line
      (each `ADD/MUL/…` quadruple expands to its load/load/op/store quartet).

### Stage 5 — The bytecode interpreter (separate binary)

**Goal:** a standalone program that loads `bytecode.txt` and executes it on a data stack + a call stack.

**Files:** new `interpreter.hh`, `interpreter.cc` (built by the `interpreter:` target from Stage 0).

- [ ] **Runtime value + instruction + frame types.** A `Value` is *runtime* data (not the TAC strings).
      `Instr` is one parsed line; `Method` bundles its code with its `label → index` map; `Frame` is one
      call's state:

      ```cpp
      struct Value { enum { INT, FLOAT, BOOL, ARRAY, OBJ } tag; long i=0; double f=0; bool b=false;
                     shared_ptr<vector<Value>> arr; shared_ptr<map<string,Value>> obj; }; // heap refs for arrays/objects
      struct Instr { string op; vector<string> args; };
      struct Method { string name; int argc; vector<Instr> code; map<string,int> labels; };
      struct Frame  { Method* m; int pc; map<string,Value> locals; };   // name-keyed locals (decision #3)

      Value mkInt(long v)  { Value x; x.tag=Value::INT;  x.i=v; return x; }
      Value mkBool(bool v) { Value x; x.tag=Value::BOOL; x.b=v; return x; }
      ```
- [ ] **Loader:** read & verify the header, then per method read lines. A line ending in `:` records a
      label; otherwise split into opcode + operands. Store methods in a `map<string,Method>`:

      ```cpp
      string line;  Method* cur=nullptr;
      while (getline(in, line)) {
          if (line.empty()) continue;
          if (line.rfind("method ",0)==0) { /* parse name+argc */ cur=&methods[name]; cur->name=name; cur->argc=argc; continue; }
          if (line=="end") { cur=nullptr; continue; }
          if (line.back()==':') { cur->labels[line.substr(0,line.size()-1)] = cur->code.size(); continue; }
          istringstream ss(line); Instr ins; ss >> ins.op;
          for (string a; ss >> a; ) ins.args.push_back(a);
          cur->code.push_back(ins);
      }
      ```
- [ ] **Dispatch loop:** index `fr.m->code[fr.pc]` and branch on `op`. Jumps set `pc` from the label map;
      everything else falls through with `pc++`. Give it an **explicit error default** for unknown opcodes,
      and parse floats with `stod` (not `stoi`):

      ```cpp
      auto pop = [&](){ Value v = ds.top(); ds.pop(); return v; };
      stack<Value> ds;  Frame fr{ &methods["main"], 0, {} };
      while (true) {
          Instr& in = fr.m->code[fr.pc];  const string& op = in.op;
          if      (op=="PUSH_INT")   { ds.push(mkInt(stol(in.args[0])));            fr.pc++; }
          else if (op=="PUSH_FLOAT") { Value v; v.tag=Value::FLOAT; v.f=stod(in.args[0]); ds.push(v); fr.pc++; }
          else if (op=="PUSH_BOOL")  { ds.push(mkBool(in.args[0]=="true"));         fr.pc++; }
          else if (op=="LOAD")       { ds.push(fr.locals[in.args[0]]);              fr.pc++; }
          else if (op=="STORE")      { fr.locals[in.args[0]] = pop();               fr.pc++; }
          else if (op=="ADD")        { Value b=pop(),a=pop(); ds.push(addValues(a,b)); fr.pc++; } // promotes int→float
          else if (op=="LT")         { Value b=pop(),a=pop(); ds.push(mkBool(asNum(a)<asNum(b))); fr.pc++; }
          // … SUB MUL DIV POW AND OR NOT GT LEQ GEQ EQ NE follow the same pop-2 / pop-1 shape …
          else if (op=="JMP")        { fr.pc = fr.m->labels[in.args[0]]; }
          else if (op=="JMP_FALSE")  { if(!pop().b) fr.pc = fr.m->labels[in.args[0]]; else fr.pc++; }
          else if (op=="PRINT")      { printValue(pop());                           fr.pc++; }
          else if (op=="HALT")       { break; }                         // end of main
          else { cerr << "unknown opcode: " << op << "\n"; exit(1); }   // explicit error default
      }
      ```
      *(`DIV` honors §1.6: if both operands are INT, do integer division; otherwise float.)*
- [ ] **Calls, returns & recursion** (folded in from the old Stage 6 — needed by `test5`–`test8` and any
      recursive program). Keep an activation `stack<Frame> callStack;`. `PARAM` stashes the next argument;
      `CALL` builds a fresh callee `Frame` (its own `locals` — this is what makes recursion automatic), binds
      the popped args to the callee's parameter names, pushes the caller, and switches frames; `RETURN`
      restores the caller and leaves the result on the data stack:

      ```cpp
      else if (op=="PARAM")  { args.push_back(pop()); fr.pc++; }        // collect call arguments
      else if (op=="CALL")   {
          Frame callee{ &methods[in.args[0]], 0, {} };
          int argc = stoi(in.args[1]);
          // bind the last `argc` collected args to the callee's parameter names, then clear `args`
          callStack.push(fr); fr = callee;                             // switch to the new frame
      }
      else if (op=="RETURN") {
          Value rv = ds.empty() ? Value{} : pop();
          if (callStack.empty()) break;                                // RETURN from main → stop
          fr = callStack.top(); callStack.pop(); ds.push(rv); fr.pc++; // resume caller, result on stack
      }
      ```
      *(Parameter names come from each method's definition. The simplest scheme: emit a `params a b c` line
      after `method <name> <argc>` in Stage 4 so the loader records them, then `CALL` binds positionally.)*
- [ ] **Arrays & objects** (heap values, also from the old Stage 6): `NEW_ARRAY` pops a size and pushes an
      `ARRAY` Value; `ARRAY_LOAD`/`ARRAY_STORE` index it; `ARRAY_LEN` pushes its size. `NEW_OBJECT` pushes an
      `OBJ` Value (a `map<string,Value>`); `GET_FIELD`/`SET_FIELD` read/write a named field on the receiver
      popped from the stack. Using `shared_ptr` (above) gives reference semantics for free.
- [ ] **`main(argc,argv)`:** `if (argc<2) …usage…;` open `argv[1]`, check the header line equals your magic
      string, load into `methods`, then run from `methods["main"]` as above.
- [ ] Add an optional **trace mode** (e.g. `--trace`): before each dispatch, print `pc`, the opcode, and
      the data-stack depth + current locals. Invaluable when output is wrong and you need to see where.
- [ ] **Verify full pipeline:**
      `make && ./compiler test_files/valid/test1.cpm && make interpreter && ./interpreter bytecode.txt`
      → output matches the program's intent. **This is the graded Option-1 minimum.**

### Stage 6 — *dissolved (was: "full language for higher grades")*

We are implementing the whole language, so this is **not** a separable add-on stage. Its subgoals have been
moved into the stage that owns the relevant layer; nothing here is dropped:

| Old Stage-6 subgoal | Now lives in |
|---|---|
| Type/class context (`classNames`, `varTypes`) | **Stage 2 (continued)** — done |
| `CallMethod` (both forms), arrays, `LengthOf` | **Stage 2 (continued)** — done (✅ with bug #2 to fix) |
| `Array` literal → `NEW_ARRAY` | **Stage 2 (continued)** — to do |
| Classes/fields/methods + parameter binding + `this` | **Stage 2 (continued)** — clarified, to do |
| Bytecode for `CALL`/`PARAM`/`NEW_OBJECT`/fields/arrays | **Stage 4** — to do |
| Interpreter `CALL`/`RETURN`/recursion + heap arrays/objects | **Stage 5** — to do |

**Verify the full language** (the old Stage-6 acceptance test, still required): run `test5`–`test8`
([test_files/valid/test5.cpm](test_files/valid/test5.cpm)–[test8.cpm](test_files/valid/test8.cpm)) and a
small recursive program (e.g. factorial) end-to-end; turn on the interpreter's trace mode if output
disagrees. `printTAC`/`.dot` should show `ARRAY_*`, `CALL`, `NEW_OBJECT`, and `GET_FIELD`/`SET_FIELD` in
the right places, and a recursive call should produce nested frames.

**Suggested first milestone (vertical slice):** Stages 0 → 1 → 2 (test1 subset) → 4 → 5 against
`test1.cpm` only — skip control flow and the array/call/field expressions. That gives a working
`compiler → bytecode.txt → interpreter` loop and the graded minimum; control flow (rest of Stage 3, already
implemented) and the full-language expressions/opcodes are incremental additions on top.

---

## 4. Your bytecode instruction set (document this — the assignment requires it)

A Java-like **stack machine**. Operands are popped/pushed on the data stack; locals are addressed by
name (decision #3). Jumps name a label resolved to an instruction index at load time.

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
| `CALL` | name, argc | call a method/self-method with `argc` args |
| `NEW_OBJECT` | className | construct, push reference |
| `GET_FIELD` / `SET_FIELD` | fieldName | object field read/write |
| `NEW_ARRAY` | — / size | allocate array, push reference |
| `ARRAY_LOAD` / `ARRAY_STORE` | — | indexed read/write (array + index on stack) |
| `ARRAY_LEN` | — | push array length |
| `PRINT` / `READ` | — | I/O on top of stack |
| `RETURN` | — | pop frame, push return value into caller |
| `HALT` | — | stop (end of `main`) |

**Text file format (keep it simple and round-trippable):** a header line (e.g. a magic string), then per
method a `method <name> <argc>` line, its instructions one per line (`label:` on its own or prefixing an
instruction), ending with a terminator. Generate and parse with matching routines; diff a known-good
`test1.cpm` output early so the format stays consistent.

> *Reference (optional):* if you want to see one concrete file format and dispatch loop, Filip's
> [filips/readme](filips/readme) and [filips/interpreter.cpp](filips/interpreter.cpp) are examples — but
> his opcodes, his "no labels / follow block pointers" jump model, and his integer slots differ from
> yours, so design your own format to match the table above rather than reusing his.

---

## 5. Conceptual notes & gotchas (the tricky parts)

### Why the lowering works

- **Stack lowering.** TAC is three-address (`t2 := t0 + t1`); the target is a stack machine. Rule: to
  evaluate `a op b`, **push a, push b, emit op** (op pops two, pushes one). An expression tree becomes a
  post-order traversal — load operands, then the op, then store the result.
- **Jumps = labels + edges.** In your model a jump is a TAC op carrying a label *and* a CFG edge. Keep the
  two in sync (always `addEdge` when you emit a jump or fall through). Debug control flow via the `.dot`.
  At bytecode time, labels become instruction indices; at run time, a jump just sets the pc.
- **Scoping / locals.** C+- has lexical block scopes, but a method's locals can be flattened into one
  name-keyed store per call frame. Recursion stays correct because each `CALL` gets a fresh frame. ⚠
  Caveat: this assumes **no name collisions after flattening** — a variable shadowed in a nested block
  would clash. For the test files this doesn't occur; if you hit it, mangle inner names (e.g. suffix a
  block id). Ensure `newTemp` names (`t0,t1,…`) can never collide with user identifiers.

### Pitfalls specific to *your* code

1. **`true`/`false` carry truth in `type`, not `value`.** [parser.yy:286-287](parser.yy#L286-L287) builds
   `Node("true","")` — read `node->type`, never `node->value`, for booleans.
2. **`LengthOf` has no children; the operand is only its `value` string.**
   [parser.yy:259-262](parser.yy#L259-L262) copies the operand expression's `value`. For a plain `ID`
   (`list.length`) that's the name — fine. For `f(x).length` or `a[i].length` the operand is *lost at parse
   time*. **Decided (§1.5): Option A** — accept the limitation, read `node->value` as the array name, leave
   the grammar untouched. The only real fix (Option B: attach the operand as a child) would also require
   editing semantic analysis ([semanalysis.cc:237](semanalysis.cc#L237)), with no test-visible benefit.
3. **`IfElseStatement` is a separate node with `ThenBody`/`ElseBody`.** Don't try to fold else into
   `IfStatement` the way some designs do — handle it as its own case and unwrap the bodies.
4. **`ForStatement` children are a variable set.** Init and condition are optional
   ([parser.yy:341-364](parser.yy#L341-L364)); update is always present. **Dispatch children by `type`,
   never by fixed index** (e.g. test7's `for ( , cont , … )` has no `Initilization`).
5. **Wrapper nodes must be unwrapped:** `Condition`, `ThenBody`, `ElseBody`, `LoopBody`, `Initilization`,
   `Update`, `ReturnType` each wrap the real node in a single child.
6. **Two program-root shapes.** `var_list class_list entry` (globals + classes + `Main method`) vs. the bare
   `stmtBl` form (a single `StatementBlock`, no `Main method`). The test files use `main()`, but make
   `generate_ir` tolerate a top-level `StatementBlock` too.
7. **`CallMethod` is overloaded.** One-child form is *either* a self-call *or* a constructor — disambiguate
   with the class-name set (Stage 2's `CallMethod` handling — already done). Two-child form is `obj.method(...)`.
8. **`Method` child order is `Parameters`, `ReturnType`, `StatementBlock`** ([parser.yy:167-183](parser.yy#L167-L183));
   `Main method`'s only child is its body block. Read these from your own grammar, not from any other layout.
9. **Division and numeric promotion (settled — see §1.6).** Your semantic analysis already fixes the rule
   ([semanalysis.cc:254-263](semanalysis.cc#L254-L263)): float if either operand is float, else int. So
   `int / int` is **truncating integer division** (test4's `(n / i) * i = n` depends on it) and
   `int ^ int → int` (test1's `2 ^ (4*2)`); a float operand promotes to float division. Keep codegen and
   the interpreter consistent with this.
10. **Interpreter robustness.** Give the opcode parser an explicit error path for unknown opcodes, and use
    the right numeric parse for floats (`stof`, not `stoi`). The text format is whitespace/marker-sensitive —
    parse with the same conventions you emit.
