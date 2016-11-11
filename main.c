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
 * Pour l'instant je veux une tête qui se déplace librement dans la carte selon la touche tapée
 * Avancer dans le main
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
	// JEU
	
	srand(time(NULL));
	jouerPartie();
	
	
	return 0;
}
