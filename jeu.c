#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"
#include "constantes.h"
#include "gestion_clavier.h"
#include "time.h"

//////////////// Fonctions qui traitent le jeu d'une partie ////////////////

void jouerPartie()
{
	char carte[HEIGHT][WIDTH], key = 0;
	position posSerpent[HEIGHT*WIDTH + 1]; // Taille maximum du serpent en comptant la position "invisible" après sa queue
	int tailleSerpent = 1, direction = HAUT, collision = 0, score  = 0;
	
	// Initialisations
	
	posSerpent[0].x = WIDTH/2;
	posSerpent[0].y = HEIGHT/2;
	
	initialiserCarte(carte, posSerpent, tailleSerpent);
	genererFruit(carte);
	genererFruit(carte);
	
	// Deroulement du jeu
	
	do
	{
		printf("\n\n\n\n\n\n");
		afficherCarte(carte, score);
		
		key = pressing_key();
		if(key != NO_KEY)
		{
			modifierDirection(key, &direction);
		}
		
		collision = verifierCollision(carte, posSerpent[0], posSerpent[tailleSerpent-1], direction);
		if(collision == 1)
		{
			printf("\n\nPerdu ! T'es mauvais\n");
		}
		else
		{
			if(collision == -1) // Si il mange un fruit
			{
				tailleSerpent++;
				score++;
				genererFruit(carte);
			}
			modifierPosition(posSerpent, tailleSerpent, direction);
			modifierCarte(carte, posSerpent, tailleSerpent, collision);
		}
		
	}while(key != 'x' && collision != 1);
	
	return;
}

// Crée une carte vierge avec le serpent au centre, tailleSerpent en paramètres au cas où j'ai besoin d'un serpent de taille > 1 au début
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
	
	return;
}

void afficherCarte(char carte[][WIDTH], int score)
{
	int i = 0, j = 0;
	
	// Score
	printf("Score : %d\n\n", score);
	
	// Paroi supérieure
	for(j = 0; j < WIDTH+2; j++)
	{
		printf("X");
	}
	printf("\n");
	
	// Affichage de la carte
	for(i = 0; i < HEIGHT; i++)
	{
		printf("X"); // Paroi latérale gauche
		
		for(j = 0; j < WIDTH; j++)
		{
			printf("%c", carte[i][j]);
		}
		printf("X"); // Paroi latérale droite
		printf("\n"); // Retour ligne
	}
	
	// Paroi inférieure
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
			case 'e':
			if(*direction != BAS)
				*direction = HAUT;
			break;
			
			case 'd':
			if(*direction != HAUT)
				*direction = BAS;
			break;
			
			case 's':
			if(*direction != DROITE)
				*direction = GAUCHE;
			break;
			
			case 'f':
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
	if(collision != -1)
	{
		carte[posSerpent[tailleSerpent].y][posSerpent[tailleSerpent].x] = ' ';
	}
	
	if(tailleSerpent > 1)
	{
		carte[posSerpent[1].y][posSerpent[1].x] = CORPS;
	}
	carte[posSerpent[0].y][posSerpent[0].x] = TETE;
	
	return;
}

// Renvoie 1 si le serpent se heurte contre le mur ou contre son corps, -1 si il mange un fruit, 0 si il avance
int verifierCollision(char carte[][WIDTH], position posTete, position posQueue, int direction)
{
	int collision = 0;
	
	switch(direction)
	{	
		case HAUT:
			if(posTete.y == 0) // Si on ne cherche pas à dépasser la map
			{
				collision = 1;
			}
			else if(carte[posTete.y-1][posTete.x] == CORPS && carte[posTete.y-1][posTete.x] != carte[posQueue.y][posQueue.x]) // On vérifie les 2 conditions séparément pour être sûr de ne pas provoquer de segfault
			{
				collision = 1;
			}
			else if(carte[posTete.y-1][posTete.x] == FRUIT) // Si le serpent mange un fruit
			{
				collision = -1;
			}
			break;
		
		case BAS:
			if(posTete.y == HEIGHT-1)
			{
				collision = 1;
			}
			else if(carte[posTete.y+1][posTete.x] == CORPS && carte[posTete.y+1][posTete.x] != carte[posQueue.y][posQueue.x])
			{
				collision = 1;
			}
			else if(carte[posTete.y+1][posTete.x] == FRUIT)
			{
				collision = -1;
			}
			break;
		
		case GAUCHE:
			if(posTete.x == 0)
			{
				collision = 1;
			}
			else if(carte[posTete.y][posTete.x-1] == CORPS && (posTete.x-1 != posQueue.x && posTete.y != posQueue.y) )
			{
				collision = 1;
			}
			else if(carte[posTete.y][posTete.x-1] == FRUIT)
			{
				collision = -1;
			}
			break;
		
		case DROITE:
			if(posTete.x == WIDTH-1)
			{
				collision = 1;
			}
			else if(carte[posTete.y][posTete.x+1] == CORPS && carte[posTete.y][posTete.x+1] != carte[posQueue.y][posQueue.x])
			{
				collision = 1;
			}
			else if(carte[posTete.y][posTete.x+1] == FRUIT)
			{
				collision = -1;
			}
			break;
	}
	
	return collision;
}

// Génère un fruit sur une case vide de la carte
void genererFruit(char carte[][WIDTH])
{
	position posFruit;
	
	do
	{
		posFruit.x = rand()%WIDTH;
		posFruit.y = rand()%HEIGHT;
	}while(carte[posFruit.y][posFruit.x] != ' ');
	
	carte[posFruit.y][posFruit.x] = FRUIT;
	
	return;
}
