/*
** malloc.c for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/git/src
** 
** Made by LALOS Bastien
** Login   <lalos_b@etna-alternance.net>
** 
** Started on  Wed Jan 31 15:18:31 2018 LALOS Bastien
** Last update Wed Jan 31 17:58:07 2018 LALOS Bastien
*/

#include "../include/malloc.h"

void	*malloc(size_t size)
{
  void *p;
  p = sbrk (0);

  if (sbrk(size) == (void*) -1)
    return NULL;
  return p;
}


