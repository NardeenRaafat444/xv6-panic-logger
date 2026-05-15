#!/bin/sh

echo "========================================"
echo " Kernel Panic Logger Verification Script"
echo "========================================"

fail=0

check_file() {
  if [ -f "$1" ]; then
    echo "[OK] Found $1"
  else
    echo "[FAIL] Missing $1"
    fail=1
  fi
}

check_grep() {
  pattern="$1"
  file="$2"
  description="$3"

  if grep -q "$pattern" "$file"; then
    echo "[OK] $description"
  else
    echo "[FAIL] $description"
    fail=1
  fi
}

echo
echo "Checking important files..."
check_file kernel/klog.c
check_file kernel/crashctx.c
check_file user/panictest.c
check_file README_KERNEL_PANIC_LOGGER.md
check_file docs/DEMO_SCRIPT.md
check_file docs/TESTING_CHECKLIST.md
check_file docs/TEAM_CONTRIBUTIONS.md

echo
echo "Checking logger functions..."
check_grep "kloginit" kernel/klog.c "kloginit exists"
check_grep "klogputc" kernel/klog.c "klogputc exists"
check_grep "klogdump" kernel/klog.c "klogdump exists"

echo
echo "Checking crash context..."
check_grep "crashctxdump" kernel/crashctx.c "crashctxdump exists"
check_grep "cpuid" kernel/crashctx.c "CPU/hart context exists"
check_grep "myproc" kernel/crashctx.c "current process context exists"

echo
echo "Checking panic integration..."
check_grep "crashctxdump" kernel/printf.c "panic calls crashctxdump"
check_grep "klogdump" kernel/printf.c "panic calls klogdump"

echo
echo "Checking panic test syscall..."
check_grep "SYS_panic_test" kernel/syscall.h "syscall number exists"
check_grep "sys_panic_test" kernel/syscall.c "syscall registered"
check_grep "sys_panic_test" kernel/sysproc.c "syscall implementation exists"
check_grep "panic_test" user/user.h "user declaration exists"
check_grep "panic_test" user/usys.pl "user syscall wrapper exists"
check_grep "panic_test" user/panictest.c "panictest calls panic_test"

echo
echo "Checking build..."
make clean
if make; then
  echo "[OK] Build succeeded"
else
  echo "[FAIL] Build failed"
  fail=1
fi

echo
if [ "$fail" -eq 0 ]; then
  echo "Verification passed."
  exit 0
else
  echo "Verification failed."
  exit 1
fi
