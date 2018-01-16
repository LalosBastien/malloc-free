
/*
** main.c for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/git/src
** 
** Made by LALOS Bastien
** Login   <lalos_b@etna-alternance.net>
** 
** Started on  Tue Jan 16 12:55:45 2018 LALOS Bastien
** Last update Tue Jan 16 16:38:13 2018 LALOS Bastien
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int	brk(const void *addr );
void*	sbrk(intptr_t incr );
char	*strcpy(char *dest, const char *src);
void	perror(const char *s);
void	*memset(void *str, int c, size_t n);
char	*strerror(int errnum);
void    *malloc2(size_t size)
{
  void *p;
  p = sbrk(0);

  printf("Pointer value => %p\n", ((uint8_t*) p));

  if (sbrk(size) == (void*) -1)
    return NULL;
  return p;
}

int	main (int argc, char **argv) 
{
  int i;
  char* allocatedMem1;
  char* allocatedMem2;
  void* point;
  int out_of_memory;
  size_t size;

  out_of_memory = 1;
  size = 1;
 
  allocatedMem1 = malloc(0*sizeof(char));
  allocatedMem2 = malloc(1*sizeof(char));

  strcpy(allocatedMem1, "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20");
  allocatedMem2 = "ABCDEFGHIJKL";

  printf("pointer1=%s\n", allocatedMem1);
  printf("pointer2=%s\n", allocatedMem2);

  point= malloc(size);

  printf("Pointer value => %p\n", ((uint8_t*) point));

if (out_of_memory){
    
    strerror(errno);
    point= NULL;
  }

  if (point == NULL)
    {
      printf("ERROR : %d", errno);
      strerror(errno);
    }
  else
    memset(point, 0, size);

   printf("\n==== Arguments List  ====\n\n");
  i = 0;
  while (argv[i] != '\0') {
    if(i > 0)
      printf("%d => %s \n" ,i, argv[i]);
    ++i;
  }
  printf("\n==> Nombre d'arguments : %d\n\n", argc - 1);  

return 0;
}
