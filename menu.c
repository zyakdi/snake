#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "constantes.h"

void afficherMenu()
{
	printf("\nMENU\n\n");
	printf("1: Lancer une partie\n2: Afficher les 5 meilleurs scores\n3: Parametres\n4: Quitter le jeu\n\n");
	return;
}

char demanderMenu()
{
	char menu[2] = ""; // On utilise une case pour le caractère et une autre pour \0
	
	do
	{
		printf("Que voulez-vous faire ?\nReponse : ");
		lireChaine(menu);
	} while(menu[0] < '1' || menu[0] > '4');
	
	return menu[0];
}

void lireChaine(char *chaine) // Lit un caractère
{
    char *posEntree = NULL;

    fgets(chaine, 2, stdin);

    if(strchr(chaine, '\n') != NULL) // Si on trouve le caractère \n
    {
        posEntree = strchr(chaine, '\n'); // On cherche le caractère \n dans notre chaine
        *posEntree = '\0'; // Et on le remplace par \0
    }
    else // Si l'utilisateur a tapé trop de caractères, il faut vider le buffer
    {
        viderBuffer();
    }

    return;
}


void viderBuffer()
{
    char car = 0;

    while(car != '\n' && car != EOF)
    {
        car = getchar(); // Lit l'entrée standard stdin jusqu'à qu'elle soit vide
    }

    return;
}
