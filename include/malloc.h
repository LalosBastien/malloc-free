/*
** malloc.h for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/git/include
**
** Made by LALOS Bastien
** Login   <lalos_b@etna-alternance.net>
**
** Started on  Wed Jan 31 15:23:53 2018 LALOS Bastien
** Last update Thu Mar  1 21:56:45 2018 LALOS Bastien
*/

#ifndef LIB_MALLOC_H_
#define LIB_MALLOC_H_

/* LibC includes */
#include <unistd.h>
#include <string.h>
#include <stdint.h>
/* Only for print tests */
#include <stdio.h>

struct m_data
{
  struct m_data *next;
  struct m_data *prev;
  size_t size;
  int is_free;
};

struct m_data   *first;
struct m_data   *last;

/* Memory Allocation functions */
void	*sbrk(intptr_t increment);
void	*malloc(size_t size);
void	free(void *ptr);
void	*calloc(size_t nmemb, size_t size);
void	*realloc(void *ptr, size_t size);

/* Utils functions */
void	list_block();
void	print_image(FILE *fptr);
int	ascii(char *filename);

#endif
