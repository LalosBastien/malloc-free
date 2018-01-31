/*
** malloc.h for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/git/include
** 
** Made by LALOS Bastien
** Login   <lalos_b@etna-alternance.net>
** 
** Started on  Wed Jan 31 15:23:53 2018 LALOS Bastien
** Last update Wed Jan 31 17:55:07 2018 LALOS Bastien
*/

#ifndef LIB_MALLOC_H_
#undef LIB_MALLOC_H_
#endif

/* CLib includes */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

/* CLib functions */
int     brk(const void *addr );
void*   sbrk(intptr_t incr );
char    *strcpy(char *dest, const char *src);
void    perror(const char *s);
void    *memset(void *str, int c, size_t n);
char    *strerror(int errnum);

/* MyLib functions */
void*	malloc(size_t size);
void*	calloc(size_t nb, size_t size);
void*	realloc(void *old, size_t newsize);
void	free(void *p);
