#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "defs.h"

#define KLOG_SIZE 4096

struct klog_buffer {
  struct spinlock lock;
  int locking;
  uint write_pos;
  uint wrapped;
  char buf[KLOG_SIZE];
};

static struct klog_buffer klog;

void
kloginit(void)
{
  initlock(&klog.lock, "klog");
  klog.locking = 1;
  klog.write_pos = 0;
  klog.wrapped = 0;
}

void
klogputc(int c)
{
  if(klog.locking)
    acquire(&klog.lock);

  klog.buf[klog.write_pos] = c;
  klog.write_pos++;

  if(klog.write_pos >= KLOG_SIZE){
    klog.write_pos = 0;
    klog.wrapped = 1;
  }

  if(klog.locking)
    release(&klog.lock);
}

void
klogdump(void)
{
  int i;
  int start;
  int count;

  consputc('\n');
  consputc('[');
  consputc('k');
  consputc('l');
  consputc('o');
  consputc('g');
  consputc(']');
  consputc('\n');

  if(klog.wrapped){
    start = klog.write_pos;
    count = KLOG_SIZE;
  } else {
    start = 0;
    count = klog.write_pos;
  }

  for(i = 0; i < count; i++){
    consputc(klog.buf[(start + i) % KLOG_SIZE]);
  }

  consputc('\n');
  consputc('[');
  consputc('/');
  consputc('k');
  consputc('l');
  consputc('o');
  consputc('g');
  consputc(']');
  consputc('\n');
}
