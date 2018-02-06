
/*
** malloc.c for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/git/src
** 
** Made by LALOS Bastien
** Login   <lalos_b@etna-alternance.net>
** 
** Started on  Wed Jan 31 15:18:31 2018 LALOS Bastien
** Last update Tue Feb  6 21:26:36 2018 LALOS Bastien
*/

#include "../include/malloc.h"

void	*malloc(size_t size)
{
  size_t	total_size;
  void	*block;
  struct t_block	*r_block;

  if (!size)
    return NULL;

  pthread_mutex_lock(&global_malloc_lock);
  r_block = get_block(size);

  if (r_block)
    {
      /* has found free block that fit requested size. */
      r_block->is_free = 0; 
      pthread_mutex_unlock(&global_malloc_lock); 
 
      return (void*)(r_block + 1);
    }
  /* no block fit requested memory -> need memory from OS. */
  total_size = sizeof(struct t_block) + size; 
  block = sbrk(total_size); 

  /* if sbrk got an error */
  if (block == (void*) -1) {
    pthread_mutex_unlock(&global_malloc_lock); 
    return NULL; 
  }
  
  /* has requested a free block that fit requested size  */
  r_block = block; 
  r_block->size = size;
  r_block->is_free = 0;
  r_block->next = NULL;

  /* check the list */
  if (!first)
    first = r_block;
  if (last)
    last->next = r_block;
  
  last = r_block;
  pthread_mutex_unlock(&global_malloc_lock);

  return (void*)(r_block + 1);
}
