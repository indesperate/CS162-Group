#include "syscall-func.h"
#include <stdio.h>
#include "threads/vaddr.h"
#include "threads/thread.h"
#include "userprog/pagedir.h"
#include "userprog/process.h"
#include "filesys/filesys.h"
#include "devices/shutdown.h"

void sys_halt(void) { shutdown_power_off(); }

void sys_exit(int status) {
  printf("%s: exit(%d)\n", thread_current()->pcb->process_name, status);
  process_exit();
}

// return file descrption that is file point muinus PHSY_BASE, plus 2 to avoid 0 and 1
int sys_open(const char* input_file) {
  check_user_ptr(input_file);
  struct file* fp = filesys_open(input_file);
  if (!fp) {
    return -1;
  }
  return (int)fp - (int)PHYS_BASE + 2;
}

int sys_write(int fd, const void* buffer, unsigned size) {
  check_user_ptr(buffer);
  if (fd == 1) {
    putbuf(buffer, size);
  }
  return size;
}

int sys_practice(int i) { return i + 1; }

void check_user_ptr(const void* ptr) {
  if (!is_user_vaddr(ptr) || !pagedir_get_page((thread_current()->pcb->pagedir), ptr)) {
    sys_exit(-1);
  }
}