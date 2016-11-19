/*
 * JEU SNAKE
 * 
 * Menu :
 * 1. Débuter une partie
 * 2. Consulter les 5 derniers scores
 * 3. Mettre fin au programme
 * 
 * 
 * AVANCEMENT
 * 
 * Ajout de plein de fruits : pomme, poire, cactus, multifruit, big mac
 * Ajout de messages relatifs à chaque fruit
 * A faire : pouvoir ultra spécial après avoir récolté les lettres ZAK, ajout des couleurs
 */

#include <stdio.h>
#include <stdlib.h>
#include "gestion_clavier.h"
#include "menu.h"
#include "jeu.h"
#include "constantes.h"
#include "time.h"


int main(void)
{
	char menu = 0;
	
	do
	{
		system("clear");
		afficherMenu();
		menu = demanderMenu();
		
		switch(menu)
		{
			case '1':
				jouerPartie(); // Amuse-toi
				break;
			
			case '2':
				printf("Pas encore disponible, desole vieux\n");
				break;
				
			case '3':
				printf("Parametres\n");
				break;
				
			case '4':
				printf("A bientot vieux\n");
		}
	} while(menu != '4');
	
	return 0;
}
