# Kernel Panic Logger for Xv6

## Project Idea

This project improves Xv6 panic handling by adding a kernel panic logger.

Normally, when Xv6 reaches a fatal kernel error, it prints a panic message and stops. That basic panic output is useful, but it does not provide enough debugging information.

Our project adds:

1. A kernel circular log buffer.
2. Panic-time log dumping.
3. Crash context information.
4. A controlled user command to trigger and test the panic logger.

## Problem

When a kernel panic happens, the system may stop immediately.

Without recent logs or crash context, it is difficult to answer:

- What happened before the panic?
- Which CPU/hart was running?
- Which process was active?
- What trap/register state existed near the crash?
- How can we reproduce the panic for testing?

## Solution Overview

The solution is divided into four technical parts:

### 1. Kernel Log Buffer

A fixed-size circular buffer stores recent kernel output.

This allows the kernel to remember important messages before a panic happens.

### 2. Panic Integration

The panic handler calls the logger dump function before freezing the kernel.

This makes the recent kernel logs visible during panic.

### 3. Crash Context

The panic output includes useful information such as:

- CPU/hart ID
- current process PID
- process name
- process state
- selected RISC-V supervisor registers
- trapframe values when available

### 4. Controlled Panic Test

A user command named `panictest` intentionally triggers a panic through a syscall.

This gives the team a clean and repeatable way to demonstrate the project.

## Main Files

| File | Purpose |
|---|---|
| `kernel/klog.c` | Implements the circular kernel log buffer |
| `kernel/crashctx.c` | Prints crash context information |
| `kernel/printf.c` | Connects panic handling to crash context and log dumping |
| `kernel/sysproc.c` | Contains the controlled panic test syscall |
| `kernel/syscall.h` | Defines the syscall number for `panic_test` |
| `kernel/syscall.c` | Registers the syscall handler |
| `user/user.h` | Exposes the syscall to user programs |
| `user/usys.pl` | Generates user syscall wrapper |
| `user/panictest.c` | User command for testing panic logger |
| `Makefile` | Builds the new kernel and user files |

## Expected Demo

Run Xv6:

```sh
make qemu
