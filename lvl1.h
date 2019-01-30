#ifndef LVL1_H_
#define LVL1_H_
#include "mouvement.h"
#include "cbt.h"
#include "var.h"
int lvl_1(SDL_Surface *screen, SDL_Surface *back, int *sound, int *fullscreen);//fonction comportant la phase de mouvement et la phase de combat
int lvl_2(SDL_Surface *screen, SDL_Surface *back, int *sound, int *fullscreen);
int lvl_3(SDL_Surface *screen, SDL_Surface *back, int *sound, int *fullscreen);
int lvl_4(SDL_Surface *screen, SDL_Surface *back, int *sound, int *fullscreen);
int lvl_5(SDL_Surface *screen, SDL_Surface *back, int *sound, int *fullscreen);




void fin_cbt(SDL_Surface *back,SDL_Surface *screen, SDL_Surface *img, SDL_Rect pos_map, SDL_Rect pos);
#endif
