echo -e "\ncompilation..------------------------------------------------------------------------------------------------------------\n"
gcc -Wall -Wextra ecrireTrame.c -o ecrireTrame.out
gcc -Wall -Wextra lireTrame.c -o lireTrame.out
echo -e "\nexécution avec les paramètres étage=10, chambre=90 et capteur=15, trame courte type = 1, valeur = 55--------------------------------------------------------\n"
./ecrireTrame.out 10 90 15 1 55
echo -e "\nlecture de la trame : ---------------------------------------------------------------------------------------------------\n"
./lireTrame.out
echo -e "\nexécution avec les paramètres étage=7, chambre=12 et capteur=8, trame longue type type = 3, moy = 37, min = 7, max = 58--------------------------------------------------------\n"
./ecrireTrame.out 7 12 8 3 37 7 58
echo -e "\nlecture de la trame : ---------------------------------------------------------------------------------------------------\n"
./lireTrame.out
