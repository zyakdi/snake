#ifndef JEU
#define JEU

#include "constantes.h"

typedef struct
{
	int x;
	int y;
}position;

void jouerPartie();
void initialiserPositions(position posSerpent[], int tailleSerpent);
void initialiserCarte(char carte[][WIDTH], position posSerpent[], int tailleSerpent);
void afficherCarte(char carte[][WIDTH], int score);
void modifierDirection(char key, int *direction);
void modifierPosition(position posSerpent[], int tailleSerpent, int direction);
void modifierCarte(char carte[][WIDTH], position posSerpent[], int tailleSerpent, int collision);
int verifierCollision(char carte[][WIDTH], position posTete, position posQueue, int direction);
void genererFruit(char carte[][WIDTH]);

#endif
