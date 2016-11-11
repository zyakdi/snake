#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "constantes.h"

void afficherMenu()
{
	printf("\nMENU\n\n");
	printf("1: Lancer une partie\n2: Afficher les 5 meilleurs scores\n3: Quitter le jeu\n\n");
	return;
}

int demanderMenu()
{
	int menu = 0;
	
	do
	{
		printf("Que voulez-vous faire ?\nReponse : ");
		// Faire la fonction de saisie sécurisée
		scanf(" %d", &menu);
	} while(menu < 1 && menu > 3);
	
	return menu;
}

void lireChaine(char *chaine) // Lit un caractère
{
    char *posEntree = NULL;

    fgets(chaine, 1, stdin);

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
