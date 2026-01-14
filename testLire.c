#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
	(void)argc;
	(void)argv;
	
	FILE * inFile = fopen("trame.txt","r") ;

	char * ch = malloc(sizeof(char)*40) ;
	for(int i=0; i<50; i++) {
		if(fgets(ch,40,inFile)!=NULL) { // normalement 40 octets est plus que ce  dont a besoin par ligne
			printf("resultat fgets : %s\n",ch) ;
		}
	}
	printf("\n -------------------------------------------------------------------------------------------------------- \n");
	fclose(inFile) ;
	
	return(0) ;
}
