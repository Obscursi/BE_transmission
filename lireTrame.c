#include <stdio.h>
#include <stdlib.h>

void affichebin(int n){
    unsigned u = (unsigned)n;   // On lit les bits 

	int compteur = 0;

    for (int i = 31; i >= 0; i--) {
        unsigned bit = (u >> i) & 1;   // On décale, puis on lit le dernier bit
        printf("%u", bit);
		compteur++;
		if (compteur%8==0){
			printf(" ");
		}
    }
    printf("\n");
}

void lireAdresse(char * adr) {
	printf("début de la lecture d'adresse (voici la trame en binaire) : ") ;

	int * trame = (int *) ch ;
	affichebin(*trame);

	int etage = ((*trame) & 4227858432) >> 26 ; 
	printf("etage   : %d\n",etage) ;

	int chambre = ((*trame) & 67043328) >> 16 ;
	printf("chambre : %d\n",chambre) ;

	int capteur = ((*trame) & 61440) >> 12 ;
	printf("capteur : %d\n",capteur) ;

	if(etage > 63 || etage <0 || chambre > 1023 || chambre < 0 || capteur > 15 || capteur < 0) {
		printf("erreur paramètres de l'adresse hors bornes\n");
		exit(2) ;
	}
	printf("fin de lecture d'adresse\n\n") ;
}

int lireType(char * oct) { //faudra sans doute check à un autre endroit
	printf("oct : %d\n", (int) (*oct)) ;
	*oct = (*oct) >> 6 ;
	int type = (int) (*oct) ;
	printf("type : %d\n", type) ;
	return(type) ;
}

int main(int argc, char ** argv) {
	(void)argc;
	(void)argv;
	
	FILE * inFile = fopen("trame.txt","r") ;
	//lireAdresse(inFile) ;
	//printf("%d",lireType(inFile)) ;
	char * ch = malloc(sizeof(char)*4) ;
	for(int i=0; i<2; i++) {
		if(fgets(ch,4,inFile)!=null) {
			switch i {
				case 0 :
					lireAdresse(ch) ;
					break ;
				case 1 :
					lireType(ch) ;
					break ;
			}
		}
	}
	
	fclose(inFile) ;
	
	return(0) ;
}
