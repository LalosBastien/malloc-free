/*
** utils.c for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/git/src
** 
** Made by LALOS Bastien
** Login   <lalos_b@etna-alternance.net>
** 
** Started on  Tue Feb  6 19:22:41 2018 LALOS Bastien
** Last update Tue Feb  6 20:38:24 2018 LALOS Bastien
*/

#include "../include/malloc.h"

struct t_block  *get_block(size_t size)
{
  struct t_block        *block = first;

  while(block) {
    /* search for free block that fit size */
    if (block->is_free && block->size >= size)
      return block;
    block = block->next;
  }
  return NULL;
}

void debug()
{
  
  struct t_block  *block = first;
  printf("first block = %p, last block = %p \n", (void*)first, (void*)last);
  while(block) {
    printf("addr = %p, size = %u, is_free=%u, next=%p \n",(void*)block, (unsigned)block->size, block->is_free, (void*)block->next);
    block = block->next;
        }
}
