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
 * Depuis que j'ai changé la tête, problèmes de collision : rectifier ça
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
				printf("A bientot vieux\n");
				break;
		}
	} while(menu != '3');
	
	return 0;
}
