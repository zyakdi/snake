#ifndef JEU_H
#define JEU_H

#include "constantes.h"

typedef struct
{
	int x;
	int y;
}position;

void jouerPartie();
void initialiserPositions(position posSerpent[], int tailleSerpent);
void initialiserCarte(char carte[][WIDTH], position posSerpent[], int tailleSerpent);
void afficherCarte(char carte[][WIDTH], int score, char fruitMange, int vitesseActuelle);
void modifierDirection(char key, int *direction);
void modifierPosition(position posSerpent[], int tailleSerpent, int direction);
void modifierCarte(char carte[][WIDTH], position posSerpent[], int tailleSerpent, int collision);
int verifierCollision(char carte[][WIDTH], position posTete, position posQueue, int direction, position *posFruit);
void genererFruit(char carte[][WIDTH], char poire);
int fruitSpecial(int probaMax);
void mangerFruit(char fruit, char carte[][WIDTH], int *score, int *tailleSerpent, position posSerpent[], int *delai);
void lireMessage(char fruitMange);

#endif
