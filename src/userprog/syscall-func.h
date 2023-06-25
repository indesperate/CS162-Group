#ifndef USERPROG_SYSCALL_FUNC_H
#define USERPROG_SYSCALL_FUNC_H

#include "threads/interrupt.h"

/* SYS_HALT 0 */
void sys_halt(void);

/* SYS_EXIT 1 */
void sys_exit(int status);

/* SYS_OPEN 6 */
int sys_open(const char* file);

/* SYS_WRITE 9 */
int sys_write(int fd, const void* buffer, unsigned size);

/* SYS_CLOSE 12 */
void sys_close(int fd);

/* SYS_PRACTICE 13*/
int sys_practice(int i);

/* check if the user pointer is valid*/
void check_user_ptr(const void* ptr);

#endif /* userprog/syscall-func.h */