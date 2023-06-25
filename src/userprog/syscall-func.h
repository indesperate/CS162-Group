#ifndef USERPROG_SYSCALL_FUNC_H
#define USERPROG_SYSCALL_FUNC_H

#include <stdbool.h>

/* SYS_HALT 0 */
void sys_halt(void);

/* SYS_EXIT 1 */
void sys_exit(int status);

/* SYS_CREATE 4 */
bool sys_create(const char* file, unsigned initial_size);

/* SYS_REMOVE 5 */
bool sys_remove(const char* file);

/* SYS_OPEN 6 */
int sys_open(const char* file);

/* SYS_FILESIZE 7 */
int sys_filesize(int fd);

/* SYS_READ 8 */
int sys_read(int fd, void *buffer, unsigned size);

/* SYS_WRITE 9 */
int sys_write(int fd, const void* buffer, unsigned size);

/* SYS_CLOSE 12 */
void sys_close(int fd);

/* SYS_PRACTICE 13*/
int sys_practice(int i);

/* check if the user pointer is valid*/
void check_user_ptr(const void* ptr);

#endif /* userprog/syscall-func.h */