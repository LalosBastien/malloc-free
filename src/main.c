/*
** main.c for Malloc in /Users/hellstasis/Documents/ETNA/Master/IDV-DEVC4/git/src
** 
** Made by LALOS Bastien
** Login   <lalos_b@etna-alternance.net>
** 
** Started on  Tue Jan 16 12:55:45 2018 LALOS Bastien
** Last update Tue Jan 16 12:55:59 2018 LALOS Bastien
*/

#include <stdlib.h>
#include <stdio.h>

int main (int argc, char **argv) {
	
	int i;
		
	printf("\n==== Arguments List  ====\n\n");
 
	i = 0;
	while (argv[i] != '\0') {
		if(i > 0)
			printf("%d => %s \n" ,i, argv[i]);
		++i;
	}
	
	printf("\n==> Nombre d'arguments : %d\n\n", argc-1);
	
	return 0;
}
