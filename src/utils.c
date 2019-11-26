/*
** utils.c for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/git/src
** 
** Made by LALOS Bastien
** Login   <lalos_b@etna-alternance.net>
** 
** Started on  Tue Feb  6 19:22:41 2018 LALOS Bastien
** Last update Tue Feb 13 16:23:10 2018 LALOS Bastien
*/

#include "../include/malloc.h"

void list_block()
{
  
  struct m_data  *block = first;
  printf("\n=== Allocate memory block list ===\n\n");
  printf("first block = %p, last block = %p \n\n", (void*)first, (void*)last);
  while(block) {
    printf("addr = %p, size = %u, is_free=%u, next=%p, prev=%p \n",(void*)block, (unsigned)block->size, block->is_free, (void*)block->next, (void*)block->prev);
    block = block->next;

    if (block == first)
      return;
        }

  printf("\n====================================\n\n");
}

void print_image(FILE *fptr)
{
    char read_string[128];
 
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
}

int ascii(char *filename)
{
    FILE *fptr = NULL;
 
    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        return 1;
    }
 
    print_image(fptr);

    printf("\n");
 
    fclose(fptr);

    return 0;
}
