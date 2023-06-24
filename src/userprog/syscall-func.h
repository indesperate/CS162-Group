#ifndef USERPROG_SYSCALL_FUNC_H
#define USERPROG_SYSCALL_FUNC_H

#include "threads/interrupt.h"

void sys_halt(void);

void sys_exit(int status);

int sys_open(const char *file);

int sys_write(int fd, const void* buffer, unsigned size);

int sys_practice(int i);

void check_user_ptr(const void* ptr);

#endif /* userprog/syscall-func.h */