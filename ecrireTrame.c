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

void afficheBinOctet(char n){
    unsigned u = (unsigned)n;   // On lit les bits 

	int compteur = 0;

    for (int i = 7; i >= 0; i--) {
        unsigned bit = (u >> i) & 1;   // On décale, puis on lit le dernier bit
        printf("%u", bit);
		compteur++;
		if (compteur%8==0){
			printf(" ");
		}
    }
    printf("\n");
}

void ecrireAdresse(int etage, int chambre, int capteur) {

	etage = etage << 26 ;
	printf("Etage    : ") ;
	affichebin(etage);

	chambre = chambre << 16 ;
	printf("Chambre  : ") ;
	affichebin(chambre);

	capteur = capteur << 12 ;
	printf("Capteur  : ") ;
	affichebin(capteur);

	int trame = etage | chambre ;
	trame = trame | capteur ;

	printf("Résultat : ");
	affichebin(trame);

	printf("\n");
	printf("Nombre correspondant à l'adresse finale : %d\n",trame) ;
	printf("adresse finie d'être construite, on sort du fichier trame.txt \n\n");

	FILE * outFile = fopen("trame.txt","w") ;
	fprintf(outFile, "%d\n", trame) ;
	fclose(outFile) ;
}

void ecrireTrameCourte(int type, int valeur) {
	if(type < 0 || type > 3 || valeur < 0 || valeur > 63) {
		printf("arguments hors bornes\n") ;
		exit(2) ;
	}

	type=type << 6;
	char * trame = malloc(sizeof(char)) ;
	printf("type     : ");
	afficheBinOctet(type);
	printf("valeur   : ");
	afficheBinOctet(valeur);

	*trame = type | valeur ;

	printf("résultat : ");
	afficheBinOctet(*trame);
	printf("Ce qui donne en nombre : %d\n",*trame);
	

	FILE * outFile = fopen("trame.txt","a") ;
	fprintf(outFile, "%c\n", (*trame)) ;
	fclose(outFile) ;
}

void ecrireTrameCapteur(int type, int moy, int min, int max) {
	if(type < 0 || type > 3 || moy < 0 || moy > 63 || min < 0 || min > 63 || max < 0 || max > 63) {
		printf("arguments hors bornes") ;
		exit(2) ;
	}
	int * trame = malloc(sizeof(int)) ;
	*trame = (type << 30) | (moy << 24) | (min << 18) | (max << 12) ;
	FILE * outFile = fopen("trame.txt","a") ;
	fprintf(outFile, "%d\n", (*trame)) ;
	fclose(outFile) ;
}

int main(int argc, char ** argv) {
	if(argc!=4) {
		printf("Il faut 3 arguments\n") ;
		return(1) ;
	}
	else {
		int etage = atoi(argv[1]) ;
		int chambre = atoi(argv[2]) ;
		int capteur = atoi(argv[3]) ;
		if(etage > 63 || etage <0 || chambre > 1023 || chambre < 0 || capteur > 15 || capteur < 0) {
			printf("arguments hors bornes\n");
			return(2) ;
		}
		ecrireAdresse(etage,chambre,capteur) ;	
		ecrireTrameCourte(1,55) ;
	}
	return(0) ;
}
