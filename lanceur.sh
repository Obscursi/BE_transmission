echo -e "\ncompilation..------------------------------------------------------------------------------------------------------------\n"
gcc -Wall -Wextra ecrireTrame.c -o ecrireTrame.out
gcc -Wall -Wextra lireTrame.c -o lireTrame.out
echo -e "\nexécution avec les paramètres étage=10, chambre=90 et capteur=15 --------------------------------------------------------\n"
./ecrireTrame.out 10 90 15
echo -e "\nlecture de la trame : ---------------------------------------------------------------------------------------------------\n"
./lireTrame.out


