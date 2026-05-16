# Team Contributions

## Person 1

### Responsibility

Kernel circular log buffer core.

### Main Work

- Added `kernel/klog.c`.
- Implemented `kloginit()`.
- Implemented `klogputc()`.
- Implemented `klogdump()`.
- Connected kernel `printf()` output to the log buffer.
- Added logger declarations and Makefile entry.

### Importance

This created the memory structure that stores recent kernel logs.

---

## Person 2

### Responsibility

Panic integration.

### Main Work

- Modified `panic()` in `kernel/printf.c`.
- Added panic-time log dumping.
- Added locking control for panic safety.
- Ensured logs are dumped before the kernel freezes.

### Importance

This made the logger useful during an actual kernel panic.

---

## Person 3

### Responsibility

Crash context information.

### Main Work

- Added `kernel/crashctx.c`.
- Implemented `crashctxdump()`.
- Printed CPU/hart information.
- Printed current process information.
- Printed selected trap/register context.
- Connected crash context to panic output.

### Importance

This made the panic output more useful for debugging and explanation.

---

## Person 4 - Ramy

### Responsibility

Controlled panic test command.

### Main Work

- Added syscall `panic_test`.
- Added user command `panictest`.
- Registered the syscall in the kernel.
- Added user syscall wrapper.
- Added a repeatable runtime demo trigger.

### Importance

This gave the team a safe and clear way to demonstrate the panic logger.

---

## Person 5 - Malak

### Responsibility

Final documentation and validation.

### Main Work

- Added project README.
- Added demo script.
- Added testing checklist.
- Added team contribution document.
- Added verification script.
- Prepared final explanation material.

### Importance

This prepared the project for grading, discussion, and demonstration.
