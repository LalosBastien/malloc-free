/*
** free.c for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/lalos_b/src
** 
** Made by LALOS Bastien
** Login   <lalos_b@etna-alternance.net>
** 
** Started on  Fri Feb  9 13:39:17 2018 LALOS Bastien
** Last update Thu Mar  1 22:27:36 2018 LALOS Bastien
*/

#include "../include/malloc.h"

void	remove_last()
{
  struct m_data	*tmp;
  
  tmp = first;
  
  while (tmp)
    {
      if(tmp->next == last)
	{
	  tmp->next = NULL;
	  last = tmp;
	}
      tmp = tmp->next;
    }
}

void	free(void *ptr)
{
  struct m_data	*tag;
  void		*end;

  if (!ptr)
    return;

  /* get meta-data of the block */
  tag = (struct m_data*)ptr - 1;

  /* store break address */
  end = sbrk(0);

  /* check if block is last */
  if ((char*)ptr + tag->size == end)
    {
      /* if only 1 element -> empty the list */
      if (tag->prev == NULL && tag->next == NULL)
	{
	  first = NULL;
	  last = NULL;
	}
      /* else -> browse the list to move the last */
      else
	remove_last();

      /* decrement the break to release memory to system. */
      sbrk(0 - tag->size - sizeof(struct m_data));

      return;
    }
  else
    tag->is_free = 1;

  return;
}
