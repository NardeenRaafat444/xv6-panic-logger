# Person 2 - Panic Integration

## Goal

Connected the kernel log buffer to Xv6 panic handling.

## Files Modified

- `kernel/klog.c`
- `kernel/defs.h`
- `kernel/printf.c`

## What Was Added

Added `klogsetlocking(int enabled)` to control logger locking.

Modified `panic()` so that when the kernel panics, it prints:

1. A clear panic header
2. The panic message
3. The recent kernel log buffer
4. A clear ending marker

## Why Disable Logger Locking During Panic?

During a kernel panic, the system may already be in an unsafe state.

If the panic happens while a lock is held, trying to acquire another lock may cause a deadlock.

So `panic()` disables printf locking and also disables klog locking before dumping logs.

## Current Status

The kernel panic function now dumps recent kernel logs before freezing the system.

The next team member will add richer crash context information such as CPU ID, process ID, process name, and trap/register details.
