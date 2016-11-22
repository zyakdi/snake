#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"
#include "constantes.h"
#include "gestion_clavier.h"
#include "time.h"

//////////////// Fonctions qui traitent le jeu d'une partie ////////////////


void jouerPartie()
{
	char carte[HEIGHT][WIDTH], key = 0, fruitMange = 0;
	position posSerpent[HEIGHT*WIDTH + 1], posFruit; // posSerpent : aille maximum du serpent en comptant la position "invisible" après sa queue
	int tailleSerpent = HEIGHT/3, direction = HAUT, collision = 0, score  = 0, delai = DELAY_KEY_DETECTION;
	
	// Initialisations
	
	initialiserPositions(posSerpent, tailleSerpent);
	initialiserCarte(carte, posSerpent, tailleSerpent);
	
	srand(time(NULL));
	genererFruit(carte, 0);
	genererFruit(carte, 0);
	
	// Deroulement du jeu
	
	do
	{
		system("clear");
		afficherCarte(carte, score, fruitMange, delai);
		
		////// JEU //////
		
		// Détection de la direction
		key = pressing_key(delai);
		if(key != NO_KEY)
		{
			modifierDirection(key, &direction);
		}
		
		// Vérification de la collision
		collision = verifierCollision(carte, posSerpent[0], posSerpent[tailleSerpent-1], direction, &posFruit);
		if(collision == 1) // Si le serpent heurte un mur ou son corps
		{
			printf("\n\nPerdu ! T'es mauvais\nScore : %d\n", score);
		}
		else
		{
			if(collision == -1) // Si il mange un fruit
			{
				mangerFruit(carte[posFruit.y][posFruit.x], carte, &score, &tailleSerpent, posSerpent, &delai); // Active les effets provoqués par le fruit mangé
				delai -= CHANGE_VITESSE; // A chaque fruit mangé, la vitesse du serpent augmente
				fruitMange = carte[posFruit.y][posFruit.x]; // Permet de déterminer le message à afficher
				
				
				if(carte[posFruit.y][posFruit.x] == POMME)
				{
					collision = 2; // Indique que le serpent mange une pomme, utile pour modifierCarte()
				}
			}
			modifierPosition(posSerpent, tailleSerpent, direction);
			modifierCarte(carte, posSerpent, tailleSerpent, collision);
		}
		
	}while(key != 'x' && collision != 1);
	
	return;
}


void initialiserPositions(position posSerpent[], int tailleSerpent)
{
	int i = 0;
	
	// TETE
	
	posSerpent[0].x = WIDTH/2;
	posSerpent[0].y = HEIGHT/2;
	
	// CORPS
	
	for(i = 1; i < tailleSerpent; i++)
	{
		posSerpent[i].x = posSerpent[0].x; // Ca change pas
		posSerpent[i].y = posSerpent[i-1].y + 1; // On étale le serpent à la verticale
	}
	
	return;
}


// Crée une carte vierge avec le serpent au centre
void initialiserCarte(char carte[][WIDTH], position posSerpent[], int tailleSerpent)
{
	int i = 0, j = 0;
	
	for(i = 0; i < HEIGHT; i++)
	{
		for(j = 0; j < WIDTH; j++)
		{
			carte[i][j] = ' ';
		}
	}
	
	carte[posSerpent[0].y][posSerpent[0].x] = TETE;
	
	// La taille du serpent initiale vaut un tiers de la hauteur de la map
	for(i = 1; i < tailleSerpent; i++)
	{
		carte[posSerpent[i].y][posSerpent[i].x] = CORPS;
	}
	
	return;
}


void afficherCarte(char carte[][WIDTH], int score, char fruitMange, int vitesseActuelle)
{
	int i = 0, j = 0;
	
	// Score
	printf("Score : %d\n\n", score);
	
	// Paroi supérieure
	for(j = 0; j < WIDTH+2; j++)
	{
		printf("X");
	}
	
	// Affichage de la 1ere moitié de la carte
	for(i = 0; i < HEIGHT/2; i++)
	{
		printf("\nX"); // Paroi latérale gauche
		
		for(j = 0; j < WIDTH; j++)
		{
			printf("%c", carte[i][j]);
		}
		printf("X"); // Paroi latérale droite
	}
	
	// Petit message sur le tec hamdoullah
	//lireMessage(fruitMange);
	printf("  Vitesse : %d", vitesseActuelle);
	
	// Affichage de la 2eme moitié de la carte
	for(i = i; i < HEIGHT; i++)
	{
		printf("\nX"); // Paroi latérale gauche
		
		for(j = 0; j < WIDTH; j++)
		{
			printf("%c", carte[i][j]);
		}
		printf("X"); // Paroi latérale droite
	}
	
	// Paroi inférieure
	printf("\n");
	for(j = 0; j < WIDTH+2; j++)
	{
		printf("X");
	}
	printf("\n");
	
	return;
}


// Modifie la direction si l'utilisateur en a décidé ainsi
void modifierDirection(char key, int *direction)
{
		switch(key)
		{
			case 'z':
			if(*direction != BAS)
				*direction = HAUT;
			break;
			
			case 's':
			if(*direction != HAUT)
				*direction = BAS;
			break;
			
			case 'q':
			if(*direction != DROITE)
				*direction = GAUCHE;
			break;
			
			case 'd':
			if(*direction != GAUCHE)
				*direction = DROITE;
			break;
		}
	return;
}


void modifierPosition(position posSerpent[], int tailleSerpent, int direction)
{
	int i = 0;
	
	// On modifie la pos de chaque partie du serpent en commençant par la fin
	for(i = tailleSerpent; i > 0; i--) // tailleSerpent car on aura besoin de la position "invisible" du serpent après sa queue
	{
		posSerpent[i] = posSerpent[i-1]; 
	}
	
	// La tête du serpent avance selon la direction
	switch(direction)
	{
		case HAUT:
		posSerpent[0].y--;
		break;
		
		case BAS:
		posSerpent[0].y++;
		break;
		
		case GAUCHE:
		posSerpent[0].x--;
		break;
		
		case DROITE:
		posSerpent[0].x++;
		break;
	}
	
	return;
}


// Ajoute la tête du serpent et supprime la queue, à chaque avancée
void modifierCarte(char carte[][WIDTH], position posSerpent[], int tailleSerpent, int collision)
{
	if(collision != 2) // Si le serpent ne mange pas une pomme
	{
		carte[posSerpent[tailleSerpent].y][posSerpent[tailleSerpent].x] = ' '; // Supprime la queue
	}
	
	if(tailleSerpent > 1)
	{
		carte[posSerpent[1].y][posSerpent[1].x] = CORPS;
	}
	carte[posSerpent[0].y][posSerpent[0].x] = TETE; // Ajoute la tête
	
	return;
}


// Renvoie 1 si le serpent se heurte contre le mur ou contre son corps, -1 si il mange un fruit, 0 si il avance
int verifierCollision(char carte[][WIDTH], position posTete, position posQueue, int direction, position *posFruit)
{
	int collision = 0;
	
	switch(direction)
	{	
		case HAUT:
			if(posTete.y == 0) // Si on ne cherche pas à dépasser la map
			{
				collision = 1;
			}
			else if(carte[posTete.y-1][posTete.x] == CORPS && (posTete.x != posQueue.x || posTete.y-1 != posQueue.y) ) // On vérifie les 2 conditions séparément pour être sûr de ne pas provoquer de segfault
			{
				collision = 1;
			}
			else if(carte[posTete.y-1][posTete.x] == POMME || carte[posTete.y-1][posTete.x] == POIRE || carte[posTete.y-1][posTete.x] == MULTIFRUIT || 
					carte[posTete.y-1][posTete.x] == CACTUS || carte[posTete.y-1][posTete.x] == BIGMAC) // Si le serpent mange un fruit
			{
				// Détection de la position du fruit pour le manipuler dans jouerPartie()
				posFruit->x = posTete.x;
				posFruit->y = posTete.y-1;
				collision = -1;
			}
			break;
		
		case BAS:
			if(posTete.y == HEIGHT-1)
			{
				collision = 1;
			}
			else if(carte[posTete.y+1][posTete.x] == CORPS && (posTete.x != posQueue.x || posTete.y+1 != posQueue.y) )
			{
				collision = 1;
			}
			else if(carte[posTete.y+1][posTete.x] == POMME || carte[posTete.y+1][posTete.x] == POIRE || carte[posTete.y+1][posTete.x] == MULTIFRUIT || 
					carte[posTete.y+1][posTete.x] == CACTUS || carte[posTete.y+1][posTete.x] == BIGMAC)
			{
				posFruit->x = posTete.x;
				posFruit->y = posTete.y+1;
				collision = -1;
			}
			break;
		
		case GAUCHE:
			if(posTete.x == 0)
			{
				collision = 1;
			}
			else if(carte[posTete.y][posTete.x-1] == CORPS && (posTete.x-1 != posQueue.x || posTete.y != posQueue.y) )
			{
				collision = 1;
			}
			else if(carte[posTete.y][posTete.x-1] == POMME || carte[posTete.y][posTete.x-1] == POIRE || carte[posTete.y][posTete.x-1] == MULTIFRUIT ||
					carte[posTete.y][posTete.x-1] == CACTUS || carte[posTete.y][posTete.x-1] == BIGMAC)
			{
				posFruit->x = posTete.x-1;
				posFruit->y = posTete.y;
				collision = -1;
			}
			break;
		
		case DROITE:
			if(posTete.x == WIDTH-1)
			{
				collision = 1;
			}
			else if(carte[posTete.y][posTete.x+1] == CORPS && (posTete.x+1 != posQueue.x || posTete.y != posQueue.y) )
			{
				collision = 1;
			}
			else if(carte[posTete.y][posTete.x+1] == POMME || carte[posTete.y][posTete.x+1] == POIRE || carte[posTete.y][posTete.x+1] == MULTIFRUIT ||
					carte[posTete.y][posTete.x+1] == CACTUS || carte[posTete.y][posTete.x+1] == BIGMAC)
			{
				posFruit->x = posTete.x+1;
				posFruit->y = posTete.y;
				collision = -1;
			}
			break;
	}
	
	return collision;
}


// Génère un fruit sur une case vide de la carte
void genererFruit(char carte[][WIDTH], char poire)
{
	position posFruit;
	char fruit = POMME;
	
	// Génération d'une position où le fruit sera placé
	do
	{
		posFruit.x = rand()%WIDTH;
		posFruit.y = rand()%HEIGHT;
	}while(carte[posFruit.y][posFruit.x] != ' ');
	
	// Determination du fruit à générer
	if(poire == POIRE) // Si l'on veut absolument générer une poire (lorsque le serpent mange un multifruit)
	{
		fruit = POIRE;
	}
	else
	{
		if(fruitSpecial(PROBA_BIGMAC))
		{
			fruit = BIGMAC;
		}
		else if(fruitSpecial(PROBA_CACTUS))
		{
			fruit = CACTUS;
		}
		else if(fruitSpecial(PROBA_MULTIFRUIT))
		{
			fruit = MULTIFRUIT;
		}
	}
	
	carte[posFruit.y][posFruit.x] = fruit;
	
	return;
}

// Probabilité de 1/probaMax de générer le fruit concerné 
int fruitSpecial(int probaMax)
{
	if(rand()%probaMax == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


// Mise en place des effets produits par le fruit
void mangerFruit(char fruit, char carte[][WIDTH], int *score, int *tailleSerpent, position posSerpent[], int *delai)
{
	int i = 0, nouvelleTailleSerpent = 0;
	
	switch(fruit)
	{
		case POMME:
			(*score)++;
			(*tailleSerpent)++;
			genererFruit(carte, 0);
			break;
			
		case POIRE:
			(*score)++;
			break;
			
		case MULTIFRUIT:
			for(i = rand()%7; i < 10; i++) // 4 à 10 itérations
			{
				genererFruit(carte, POIRE);
			}
			genererFruit(carte, 0);
			break;
			
		case CACTUS:
			if(*tailleSerpent >= 3) // Il lui faut une taille minimum de 3
			{
				nouvelleTailleSerpent = 2 * (*tailleSerpent/3);
				for(i = nouvelleTailleSerpent; i < *tailleSerpent; i++)
				{
					carte[posSerpent[i].y][posSerpent[i].x] = ' ';
				}
				*tailleSerpent = nouvelleTailleSerpent;
			}
			genererFruit(carte, 0);
			break;
			
		case BIGMAC:
			*delai += RALENTIR;
			genererFruit(carte, 0);
			break;
	}
	
	return;
}


void lireMessage(char fruitMange)
{
	switch(fruitMange)
	{
		case POIRE:
			printf(MESSAGE_POIRE);
			break;
		
		case MULTIFRUIT:
			printf(MESSAGE_MULTIFRUIT);
			break;
			
		case CACTUS:
			printf(MESSAGE_CACTUS);
			break;
		case BIGMAC:
			printf(MESSAGE_BIGMAC);
			break;
	}
	
	return;
}
