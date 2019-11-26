/*
** realloc.c for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/lalos_b/src
** 
** Made by LALOS Bastien
** Login   <lalos_b@etna-alternance.net>
** 
** Started on  Wed Feb 28 15:38:18 2018 LALOS Bastien
** Last update Thu Mar  1 21:51:40 2018 LALOS Bastien
*/

#include "../include/malloc.h"

void    *realloc(void *ptr, size_t size)
{
  struct m_data	*tag;
  void		*new_ptr;
  void		*backup_ptr;

  /* handle errors */
  if (!ptr || !size || size <= 0)
    return NULL;

  /* get block meta datas  */
  tag = (struct m_data *)ptr - 1;
  /* init block tmp */
  backup_ptr = ptr;

  if (tag->size < size)
    {
      free(ptr);
      /* allocate requested memory size */
      new_ptr = malloc(size);

      if (new_ptr)
	{
	  /* copy datas to bigger block */
	  memcpy(new_ptr, ptr, tag->size);
	  /* populate new block */
	  ptr = new_ptr;
	}
      else
	{
	  free(new_ptr);
	  ptr = backup_ptr;
	}
    }

  return ptr;
}
