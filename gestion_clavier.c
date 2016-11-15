/*
 * REMISE A NIVEAU INFO ISTY
 * Code ecrit par : Fabien Calcado
 * Email : fabien.calcado@isty.uvsq.fr
 */

#include "gestion_clavier.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>   // for read()

static struct termios initial_settings, new_settings;
static int peek_character = -1;

void init_keyboard()
{
	// on change de mode ?? ou préparation du terminal
	// le 1er arg=> 0 est égal à STDIN_FILENO à priori
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard()
{
	// Rétablissement du terminal
    tcsetattr(0, TCSANOW, &initial_settings);
}

/* retourne HIT_KEY si un caract a été détecté NO_KEY sinon */
int keyboard_hit()
{
	unsigned char ch;
	char status;
	int nread;
	
    if (peek_character != -1)
		return HIT_KEY;
	
    //ecoute du clavier
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0,&ch,1);
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);
    
    // test de lecture
    if(nread == 1)
    {
		//une touche a été appuyée
        peek_character = ch;
        status = HIT_KEY;
    }
    else
    {
		//aucune touche détectée
		status = NO_KEY;
    }
    
	return status;
	
}

// Retourne le code ascii du caractère tapé
char readch()
{
	char ch=0;

    if(peek_character != -1) // Si un caractère a été tapé
    {
		//on récup le caractère tapé
        ch = peek_character;
        peek_character = -1;
        
        return ch;
    }
    else
    {
		read(0,&ch,1);
		//printf("return peek_caract ==1 readch() \n");
    }
    return ch;
}


char pressing_key()
{
	char key = NO_KEY;
	
	init_keyboard();
	usleep(DELAY_KEY_DETECTION);
	
	if( keyboard_hit() != NO_KEY )
	{
		do
		{
			key = readch();
		}while( keyboard_hit() != NO_KEY  );
	}
	
	/*TO DO récupérer flèche directionnelle 
	 * 	=> pas évident car c'est une suite de caractère...*/	
	close_keyboard();
	
	return key;
}

