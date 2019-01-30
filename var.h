#ifndef VAR_H_
#define VAR_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
/**
* \file variables
**/
typedef struct perso perso;
typedef struct hero hero;
struct hero //structure des personnages principaux
{
	int life,attack1,attack2,attack3,mana,life_max,mana_max,presence;
	float rapport[2];
	SDL_Surface *barre[3],*sorts,*img[4];
	SDL_Rect posbar[2],pos;
	Mix_Chunk *sound[3];
};
struct perso //structure des ennmies
{
	int life,life_max,attaque,type,attaque_ultime;
	float rapport;
	SDL_Surface *img[9], *barre[2];
	SDL_Rect posbar,pos;
};
hero Init_raiden(int lvl);//initialisation de Raiden
hero Init_slendy(int lvl);//initialisation de Slendy
perso Init_archer(int lvl, SDL_Surface *archer_img[4], SDL_Surface *barre, SDL_Surface *vie, SDL_Rect slot);//initialisation de l'archer
perso Init_war(int lvl, SDL_Surface *war_img[9], SDL_Surface *barre, SDL_Surface *vie,SDL_Rect slot); //initialisation du guerrier
void free_raiden(hero carac); //libération raiden
void free_slendy(hero carac); //libération de slendy
perso Init_boss_lvl4(int lvl, SDL_Surface *barre, SDL_Surface *vie,SDL_Rect slot);//initialisation du boss du niveau 4
perso Init_boss_lvl3(int lvl, SDL_Surface *barre, SDL_Surface *vie,SDL_Rect slot); //init boss niveau 3
perso Init_boss_lvl5(int lvl, SDL_Surface *barre, SDL_Surface *vie,SDL_Rect slot); //init boss niveau 5
void free_boss(perso carac); //libération boss


#endif
