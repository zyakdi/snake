/*
 * REMISE A NIVEAU INFO ISTY
 * Code ecrit par : Fabien Calcado
 * Email : fabien.calcado@isty.uvsq.fr
 * */

#ifndef GESTION_CLAVIER_H
#define GESTION_CLAVIER_H

/*Macro utilisée par la fonction "pressing_key()" */
#define DELAY_KEY_DETECTION 1
#define HIT_KEY 1
#define NO_KEY -1

/* Fonctions permettant de changer le flot d'entrée et de le réinitialiser */
void   init_keyboard(void);
void   close_keyboard(void);
int    keyboard_hit(void);
char   readch(void);

/*Fonction qui renvoie une touche pressée par l'utilisateur
 * Renvoie la valeur NO_KEY si aucune touche n'a été appuyée
 * pendant le temps DELAY_KEY_DETECTION (en secondes)*/
char pressing_key(void);

#endif 
