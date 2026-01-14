void affichebin(int n) ;

void afficheBinOctet(char n) ;

long int findSizeFile(char file_name[]) ;

void ecrirePaddingEtHeader(char * motif, int nb, char * wOra) ;

void clearFile() ;
void ecrireAdresse(unsigned int etage, unsigned int chambre, unsigned int capteur) ;

void ecrireTrameCourte(unsigned int type, unsigned int valeur) ;
void ecrireTrameCapteur(unsigned int type, unsigned int moy, unsigned int min, unsigned int max) ;
int lanceurEnvoi(int argc, char ** argv) ;
