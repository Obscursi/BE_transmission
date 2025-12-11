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

	unsigned int trame = (unsigned) atoi(adr) ;
	affichebin(trame);

	unsigned int etage = (trame & 4227858432) >> 26 ; 
	printf("etage   : %d\n",etage) ;

	unsigned int chambre = (trame & 67043328) >> 16 ;
	printf("chambre : %d\n",chambre) ;

	unsigned int capteur = (trame & 61440) >> 12 ;
	printf("capteur : %d\n",capteur) ;

	if(etage > 63 || chambre > 1023 || capteur > 15) {
		printf("erreur paramètres de l'adresse hors bornes\n");
		exit(2) ;
	}
	printf("fin de lecture d'adresse\n\n") ;
}

void lireTrame(char * ch) { //faudra sans doute check à un autre endroit
	//int oct = (int) ch[0] ;
	
	unsigned int trame = (unsigned) atoi(ch) ;
	printf("\naffichage binaire de la trame : ");
	affichebin(trame);
	printf("oct : %d\n", trame) ;
	unsigned int type = trame >> 30 ;
	unsigned int val = trame >> 24 ;
	val = val & 63 ;
	printf("type : %d\n", type) ;
	printf("valeur : %d\n", val) ;
	if(type==3) { // type 3 on est sur une grande trame donc on doit lire 2 valeurs de plus
		unsigned int min = trame >> 18 ;
		min = min & 63 ;
		unsigned int max = trame >> 12 ;
		max = max & 63 ;
		printf("min : %d\n", min) ;
		printf("max : %d\n", max) ;
	}
}


int main(int argc, char ** argv) {
	(void)argc;
	(void)argv;
	
	FILE * inFile = fopen("trame.txt","r") ;
	//lireAdresse(inFile) ;
	//printf("%d",lireType(inFile)) ;
	char * ch = malloc(sizeof(char)*11) ;
	for(int i=0; i<2; i++) {
		if(fgets(ch,11,inFile)!=NULL) {
			printf("resultat fgets : %s\n",ch) ;
			switch(i) {
				case 0 :
					lireAdresse(ch) ;
					break ;
				case 1 :
					lireTrame(ch) ;
					break ;
			}
		}
	}
	
	fclose(inFile) ;
	
	return(0) ;
}
