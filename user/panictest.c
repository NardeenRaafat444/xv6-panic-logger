#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  printf("panictest: starting controlled kernel panic test\n");
  printf("panictest: the kernel should now print panic logs and crash context\n");

  panic_test();

  printf("panictest: ERROR - panic_test returned unexpectedly\n");
  exit(1);
}
