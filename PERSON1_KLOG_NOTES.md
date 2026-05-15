# Person 1 - Kernel Log Buffer Core

## Goal

Implemented the first part of the Kernel Panic Logger project: the kernel log buffer core.

## Files Modified

- `kernel/klog.c`
- `kernel/defs.h`
- `kernel/main.c`
- `kernel/printf.c`
- `Makefile`

## Design Idea

The logger uses a fixed-size circular buffer inside the kernel.

The buffer stores the most recent kernel output printed through `printf()`.

## Why Circular Buffer?

The kernel cannot keep unlimited logs because memory is limited.

A circular buffer keeps the newest messages and overwrites the oldest messages when full.

## Main Functions

### `kloginit()`

Initializes the kernel log buffer and its spinlock.

### `klogputc(int c)`

Stores one character in the circular buffer.

### `klogdump()`

Prints the saved log buffer directly using `consputc()`.

## Why `klogdump()` uses `consputc()`

`klogdump()` does not use `printf()` because `printf()` now writes to the logger.

Using `printf()` inside `klogdump()` could create recursive logging behavior.

## Current Status

The kernel log buffer is initialized during boot.

Kernel `printf()` output is automatically copied into the log buffer.

The next team member will connect `klogdump()` to `panic()` so the log appears when the kernel crashes.
