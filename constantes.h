#ifndef CONSTANTES_H
#define CONSTANTES_H

#define TMAX 100
#define RALENTIR 100000 // Augmente le délai entre les mouvements de RALENTIR (en microsecondes)
#define CHANGE_VITESSE 10000 // Augmente la vitesse de CHANGE_VITESSE microsecondes par mouvement

#define HEIGHT 15
#define WIDTH 30

#define CORPS '0'
#define TETE '@'
#define POMME '*' // Score +1
#define POIRE '+' // Score +1
#define MULTIFRUIT '%' // Génère 4 à 10 fruits
#define CACTUS '#' // Coupe un tiers du serpent
#define BIGMAC '=' // Ralentit le serpent

#define PROBA_MULTIFRUIT 10 // 1/PROBA
#define PROBA_CACTUS 10
#define PROBA_BIGMAC 10

#define MESSAGE_POIRE "  Une poire! Miam"
#define MESSAGE_MULTIFRUIT "  Cocktail multifruit! Bismillah"
#define MESSAGE_CACTUS "  Aie! Un cactus!"
#define MESSAGE_BIGMAC "  Un big mac! On peut digerer tranquillement"

#define HAUT 0
#define BAS 1
#define GAUCHE 2
#define DROITE 3

#endif
