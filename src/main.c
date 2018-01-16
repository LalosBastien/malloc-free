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
