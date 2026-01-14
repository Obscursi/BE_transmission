#!/bin/bash

# Variable pour définir le chemin du fichier à évaluer
fichier="./trame.txt"

while [ true ]
do
	# Test pour vérifier si le fichier existe
	var1=`wc -c trame.txt | cut -d " " -f 1`
	#echo $var1
	if [ $var1 -gt 1 ]; then
		echo on a reçu une nouvelle trame : 
		cat ./trame.txt
		./lireTrame.out >> fichierAutomatisation.txt
		rm -f trame.txt
		touch trame.txt
	fi
done
