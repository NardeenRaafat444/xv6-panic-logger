# Testing Checklist - Kernel Panic Logger

## Build Tests

- [ ] `make clean` runs successfully.
- [ ] `make` runs successfully.
- [ ] No undefined reference errors.
- [ ] No implicit declaration errors.
- [ ] No Makefile errors.

## Normal Boot Tests

- [ ] `make qemu` starts Xv6.
- [ ] Xv6 prints boot messages.
- [ ] Xv6 reaches the shell.
- [ ] The shell prompt `$` appears.
- [ ] Normal boot does not trigger panic automatically.

## File Existence Tests

- [ ] `kernel/klog.c` exists.
- [ ] `kernel/crashctx.c` exists.
- [ ] `user/panictest.c` exists.
- [ ] `README_KERNEL_PANIC_LOGGER.md` exists.
- [ ] `docs/DEMO_SCRIPT.md` exists.
- [ ] `docs/TESTING_CHECKLIST.md` exists.
- [ ] `docs/TEAM_CONTRIBUTIONS.md` exists.

## Logger Integration Tests

- [ ] `kernel/printf.c` calls `klogdump()` inside `panic()`.
- [ ] `kernel/printf.c` calls `crashctxdump()` inside `panic()`.
- [ ] `kernel/defs.h` declares `klogdump()`.
- [ ] `kernel/defs.h` declares `crashctxdump()`.

## Panic Test Command Tests

- [ ] `user/panictest.c` calls `panic_test()`.
- [ ] `user/user.h` declares `panic_test()`.
- [ ] `user/usys.pl` includes `entry("panic_test")`.
- [ ] `kernel/syscall.h` defines `SYS_panic_test`.
- [ ] `kernel/syscall.c` registers `sys_panic_test`.
- [ ] `kernel/sysproc.c` implements `sys_panic_test()`.

## Runtime Panic Output Tests

After running `panictest`, output should include:

- [ ] `KERNEL PANIC`
- [ ] panic reason
- [ ] `CRASH CONTEXT`
- [ ] CPU / hart ID
- [ ] current process information
- [ ] process name `panictest`
- [ ] selected register / trap values
- [ ] recent kernel log
