#include "mouvement.h"
#include "var.h"


void mvt_droite(int *droite, SDL_Rect *pos_map, int limite, SDL_Rect *pos, int y, SDL_Surface *back, SDL_Surface *screen, SDL_Surface *a, int *i)
{
	*droite=1;//le personnage est dirigé vers la droite
	SDL_Rect b,c;
	if (pos_map->x==limite-1280)//si le personnage est arrivé à la limite de la map->arrêt du scrolling et changement des coordonées de raiden à la place
	{
		if (pos->x>-1280+261)//si le personnage n'est pas encore arrivée à la fin de l'écran(pour éviter que le personnage dépasse le mur et disparâit de l'écran)
		{
			pos->x=pos->x-y;//changement des coordonnées de raiden
		}
	}
	else
	{
		pos_map->x=pos_map->x+y;//changement des coordonnées de la map
	}
	b=*pos_map;//position de la map
	c=*pos;//position raiden
	SDL_BlitSurface(back,&b,screen,NULL);//affichage background
	SDL_BlitSurface(a,&c,screen,NULL);//affichage du personange
	SDL_Flip(screen);
	(*i)++;//compteur qui gère l'ordre des mouvement de raiden
	if (*i==14)//si le compteur dépasse le nombre d'images de raiden alors il recommence à nouveau
	{
		*i=0;
	}	
}
void mvt_gauche(int *droite, SDL_Rect *pos_map, int limite, SDL_Rect *pos, int y, SDL_Surface *back, SDL_Surface *screen, SDL_Surface *a, int *i)
{

	SDL_Rect b,c;
	*droite=0;//personnage dirigé vers la gauche
	if (pos_map->x==0)
	{
		if (pos->x<70)
		{
			pos->x=pos->x+y;
		}
	}
	else 
	{
		pos_map->x=pos_map->x-y;
	}
	b=*pos_map;
	c=*pos;
	SDL_BlitSurface(back,&b,screen,NULL);
	SDL_BlitSurface(a,&c,screen,NULL);
	SDL_Flip(screen);
	(*i)++;
	if (*i==14)
	{
		*i=0;
	}	
}
void mvt_haut(SDL_Rect pos_map,SDL_Rect *pos, int y, SDL_Surface *back, SDL_Surface *screen, SDL_Surface *a, SDL_Surface *c, int *i, int droite)
{
	SDL_Rect b;
	if (droite==1)
	{
		if (pos->y<20)
		{
			pos->y=pos->y+y;
		}
		b=*pos;
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		SDL_BlitSurface(a,&b,screen,NULL);
	}
	else if (droite==0) 
	{
		if (pos->y<20)
		{
			pos->y=pos->y+y;
		}
		b=*pos;
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		SDL_BlitSurface(c,&b,screen,NULL);
	}
	SDL_Flip(screen);
	(*i)++;
	if (*i==14)
	{
		*i=0;
	}
}
void mvt_bas(SDL_Rect pos_map,SDL_Rect *pos, int y, SDL_Surface *back, SDL_Surface *screen, SDL_Surface *a, SDL_Surface *c, int *i, int droite)
{
	SDL_Rect b;
	if (droite==1)
	{
		if (pos->y>-180)
		{
			pos->y=pos->y-y;
		}
		b=*pos;
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		SDL_BlitSurface(a,&b,screen,NULL);
		}
	else if (droite==0) 
	{
		if (pos->y>-180)
		{
			pos->y=pos->y-y;
		}
		b=*pos;
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		SDL_BlitSurface(c,&b,screen,NULL);
		}
	SDL_Flip(screen);
	(*i)++;
	if (*i==14)
	{
		*i=0;
	}
}
void boucle(int vitesse, int *actuel, int *precedent)
{
	do
	{
		*actuel=SDL_GetTicks();
	}
	while (*actuel-*precedent<vitesse);
	*precedent=*actuel;
}
