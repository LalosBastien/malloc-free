/*
** malloc.h for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/git/include
** 
** Made by LALOS Bastien
** Login   <lalos_b@etna-alternance.net>
** 
** Started on  Wed Jan 31 15:23:53 2018 LALOS Bastien
** Last update Tue Feb  6 21:30:07 2018 LALOS Bastien
*/

#ifndef LIB_MALLOC_H_
#undef LIB_MALLOC_H_
#endif

/* LibC includes */
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
/* Only for debug */
#include <stdio.h>

#define ALIGN = 8;
#define align(size) (((size) + (ALIGN-1)) & ~(ALIGN-1))
#define align4(size) (((((x) -1) > >2) < <2)+4)
#define header_size (align(sizeof(size_t)))
#define usizeof(a) ((unsigned)sizeof(a))

struct t_block
{
  struct t_block *next;
  size_t size;
  int is_free;
  
};

struct t_block	*first;
struct t_block	*last;

pthread_mutex_t global_malloc_lock;

/* CLib functions */
char    *strcpy(char *dest, const char *src);
void    perror(const char *s);
void    *memset(void *str, int c, size_t n);
char    *strerror(int errnum);
int	brk(void *addr);
void	*sbrk(intptr_t increment);
int	printf(const char *format, ...);

/* MyLib functions */
void*		malloc(size_t size);
void		debug();
struct t_block	*get_block(size_t size);
