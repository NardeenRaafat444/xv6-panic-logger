

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "defs.h"

static char*
proc_state_name(enum procstate state)
{
  switch(state){
  case UNUSED:
    return "UNUSED";
  case USED:
    return "USED";
  case SLEEPING:
    return "SLEEPING";
  case RUNNABLE:
    return "RUNNABLE";
  case RUNNING:
    return "RUNNING";
  case ZOMBIE:
    return "ZOMBIE";
  default:
    return "UNKNOWN";
  }
}

void
crashctxdump(void)
{
  struct proc *p;

  printf("\n========== CRASH CONTEXT ==========\n");

  printf("CPU / hart id: %d\n", cpuid());

  printf("Supervisor CSRs:\n");
  printf(" sepc    = %p\n", (void*)r_sepc());
  printf(" scause  = %p\n", (void*)r_scause());
  printf(" stval   = %p\n", (void*)r_stval());
  printf(" sstatus = %p\n", (void*)r_sstatus());

 

  p = myproc();

  if(p == 0){
    printf("Current process: none\n");
    printf("Reason: panic happened in kernel context or before a process was running.\n");
  } else {
    printf("Current process:\n");
    printf("  pid   = %d\n", p->pid);
    printf("  name  = %s\n", p->name);
    printf("  state = %s\n", proc_state_name(p->state));
    printf("  killed = %d\n", p->killed);

    if(p->trapframe == 0){
      printf("Trapframe: none\n");
    } else {
      printf("Trapframe snapshot:\n");
      printf("  epc = %p\n", (void*)p->trapframe->epc);
      printf("  ra  = %p\n", (void*)p->trapframe->ra);
      printf("  sp  = %p\n", (void*)p->trapframe->sp);
      printf("  a0  = %p\n", (void*)p->trapframe->a0);
      printf("  a1  = %p\n", (void*)p->trapframe->a1);
      printf("  a2  = %p\n", (void*)p->trapframe->a2);
      printf("  a3  = %p\n", (void*)p->trapframe->a3);
      printf("  a4  = %p\n", (void*)p->trapframe->a4);
      printf("  a5  = %p\n", (void*)p->trapframe->a5);
      printf("  a6  = %p\n", (void*)p->trapframe->a6);
      printf("  a7  = %p\n", (void*)p->trapframe->a7);
    }
  }

  printf("========== END CRASH CONTEXT ==========\n\n");
}
