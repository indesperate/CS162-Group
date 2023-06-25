#include "syscall-func.h"
#include <stdio.h>
#include "threads/vaddr.h"
#include "threads/thread.h"
#include "userprog/pagedir.h"
#include "userprog/process.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "devices/shutdown.h"

void sys_halt(void) { shutdown_power_off(); }

void sys_exit(int status) {
  /* close all file descriptors */
  struct fd_table* fd_t = &thread_current()->pcb->fd_t;
  int i = 0, j = 0;
  for (; j < fd_t->num && i < MAX_FILES; i++) {
    if (fd_t->fd_elem[i] != NULL) {
      file_close(fd_t->fd_elem[i]);
      fd_t->fd_elem[i] == NULL;
      j++;
    }
  }
  printf("%s: exit(%d)\n", thread_current()->pcb->process_name, status);
  process_exit();
}

int sys_open(const char* input_file) {
  check_user_ptr(input_file);
  struct fd_table* fd_t = &thread_current()->pcb->fd_t;
  if (fd_t->num >= MAX_FILES) {
    return -1;
  }
  struct file* fp = filesys_open(input_file);
  if (!fp) {
    return -1;
  };
  int fd = fd_t->index;
  fd_t->fd_elem[fd_t->index] = fp;
  fd_t->num++;
  /* find the next empty node */
  for (int i = 1; i < MAX_FILES; i++) {
    fd_t->index = (fd_t->index + 1) % MAX_FILES;
    if (!fd_t->fd_elem[fd_t->index]) {
      break;
    }
  }
  /* index plus 2 as the fd to prevent 0 and 1*/
  return fd + 2;
}

int sys_write(int fd, const void* buffer, unsigned size) {
  check_user_ptr(buffer);
  if (fd == 1) {
    putbuf(buffer, size);
  }
  return size;
}

void sys_close(int fd) {
  /* restore index */
  int index = fd - 2;
  struct fd_table* fd_t = &thread_current()->pcb->fd_t;
  if (index < 0 || index >= MAX_FILES || !fd_t->fd_elem[index]) {
    sys_exit(-1);
  }
  file_close(fd_t->fd_elem[index]);
  fd_t->fd_elem[index] = NULL;
  fd_t->num--;
}

int sys_practice(int i) { return i + 1; }

void check_user_ptr(const void* ptr) {
  if (!is_user_vaddr(ptr) || !pagedir_get_page((thread_current()->pcb->pagedir), ptr)) {
    sys_exit(-1);
  }
}