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

long int findSizeFile(char file_name[])
{
    // opening the file in read mode
    FILE* fp = fopen(file_name, "r");

    // checking if the file exist or not
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    // calculating the size of the file
    long int res = ftell(fp);

    // closing the file
    fclose(fp);

    return res;
}

	

/*void afficheAdresse(int n){ //ne marche pas
    unsigned u = (unsigned)n;   // On lit les bits 

	int compteur = 0;

    for (int i = 19; i >= 0; i--) {
        unsigned bit = (u >> i) & 1;   // On décale, puis on lit le dernier bit
        printf("%u", bit);
		compteur++;
		if (compteur==6 || compteur ==16){
			printf(" || ");
		}
    }
    printf("\n");
}*/

void ecrirePaddingEtHeader(char * motif, int nb, char * wOra) {
	FILE * outFile= fopen("trame.txt",wOra) ;

	
	for(int i=0; i<nb; i++) {
		fprintf(outFile, "%s", motif) ;
	}
	fprintf(outFile, "\n%d\n", 1234567890) ;
	fclose(outFile) ;
}

void clearFile() {
	FILE * outFile = fopen("trame.txt","w") ;
	fclose(outFile) ;
}

void ecrireAdresse(unsigned int etage, unsigned int chambre, unsigned int capteur) {

	etage = etage << 26 ;
	printf("Etage    : ") ;
	affichebin(etage);

	chambre = chambre << 16 ;
	printf("Chambre  : ") ;
	affichebin(chambre);

	capteur = capteur << 12 ;
	printf("Capteur  : ") ;
	affichebin(capteur);

	unsigned int trame = etage | chambre ;
	trame = trame | capteur ;

	printf("Résultat : ");
	affichebin(trame);

	printf("\n");
	printf("Nombre correspondant à l'adresse finale : %d\n",trame) ;
	printf("adresse finie d'être construite, on sort du fichier trame.txt \n\n");

	FILE * outFile = fopen("trame.txt","a") ;
	fprintf(outFile, "%d\n", trame) ;
	fclose(outFile) ;
}

void ecrireTrameCourte(unsigned int type, unsigned int valeur) {
	if(type > 3 || valeur > 63) {
		printf("arguments hors bornes\n") ;
		exit(2) ;
	}

	type=type << 6;
	unsigned int * trame = malloc(sizeof(int)) ;
	printf("type     : ");
	afficheBinOctet(type);
	printf("valeur   : ");
	afficheBinOctet(valeur);

	*trame = type | valeur ;

	printf("résultat : ");
	afficheBinOctet(*trame);
	printf("Ce qui donne en nombre : %d\n",*trame);
	

	FILE * outFile = fopen("trame.txt","a") ;
	fprintf(outFile, "%d\n", (*trame) << 24) ;
	fclose(outFile) ;
}
//0 alerte, 1 actionneur 2 ACK

void ecrireTrameCapteur(unsigned int type, unsigned int moy, unsigned int min, unsigned int max) {
	if(type > 3 || moy > 63 || min > 63 || max > 63) {
		printf("arguments hors bornes") ;
		exit(2) ;
	}
	unsigned int * trame = malloc(sizeof(int)) ;
	*trame = (type << 30) | (moy << 24) | (min << 18) | (max << 12) ;
	/**trame = (type << 22) | (moy << 16) | (min << 10) | (max << 4) ;
	char c1 = (char) (*trame) ;
	*trame = (*trame) >> 8 ;
	char c2 = (char) (*trame) ;
	*trame = (*trame) >> 8 ;
	char c3 = (char) (*trame) ;*/
	FILE * outFile = fopen("trame.txt","a") ;
	/*fprintf(outFile, "%c\n", c1) ;
	printf("char 1 : %c\n", c1) ;
	printf("char 1 int : %d\n", (int) c1) ;
	fprintf(outFile, "%c\n", c2) ;
	printf("char 2 : %c\n", c2) ;
	printf("char 2 int : %d\n", (int) c2) ;
	fprintf(outFile, "%c\n", c3) ;
	printf("char 3 : %c\n", c3) ;
	printf("char 3 int : %d\n", (int) c3) ;*/
	fprintf(outFile, "%d\n",(*trame)) ;
	fclose(outFile) ;
}

int lanceurEnvoi(int argc, char ** argv) {
	if(argc==6) {
		int etage = atoi(argv[1]) ;
		int chambre = atoi(argv[2]) ;
		int capteur = atoi(argv[3]) ;
		if(etage > 63 || etage <0 || chambre > 1023 || chambre < 0 || capteur > 15 || capteur < 0) {
			printf("arguments hors bornes\n");
			return(2) ;
		}
		clearFile() ;
		//ecrirePaddingEtHeader("0000",8) ; //attention si modif modif lireTrame
		ecrireAdresse(etage,chambre,capteur) ;	
		int type = atoi(argv[4]) ;
		int val = atoi(argv[5]) ;
		ecrireTrameCourte(type,val) ;
		long sizeFile = findSizeFile("trame.txt");
		int taillePadding = 24-sizeFile; //entier+\n =12 par ligne = 24 (caractère fin de fichier ne compte pas)
		
		char * charAppend="w";
		for (int i=0;i<3;i++){
			ecrirePaddingEtHeader("0",taillePadding,charAppend) ; //attention si modif modif lireTrame
			charAppend="a"; //maintenant on efface plus on append la trame (on l'écrit trois fois en tout)
			ecrireAdresse(etage,chambre,capteur) ;	
			ecrireTrameCourte(type,val) ;		
		}

	}
	else if(argc==8) {
		int etage = atoi(argv[1]) ;
		int chambre = atoi(argv[2]) ;
		int capteur = atoi(argv[3]) ;
		if(etage > 63 || etage <0 || chambre > 1023 || chambre < 0 || capteur > 15 || capteur < 0) {
			printf("arguments hors bornes\n");
			return(2) ;
		}
		clearFile() ;
		//ecrirePaddingEtHeader("0000",8) ; //attention si modif modif lireTrame
		ecrireAdresse(etage,chambre,capteur) ;	
		int type = atoi(argv[4]) ;
		int val = atoi(argv[5]) ;
		int min = atoi(argv[6]) ;
		int max = atoi(argv[7]) ;
		ecrireTrameCapteur(type,val,min,max) ;
		long sizeFile = findSizeFile("trame.txt");
		int taillePadding = 24-sizeFile; //entier+\n =12 par ligne =24
		
		char * charAppend="w";
		for (int i=0;i<3;i++){
			ecrirePaddingEtHeader("0",taillePadding,charAppend) ; //attention si modif modif lireTrame
			charAppend="a"; //maintenant on efface plus on append la trame (on l'écrit trois fois en tout)
			ecrireAdresse(etage,chambre,capteur) ;	
			ecrireTrameCapteur(type,val,min,max);		
		}
	}
	else {
		printf("Nombre d'arguments incohérent, 5 arguments pour une trame courte ou 7 arguments pour une trame longue\n") ;
	}
	return(0) ;
}

int main(int argc, char ** argv) {
	lanceurEnvoi(argc,argv) ;
}
