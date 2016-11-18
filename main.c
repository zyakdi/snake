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
 * La progression de la vitesse est fonctionnelle, maintenant je veux rajouter des fonctionnalités fun comme des fruits différents donnant des effets spéciaux
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
