
/*
** main.c for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/git/src
** 
** Made by LALOS Bastien
** Login   <lalos_b@etna-alternance.net>
** 
** Started on  Tue Jan 16 12:55:45 2018 LALOS Bastien
** Last update Thu Mar  1 22:40:44 2018 LALOS Bastien
*/

#include "malloc.h"

int     main(int argc, char **argv)
{
  ascii("malloc.ascii");

  printf("1 - Allocate 4 integers");
  void *first_int = malloc(sizeof(int));
  void *second_int = malloc(sizeof(int));
  void *third_int = malloc(sizeof(int));
  void *fourth_int = malloc(sizeof(int));
  list_block();

  printf("2 - Free them");
  free(first_int);
  free(second_int);
  free(third_int);
  free(fourth_int);
  list_block();
  
  printf("3 - Allocate size of 3 integers (should reuse free space)");
  void *three_int = malloc(3 * sizeof(int));
  list_block();

  printf("4 - Free the last ptr");
  free(three_int);
  list_block();

  /////////////////////
  ascii("calloc.ascii");
    
  printf("1 - Allocate int array[50] (should be 200)");
  int *c_alloc = calloc(50, sizeof(int));
  list_block();

  printf("2 - Free the array");
  free(c_alloc);
  list_block();
  
  /////////////////////
  ascii("realloc.ascii");

  printf("1 - Allocate 80 bytes int Array");
  int *r_alloc = malloc(80);
  list_block();

  printf("2 - Reallocate 800 bytes int Array");
  realloc(r_alloc, 800);
  list_block();

  /////////////////////
  printf("=== END ===");
  
  return 0;
}
