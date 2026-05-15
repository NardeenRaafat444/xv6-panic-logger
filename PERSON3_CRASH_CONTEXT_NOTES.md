# Person 3 - Crash Context Information

## Goal

Added crash context information to the Kernel Panic Logger project.

## Files Modified

- `kernel/crashctx.c`
- `kernel/defs.h`
- `kernel/printf.c`
- `Makefile`
- `PERSON3_CRASH_CONTEXT_NOTES.md`

## Design Idea

When the kernel panics, the panic handler now prints useful debugging context before dumping the kernel log buffer.

## Information Printed

The crash context includes:

- CPU / hart ID
- Supervisor CSR values:
  - `sepc`
  - `scause`
  - `stval`
  - `sstatus`
- Current process information:
  - PID
  - process name
  - process state
  - killed flag
- Trapframe snapshot:
  - `epc`
  - `ra`
  - `sp`
  - `a0` to `a7`

## Why This Helps

The log buffer shows what happened before the panic.

The crash context shows where and under what execution state the panic happened.

Together, they make the panic output more useful for debugging and explanation.

## Safety Notes

The crash context function avoids acquiring process locks during panic.

During panic, the kernel may already be in an unsafe state, so the function prints best-effort information only.

## Current Status

The panic handler now prints:

1. Panic message
2. Crash context
3. Recent kernel log buffer
4. End panic marker
