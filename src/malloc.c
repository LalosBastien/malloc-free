/*
** malloc.c for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/git/src
**
** Made by LALOS Bastien
** Login   <lalos_b@etna-alternance.net>
**
** Started on  Wed Jan 31 15:18:31 2018 LALOS Bastien
** Last update Thu Mar  1 21:55:41 2018 LALOS Bastien
*/

#include "../include/malloc.h"

int	insert_in_list(struct m_data *tag)
{
  if (!first)
    first = tag;
  if (last)
    {
      last->next = tag;
      tag->prev = last;
    }
  last = tag;

  return 0;
}

struct m_data	*init_tag(struct m_data *tag, size_t size, void* ptr)
{
  /* init meta data */
  tag = ptr;
  tag->size = size;
  tag->is_free = 0;
  tag->next = NULL;
  tag->prev = NULL;

  return tag;
}

struct m_data	*right_fusion(struct m_data *tag)
{
  tag->size += tag->next->size;
  if(tag->next->next != NULL)
    tag->next->next->prev = tag;

  if (last == (void *)tag->next)
    {
      tag->next = NULL;
      last = tag;
    }
  else
    tag->next = tag->next->next;

  return tag;
}

struct m_data   *left_fusion(struct m_data *tag)
{
  /* fusion actual & prev block */
  tag->size += tag->prev->size;

  if (first == (void *)tag->prev)
    {
      tag->prev = NULL;
      first = tag;
    }
  else
    {
      tag->prev = tag->prev->prev;
      tag->prev->prev->next = tag;
    }

  return tag;
}

struct m_data   *big_fusion(struct m_data *tag)
{
  /* fusion actual & next & prev block */
  tag = right_fusion(left_fusion(tag));

  return tag;
}

int	search_for_fusion(size_t size, struct m_data *tag)
{
  /* check actual & next memory block */
  if(tag->next != NULL && tag->is_free == 1)
    if((tag->size + tag->next->size) == size && tag->next->is_free == 1)
      return 0;
  /* check actual & next & prev memory block */ 
  if(tag->next != NULL && tag->prev != NULL && tag->is_free == 1)
    if((tag->size + tag->next->size + tag->prev->size) == size)
      if(tag->next->is_free == 1 && tag->prev->is_free == 1)
	return 1;

  return -1;
}

struct m_data	*search_free_block(size_t size)
{
  struct m_data	*tag;
  tag = first;

  while(tag) {
    /* search for free block that fit size */
    if (tag->is_free && tag->size == size)
      return tag;

    /* check if available fusion */
    if(search_for_fusion(size, tag) == 0)
      return right_fusion(tag);
    else if (search_for_fusion(size, tag) == 1)
      return big_fusion(tag);
    else
      tag = tag->next;
  }
  
  return NULL;
}

void	*malloc(size_t size)
{
  size_t	total_size;
  void		*ptr;
  struct m_data	*tag;

  if (!size || size == 0)
    return NULL;

  /* search for block that fit requested size. */
  tag = search_free_block(size);

  if (tag)
    {
      /* has found free or fusion block. */
      tag->is_free = 0;
      return ( ((char *)tag) + sizeof(*tag) );
    }
  else
    {
      /* no block fit requested memory -> need memory from OS. */
      total_size = sizeof(struct m_data) + size;
      ptr = sbrk(total_size);
      /* sbrk got an error */
      if (ptr == (void*) -1) {
	return NULL;
      }
      /* has requested a block that fit requested size  */
      tag = init_tag(tag, size, ptr);
      /* check list state & move the last */
      insert_in_list(tag);

      return ( ((char *)tag) + sizeof(*tag) );
    }
}
