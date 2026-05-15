# Person 4 - Ramy - Panic Logger Test Trigger

## Goal

Added a controlled user command to test the Kernel Panic Logger project.

## New User Command

- panictest

## Files Modified

- kernel/syscall.h
- kernel/syscall.c
- kernel/sysproc.c
- user/user.h
- user/usys.pl
- user/panictest.c
- Makefile
- PERSON4_RAMY_TESTING_NOTES.md

## Design Idea

The project needs a clean way to demonstrate that the panic logger works.

Instead of forcing Xv6 to crash during boot, we added a user command that triggers a kernel panic only when manually executed.

## How It Works

1. The user runs panictest inside the Xv6 shell.
2. panictest calls the new syscall panic_test().
3. The kernel enters sys_panic_test().
4. sys_panic_test() calls panic().
5. The panic handler prints:
   - panic message
   - crash context information
   - recent kernel log buffer

## Why This Is Useful

This gives the team a repeatable demo command.

Normal Xv6 boot remains safe, but the panic logger can be tested whenever needed.

## Expected Demo Command

Inside Xv6:

panictest

Expected result:

- Kernel panic message appears.
- Crash context appears.
- Recent kernel logs appear.
- Xv6 stops after the panic, which is expected.
