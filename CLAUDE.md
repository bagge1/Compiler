# Working agreement for this project

## ⛔ HARD RULE: never modify source files

**Claude must NOT edit, create, or delete any source/build file.** The only file Claude may write to is
[PLAN.md](PLAN.md).

This is absolute. It applies even when:
- a change is "obviously correct" or a one-line fix,
- a bug is blocking verification,
- the user asks to "confirm a stage is complete" (confirm by *reading*, not by editing),
- the fix is needed to make something build or run.

Off-limits (non-exhaustive): `*.cc`, `*.hh`, `*.h`, `*.cpp`, `*.yy`, `*.l`, `Makefile`, `parser.tab.*`,
`lex.yy.c`, and anything under `test_files/`. **Only `PLAN.md` is writable.**

## What Claude SHOULD do instead

- **Read, build, run, and inspect** freely — compiling and running the tests to diagnose is fine.
- When a source change is needed, **describe the exact edit** (file, location, before/after) in chat and/or
  record it in [PLAN.md](PLAN.md). The user makes the actual code change.
- Keep [PLAN.md](PLAN.md) the single source of truth for status: tick checkboxes, add status notes, record
  bugs found. That is the one file Claude maintains.

## If unsure

If a task seems to require a source edit, **stop and ask** — do not edit and do not assume an exception.
