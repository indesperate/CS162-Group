#include "syscall-func.h"
#include <stdio.h>
#include "threads/vaddr.h"
#include "userprog/pagedir.h"
#include "threads/thread.h"
#include "userprog/process.h"
#include "devices/shutdown.h"

void sys_halt(void) {
  shutdown_power_off();
}

void sys_exit(int status) {
  printf("%s: exit(%d)\n", thread_current()->pcb->process_name, status);
  process_exit();
}

int sys_write(int fd, const void* buffer, unsigned size) {
  check_user_ptr(buffer);
  if (fd == 1) {
    putbuf(buffer, size);
  }
  return size;
}

int sys_practice( int i) { return i + 1; }

void check_user_ptr(const void* ptr) {
  if(!is_user_vaddr(ptr) && pagedir_get_page((thread_current()->pcb->pagedir), ptr))
  {
    printf("%s: exit(%d)\n", thread_current()->pcb->process_name, -1);
    process_exit();
  }
}