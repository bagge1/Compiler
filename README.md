# C+- Compiler

A compiler front-end for **C+-** (`.cpm`), a small statically-typed, object-oriented
toy language. The compiler is written in C++14 and built with the classic
**Flex + Bison** toolchain. It takes a `.cpm` source file and runs it through the
standard front-end stages — lexical analysis, parsing, AST construction, and semantic
analysis — emitting a Graphviz parse tree and reporting any lexical, syntax, or
semantic errors it finds.

An intermediate-representation (three-address code / control-flow graph) back-end is
scaffolded but not yet implemented.

---

## Table of Contents

- [The C+- Language](#the-c--language)
- [Compiler Pipeline](#compiler-pipeline)
- [Project Structure](#project-structure)
- [How the Files Work Together](#how-the-files-work-together)
- [Building](#building)
- [Running](#running)
- [Exit Codes](#exit-codes)
- [Tests](#tests)
- [Visualizing the Parse Tree](#visualizing-the-parse-tree)
- [Implementation Notes](#implementation-notes)

---

## The C+- Language

C+- is a compact OOP language. A program consists of optional global variable
declarations, optional class declarations, and a mandatory `main` entry point.

```
class Counter {
  count: int

  increment(step: int): int {
    return step + 1
  }
}

main(): int {
  volatile result: float := ( (2 ^ (4 * 2) + 10 - 2 * 6 + 1.0 / 4.0) * 2 )
  print(result)
  return 0
}
```

Key features (see [grammar.g](grammar.g) for the full EBNF reference grammar):

| Feature            | Notes |
|--------------------|-------|
| **Types**          | `int`, `float`, `boolean`, array types (`int[]`, ...), class types, and `void` |
| **Variables**      | `name : type` with optional `:= expr` initializer |
| **`volatile`**     | Marks a variable as mutable; non-volatile variables and parameters are immutable |
| **Classes**        | Fields and methods; methods called as `obj.method(args)` or `method(args)` |
| **Entry point**    | `main() : int { ... }` |
| **Control flow**   | `if/else`, `for`, `break`, `continue`, `return` |
| **I/O**            | `print(expr)`, `read(expr)` |
| **Operators**      | Arithmetic `+ - * / ^`, comparison `< > <= >= = !=`, boolean `& | !`, array index `[]`, `.length` |
| **Statement end**  | Statements are newline-terminated |

> **Note:** statements are terminated by newlines (`NEWLINE`), so line breaks are
> syntactically significant in C+-.

---

## Compiler Pipeline

Source flows through the stages below. Each stage's failure short-circuits the rest
and sets a distinct [exit code](#exit-codes).

```
 .cpm source
     │
     ▼
┌─────────────────┐   lexer.flex ──flex──► lex.yy.c
│ 1. Lexer        │   Converts characters into tokens (MAIN, ID, INT, PLUSOP, ...).
│    (Flex)       │   Reports "Lexical errors" for unrecognized characters.
└─────────────────┘
     │ tokens
     ▼
┌─────────────────┐   parser.yy ──bison──► parser.tab.cc / parser.tab.hh
│ 2. Parser       │   LALR(1) grammar. Validates syntax and, via embedded actions,
│    (Bison)      │   builds the Abstract Syntax Tree out of Node objects.
└─────────────────┘
     │ AST (root: Node*)
     ▼
┌─────────────────┐   symboltable.cc / .hh
│ 3. Symbol Table │   Walks the AST building nested scopes (global → class →
│                 │   method → block) and records variables, params, methods, classes.
└─────────────────┘
     │
     ▼
┌─────────────────┐   semanalysis.cc / .hh
│ 4. Semantic     │   Type checking, scope/declaration checks, immutability,
│    Analysis     │   return-type checks, unreachable-code detection, etc.
└─────────────────┘
     │
     ▼
┌─────────────────┐   Node::generate_tree() in Node.h
│ 5. Tree output  │   Emits tree.dot (Graphviz) for the parse tree.
└─────────────────┘
     │
     ▼
┌─────────────────┐   ir.cc / ir.hh  (SCAFFOLDED — not yet active)
│ 6. IR / CFG     │   Three-address code + basic-block control-flow graph.
│    (future)     │   Currently stubbed out and commented out in main.cc.
└─────────────────┘
```

---

## Project Structure

### Source you edit

| File              | Role |
|-------------------|------|
| [lexer.flex](lexer.flex)         | Flex specification — token patterns for the lexer |
| [parser.yy](parser.yy)           | Bison grammar — productions + AST-building actions |
| [grammar.g](grammar.g)           | Human-readable EBNF reference for the language (documentation, not compiled) |
| [Node.h](Node.h)                 | `Node` class: the AST node type, plus tree printing / Graphviz export |
| [symboltable.hh](symboltable.hh) / [symboltable.cc](symboltable.cc) | Scoped symbol table (`Scope`, `SymbolTableEntry`, `SymbolTable`) |
| [semanalysis.hh](semanalysis.hh) / [semanalysis.cc](semanalysis.cc) | `SemAnalysis` — semantic / type checking over the AST |
| [ir.hh](ir.hh) / [ir.cc](ir.cc) | Intermediate representation (TAC + CFG). Scaffolded, mostly stubbed |
| [main.cc](main.cc)               | Driver — wires the stages together and manages exit codes |
| [Makefile](Makefile)             | Build rules and the `tree` / `clean` helpers |

### Generated build artifacts (do not edit by hand)

| File | Generated from | By |
|------|----------------|----|
| `lex.yy.c`        | `lexer.flex`     | `flex` |
| `parser.tab.cc`   | `parser.yy`      | `bison` |
| `parser.tab.hh`   | `parser.yy`      | `bison` |
| `parser.tab.o`    | `parser.tab.cc`  | `g++` |
| `stack.hh`, `position.hh`, `location.hh` | `parser.yy` | `bison` |
| `compiler`        | all of the above + `*.cc` | `g++` (final executable) |
| `tree.dot`        | a compiled run   | `Node::generate_tree()` |

### Test data

| Path | Contents |
|------|----------|
| [test_files/valid/](test_files/valid/)               | Programs that should compile cleanly (`test1.cpm` … `test8.cpm`) |
| [test_files/lexical_errors/](test_files/lexical_errors/)   | Programs with illegal characters |
| [test_files/syntax_errors/](test_files/syntax_errors/)     | Programs that violate the grammar |
| [test_files/semantic_errors/](test_files/semantic_errors/) | Programs with type/scope/return/etc. errors |
| [test_files/tree_validation/](test_files/tree_validation/) | Programs for checking precedence / dangling-else tree shape |
| [aitest.cpm](aitest.cpm) | A single annotated file exercising many semantic-error categories |

---

## How the Files Work Together

A single compile is driven by [main.cc](main.cc). Walking the dependency chain:

1. **`USE_LEX_ONLY` switch.** Defined in [parser.yy](parser.yy) (`#define USE_LEX_ONLY false`).
   When `true`, `main()` calls `yylex()` directly and the lexer just prints token names —
   a handy way to debug the lexer in isolation. When `false` (the default), the full
   parser runs.

2. **Lexer ↔ Parser handshake.** [lexer.flex](lexer.flex) includes `parser.tab.hh` and
   returns Bison *symbol* objects (e.g. `yy::parser::make_INT(yytext)`), because the
   grammar uses Bison's `api.token.constructor` + `variant` value type. Each token
   carries its text as a `std::string`. Unrecognized characters set the global
   `lexical_errors` flag.

3. **Parsing + AST construction.** [parser.yy](parser.yy) productions carry embedded
   C++ actions that allocate `Node` objects (from [Node.h](Node.h)) and link them via
   `children`. The start rule assigns the finished tree to the global `Node* root`.
   Operator precedence/associativity (`%left`, `%right`, `%nonassoc`, `%prec`) resolves
   expression ambiguity, and `%prec IFELSE` handles the dangling-else case.

4. **Semantic analysis.** `main()` calls `semanalyzer.analyze()` ([semanalysis.cc](semanalysis.cc)),
   which:
   - First calls `st.build_st()` to populate the [symbol table](symboltable.cc) by
     walking `root` and creating nested scopes (`global` → class → method → `blockN`).
   - Calls `st.resetTable()` to rewind the scope cursor to the root.
   - Then `traversal(root)` re-walks the tree, re-entering the *already-built* scopes and
     running checks: type compatibility of assignments and operators, declared-before-use,
     immutability of non-`volatile` variables and parameters, boolean conditions in
     `if`/`for`, array-index and `.length` rules, method-call arity/argument types,
     return-type matching, missing returns in non-void methods, and unreachable code
     after `return`.
   - All diagnostics are printed to `stderr` as `Semantic Error at line N: ...`.

5. **Tree emission.** `root->generate_tree()` ([Node.h](Node.h)) writes `tree.dot` in
   Graphviz format.

6. **IR (future).** The `IntermediateRepresentation` calls in `main.cc` are commented
   out; [ir.cc](ir.cc) currently has the class/method/block plumbing in place but the
   per-node TAC generation bodies are empty.

The shared global state tying the stages together — `Node* root`, `yyin`, `yylineno`,
`lexical_errors` — is declared `extern` in [main.cc](main.cc) and defined in the
generated lexer/parser.

---

## Building

**Requirements:** `g++` (C++14), `flex`, `bison`, and optionally Graphviz (`dot`) for
PDF tree rendering. A POSIX-style build environment is assumed — the sources include
`<unistd.h>`/`<sys/wait.h>`, so on Windows build under WSL, MSYS2, or similar.

```sh
make
```

This runs, in order (per the [Makefile](Makefile)):

```
bison parser.yy           # → parser.tab.cc / parser.tab.hh (+ stack.hh, etc.)
flex  lexer.flex          # → lex.yy.c
g++   -c parser.tab.cc    # → parser.tab.o
g++   -o compiler  parser.tab.o lex.yy.c main.cc symboltable.cc semanalysis.cc -std=c++14
```

The result is an executable named `compiler`.

Clean all generated files:

```sh
make clean
```

---

## Running

Pass a source file as the first argument:

```sh
./compiler test_files/valid/test1.cpm
```

If no argument is given, the compiler reads from **stdin**:

```sh
./compiler < test_files/valid/test1.cpm
```

On success you'll see:

```
The compiler successfuly generated a syntax tree for the given input!

Built a parse-tree at tree.dot. Use 'make tree' to generate the pdf version.
```

Lexical, syntax, and semantic errors are printed to `stderr`.

---

## Exit Codes

Defined in [main.cc](main.cc):

| Code | Name                 | Meaning |
|------|----------------------|---------|
| 0    | `SUCCESS`            | Compiled with no errors |
| 1    | `LEXICAL_ERROR`      | Unrecognized character(s) |
| 2    | `SYNTAX_ERROR`       | Grammar violation |
| 3    | `AST_ERROR`          | Exception thrown during analysis / tree building |
| 4    | `SEMANTIC_ERROR`     | (reserved) semantic-analysis failure code |
| 139  | `SEGMENTATION_FAULT` | Crash |

---

## Tests

The [test_files/](test_files/) directory groups sample programs by expected outcome.
There is no automated test harness checked in; run files individually and inspect the
output / exit code. For example:

```sh
./compiler test_files/syntax_errors/NoMainMethod.cpm        # expect syntax error
./compiler test_files/semantic_errors/MissingReturnStatement.cpm  # expect semantic error
./compiler test_files/valid/test3.cpm                       # expect success
```

[aitest.cpm](aitest.cpm) is a single file annotated with `//@error` comments marking
each line that should trigger a specific semantic error — useful as a one-shot
regression check of the semantic analyzer.

---

## Visualizing the Parse Tree

After a successful compile, `tree.dot` is written to the project root. Render it to PDF
with Graphviz via the Makefile helper:

```sh
make tree        # runs: dot -Tpdf tree.dot -o tree.pdf
```

---

## Implementation Notes

- **AST representation.** Every node is a `Node` ([Node.h](Node.h)) with a `type` (e.g.
  `"Addition"`, `"IfStatement"`, `"Variable"`), a `value` (identifier name, literal text,
  operator symbol), a `lineno`, and a list of `children`. The whole tree hangs off the
  global `root`.

- **Scopes.** The symbol table ([symboltable.cc](symboltable.cc)) is a tree of `Scope`
  objects mirroring program nesting. `lookup` walks parent scopes for ordinary symbols;
  `lookup_method` resolves `Class.method` against the class's scope directly. Blocks get
  synthetic names (`block1`, `block2`, …). Crucially, the table is **built once** and
  then **re-traversed** during semantic analysis, with `enterScope`/`exitScope` navigating
  the existing scope tree rather than rebuilding it.

- **Immutability model.** Only `volatile` variables are assignable. Plain variables and
  all parameters are immutable, and assigning to them is a semantic error.

- **Line-number quirk.** Because statements end with `NEWLINE`, some declaration nodes are
  created with `yylineno - 1` so error messages point at the declaration's actual line.
  You'll see matching `lineno - 1` adjustments in the semantic analyzer.

- **Not yet implemented.** Intermediate representation ([ir.cc](ir.cc)): the expression/
  statement code-gen bodies are empty, and the `ir` instance plus `generate_ir` /
  `printTAC` / `writeCFG` calls are commented out in [main.cc](main.cc). The symbol-table
  print (`st.printST()`) and AST text dump (`root->print_tree()`) are also available but
  commented out — uncomment them in `main.cc` for debugging.
