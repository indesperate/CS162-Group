#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "userprog/process.h"
#include "userprog/syscall-func.h"

static void syscall_handler(struct intr_frame*);

void syscall_init(void) { intr_register_int(0x30, 3, INTR_ON, syscall_handler, "syscall"); }

static void syscall_handler(struct intr_frame* f) {
  uint32_t* args = ((uint32_t*)f->esp);
  check_user_ptr(args);

  /*
   * The following print statement, if uncommented, will print out the syscall
   * number whenever a process enters a system call. You might find it useful
   * when debugging. It will cause tests to fail, however, so you should not
   * include it in your final submission.
   */

  /* printf("System call number: %d\n", args[0]); */

  switch (args[0]) {
    case SYS_HALT: {
      sys_halt();
    } break;
    case SYS_EXIT: {
      int status = args[1];
      sys_exit(status);
    } break;
    case SYS_CREATE: {
      const char* file = (void*)args[1];
      unsigned initial_size = args[2];
      f->eax = sys_create(file, initial_size);
    } break;
    case SYS_REMOVE: {
      const char* file = (void*)args[1];
      f->eax = sys_remove(file);
    } break;
    case SYS_OPEN: {
      const char* file = (void*)args[1];
      f->eax = sys_open(file);
    } break;
    case SYS_FILESIZE: {
      int fd = args[1];
      f->eax = sys_filesize(fd);
    } break;
    case SYS_READ: {
      int fd = args[1];
      void *buffer = (void*)args[2];
      unsigned size = args[3];
      f->eax = sys_read(fd, buffer, size);
    } break;
    case SYS_WRITE: {
      int fd = args[1];
      const void* buffer = (void*)args[2];
      unsigned int size = args[3];
      f->eax = sys_write(fd, buffer, size);
    } break;
    case SYS_CLOSE: {
      int fd = args[1];
      sys_close(fd);
    } break;
    case SYS_PRACTICE: {
      int i = args[1];
      f->eax = sys_practice(i);
    } break;
    default:
      break;
  }
}
