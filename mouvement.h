#ifndef MOUVEMENT_H_
#define MOUVEMENT_H_
#include "var.h"
//focntion qui permet de déplacer le personnage à droite
void mvt_droite(int *droite, SDL_Rect *pos_map, int limite, SDL_Rect *pos, int y, SDL_Surface *back, SDL_Surface *screen, SDL_Surface *a, int *i);

//fonction qui permet de déplacer le personnage à gauche
void mvt_gauche(int *droite, SDL_Rect *pos_map, int limite, SDL_Rect *pos, int y, SDL_Surface *back, SDL_Surface *screen, SDL_Surface *a, int *i);

//fonction qui permet de déplacer le personnage vers le haut
void mvt_haut(SDL_Rect pos_map,SDL_Rect *pos, int y, SDL_Surface *back, SDL_Surface *screen, SDL_Surface *a, SDL_Surface *c, int *i,int droite);

//fonction qui permet de déplacer le personnage vers le bas
void mvt_bas(SDL_Rect pos_map,SDL_Rect *pos, int y, SDL_Surface *back, SDL_Surface *screen, SDL_Surface *a, SDL_Surface *c, int *i, int droite);

//fonction qui permet de contrôler la vitesse de raiden
void boucle(int vitesse, int *actuel, int *precedent);
#endif