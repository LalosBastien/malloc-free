/*
** calloc.c for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/lalos_b/src
** 
** Made by LALOS Bastien
** Login   <lalos_b@etna-alternance.net>
** 
** Started on  Wed Feb 28 15:38:05 2018 LALOS Bastien
** Last update Thu Mar  1 21:48:15 2018 LALOS Bastien
*/

#include "../include/malloc.h"

void    *calloc(size_t nmemb, size_t size)
{
  size_t	array_size;
  void		*ptr;

  /* error handle */
  if (!nmemb || nmemb <= 0)
    return NULL;
  if (!size || size <= 0)
    return NULL;

  /* get & allocate requested size  */
  array_size = nmemb * size;
  ptr = malloc(array_size);

  if (!ptr)
    return NULL;

  return ptr;
  
}
