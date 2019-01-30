#include "SDL/SDL.h"
#include <SDL/SDL_image.h>

int main(int argc, char *argv[])
{
	SDL_Surface *back=NULL,*screen=NULL,*mvt0=NULL,*mvt1=NULL,*mvt2=NULL,*mvt3=NULL,*mvt4=NULL,*mvt5=NULL,*mvt6=NULL,*mvt7=NULL,*mvt8=NULL,*mvt9=NULL,*mvt10=NULL,*mvt11=NULL,*mvt12=NULL,*mvt13=NULL,*mvtg0=NULL,*mvtg1=NULL,*mvtg2=NULL,*mvtg3=NULL,*mvtg4=NULL,*mvtg5=NULL,*mvtg6=NULL,*mvtg7=NULL,*mvtg8=NULL,*mvtg9=NULL,*mvtg10=NULL,*mvtg11=NULL,*mvtg12=NULL,*mvtg13=NULL;
	int continuer=1,i=0,x=70,precedent=0,actuel=0,y=10,droite=1;
	SDL_Event event;
	SDL_Rect pos, pos_map;

	SDL_Init(SDL_INIT_EVERYTHING);
	screen=SDL_SetVideoMode(1280,768,32,SDL_SWSURFACE | SDL_DOUBLEBUF);
	back=IMG_Load("Untitled-1.png");
	mvt0=IMG_Load("mouvement droite 0.png");
	mvt1=IMG_Load("mouvement droite 1.png");
	mvt2=IMG_Load("mouvement droite 2.png");
	mvt3=IMG_Load("mouvement droite 3.png");
	mvt4=IMG_Load("mouvement droite 4.png");
	mvt5=IMG_Load("mouvement droite 5.png");
	mvt6=IMG_Load("mouvement droite 6.png");
	mvt7=IMG_Load("mouvement droite 0.png");
	mvt8=IMG_Load("mouvement droite 8.png");
	mvt9=IMG_Load("mouvement droite 9.png");
	mvt10=IMG_Load("mouvement droite 10.png");
	mvt11=IMG_Load("mouvement droite 11.png");
	mvt12=IMG_Load("mouvement droite 12.png");
	mvt13=IMG_Load("mouvement droite 13.png");
	mvtg0=IMG_Load("mouvement gauche 0.png");
	mvtg1=IMG_Load("mouvement gauche 1.png");
	mvtg2=IMG_Load("mouvement gauche 2.png");
	mvtg3=IMG_Load("mouvement gauche 3.png");
	mvtg4=IMG_Load("mouvement gauche 4.png");
	mvtg5=IMG_Load("mouvement gauche5.png");
	mvtg6=IMG_Load("mouvement gauche6.png");
	mvtg7=IMG_Load("mouvement gauche 0.png");
	mvtg8=IMG_Load("mouvement gauche8.png");
	mvtg9=IMG_Load("mouvement gauche9.png");
	mvtg10=IMG_Load("mouvement gauche10.png");
	mvtg11=IMG_Load("mouvement gauche11.png");
	mvtg12=IMG_Load("mouvement gauche12.png");
	mvtg13=IMG_Load("mouvement gauche13.png");

	pos_map.x=0;
	pos_map.y=0;
	pos.x=0;
	pos.y=0;
	SDL_BlitSurface(back,NULL,screen,NULL);
	SDL_BlitSurface(mvt0,NULL,screen,NULL);
	SDL_Flip(screen);
	
	do
	{
		SDL_PollEvent(&event);
		if (event.type==SDL_QUIT)
		{
			continuer=0;
		}
		if (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_RIGHT)
		{
			droite=1;
			switch (i)
			{
				case 0:
				{
					pos_map.x=pos_map.x+y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvt1,NULL,screen,NULL);
					SDL_Flip(screen);
					i=1;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 1:
				{
					pos_map.x=pos_map.x+y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvt2,NULL,screen,NULL);
					SDL_Flip(screen);		
					i=2;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;		
				}
				case 2:
				{
					pos_map.x=pos_map.x+y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvt3,NULL,screen,NULL);
					SDL_Flip(screen);
					i=3;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 3:
				{
					pos_map.x=pos_map.x+y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvt4,NULL,screen,NULL);
					SDL_Flip(screen);
					i=4; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 4:
				{
					pos_map.x=pos_map.x+y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvt5,NULL,screen,NULL);
					SDL_Flip(screen);
					i=5; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 5:
				{
					pos_map.x=pos_map.x+y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvt6,NULL,screen,NULL);
					SDL_Flip(screen);
					i=6; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 6:
				{
					pos_map.x=pos_map.x+y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvt7,NULL,screen,NULL);
					SDL_Flip(screen);
					i=7; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 7:
				{
					pos_map.x=pos_map.x+y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvt8,NULL,screen,NULL);
					SDL_Flip(screen);
					i=8; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 8:
				{
					pos_map.x=pos_map.x+y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvt9,NULL,screen,NULL);
					SDL_Flip(screen);
					i=9;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 9:
				{
					pos_map.x=pos_map.x+y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvt10,NULL,screen,NULL);
					SDL_Flip(screen);
					i=10;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 10:
				{
					pos_map.x=pos_map.x+y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvt11,NULL,screen,NULL);
					SDL_Flip(screen);
					i=11;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 11:
				{
					pos_map.x=pos_map.x+y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvt12,NULL,screen,NULL);
					SDL_Flip(screen);
					i=12;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 12:
				{
					pos_map.x=pos_map.x+y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvt13,NULL,screen,NULL);
					SDL_Flip(screen);
					i=13; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 13:
				{
					pos_map.x=pos_map.x+y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvt0,NULL,screen,NULL);
					SDL_Flip(screen);
					i=0; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
			}

		}
		if (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_LEFT)
		{
			droite=0;
			switch (i)
			{
				case 0:
				{
					pos_map.x=pos_map.x-y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvtg1,NULL,screen,NULL);
					SDL_Flip(screen);
					i=1;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 1:
				{
					pos_map.x=pos_map.x-y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvtg2,NULL,screen,NULL);
					SDL_Flip(screen);		
					i=2;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;		
				}
				case 2:
				{
					pos_map.x=pos_map.x-y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvtg3,NULL,screen,NULL);
					SDL_Flip(screen);
					i=3;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 3:
				{
					pos_map.x=pos_map.x-y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvtg4,NULL,screen,NULL);
					SDL_Flip(screen);
					i=4; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 4:
				{
					pos_map.x=pos_map.x-y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvtg5,NULL,screen,NULL);
					SDL_Flip(screen);
					i=5; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 5:
				{
					pos_map.x=pos_map.x-y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvtg6,NULL,screen,NULL);
					SDL_Flip(screen);
					i=6; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 6:
				{
					pos_map.x=pos_map.x-y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvtg7,NULL,screen,NULL);
					SDL_Flip(screen);
					i=7; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 7:
				{
					pos_map.x=pos_map.x-y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvtg8,NULL,screen,NULL);
					SDL_Flip(screen);
					i=8; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 8:
				{
					pos_map.x=pos_map.x-y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvtg9,NULL,screen,NULL);
					SDL_Flip(screen);
					i=9;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 9:
				{
					pos_map.x=pos_map.x-y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvtg10,NULL,screen,NULL);
					SDL_Flip(screen);
					i=10;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 10:
				{
					pos_map.x=pos_map.x-y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvtg11,NULL,screen,NULL);
					SDL_Flip(screen);
					i=11;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 11:
				{
					pos_map.x=pos_map.x-y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvtg12,NULL,screen,NULL);
					SDL_Flip(screen);
					i=12;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 12:
				{
					pos_map.x=pos_map.x-y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvtg13,NULL,screen,NULL);
					SDL_Flip(screen);
					i=13; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 13:
				{
					pos_map.x=pos_map.x-y;
					SDL_BlitSurface(back,&pos_map,screen,NULL);
					SDL_BlitSurface(mvtg0,NULL,screen,NULL);
					SDL_Flip(screen);
					i=0; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
			}

		}
		else if (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_UP && droite==1)
		{
			switch (i)
			{
				case 0:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt1,NULL,screen,&pos);
					SDL_Flip(screen);
					i=1;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 1:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt2,NULL,screen,&pos);
					SDL_Flip(screen);		
					i=2;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;		
				}
				case 2:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt3,NULL,screen,&pos);
					SDL_Flip(screen);
					i=3;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 3:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt4,NULL,screen,&pos);
					SDL_Flip(screen);
					i=4; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 4:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt5,NULL,screen,&pos);
					SDL_Flip(screen);
					i=5; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 5:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt6,NULL,screen,&pos);
					SDL_Flip(screen);
					i=6; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 6:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt7,NULL,screen,&pos);
					SDL_Flip(screen);
					i=7; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 7:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt8,NULL,screen,&pos);
					SDL_Flip(screen);
					i=8; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 8:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt9,NULL,screen,&pos);
					SDL_Flip(screen);
					i=9;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 9:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt10,NULL,screen,&pos);
					SDL_Flip(screen);
					i=10;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 10:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt11,NULL,screen,&pos);
					SDL_Flip(screen);
					i=11;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 11:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt12,NULL,screen,&pos);
					SDL_Flip(screen);
					i=12;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 12:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt13,NULL,screen,&pos);
					SDL_Flip(screen);
					i=13; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 13:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt0,NULL,screen,&pos);
					SDL_Flip(screen);
					i=0; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
			}

		}
		else if (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_DOWN && droite==1)
		{
			switch (i)
			{
				case 0:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt1,NULL,screen,&pos);
					SDL_Flip(screen);
					i=1;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 1:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt2,NULL,screen,&pos);
					SDL_Flip(screen);		
					i=2;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;		
				}
				case 2:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt3,NULL,screen,&pos);
					SDL_Flip(screen);
					i=3;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 3:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt4,NULL,screen,&pos);
					SDL_Flip(screen);
					i=4; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 4:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt5,NULL,screen,&pos);
					SDL_Flip(screen);
					i=5; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 5:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt6,NULL,screen,&pos);
					SDL_Flip(screen);
					i=6; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 6:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt7,NULL,screen,&pos);
					SDL_Flip(screen);
					i=7; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 7:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt8,NULL,screen,&pos);
					SDL_Flip(screen);
					i=8; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 8:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt9,NULL,screen,&pos);
					SDL_Flip(screen);
					i=9;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 9:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt10,NULL,screen,&pos);
					SDL_Flip(screen);
					i=10;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 10:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt11,NULL,screen,&pos);
					SDL_Flip(screen);
					i=11;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 11:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt12,NULL,screen,&pos);
					SDL_Flip(screen);
					i=12;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 12:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt13,NULL,screen,&pos);
					SDL_Flip(screen);
					i=13; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 13:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvt0,NULL,screen,&pos);
					SDL_Flip(screen);
					i=0; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
			}

		}
		if (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_UP && droite==0)
		{
			switch (i)
			{
				case 0:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg1,NULL,screen,&pos);
					SDL_Flip(screen);
					i=1;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 1:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg2,NULL,screen,&pos);
					SDL_Flip(screen);		
					i=2;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;		
				}
				case 2:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg3,NULL,screen,&pos);
					SDL_Flip(screen);
					i=3;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 3:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg4,NULL,screen,&pos);
					SDL_Flip(screen);
					i=4; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 4:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg5,NULL,screen,&pos);
					SDL_Flip(screen);
					i=5; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 5:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg6,NULL,screen,&pos);
					SDL_Flip(screen);
					i=6; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 6:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg7,NULL,screen,&pos);
					SDL_Flip(screen);
					i=7; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 7:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg8,NULL,screen,&pos);
					SDL_Flip(screen);
					i=8; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 8:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg9,NULL,screen,&pos);
					SDL_Flip(screen);
					i=9;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 9:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg10,NULL,screen,&pos);
					SDL_Flip(screen);
					i=10;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 10:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg11,NULL,screen,&pos);
					SDL_Flip(screen);
					i=11;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 11:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg12,NULL,screen,&pos);
					SDL_Flip(screen);
					i=12;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 12:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg13,NULL,screen,&pos);
					SDL_Flip(screen);
					i=13; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 13:
				{
					pos.y=pos.y-y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg0,NULL,screen,&pos);
					SDL_Flip(screen);
					i=0; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
			}

		}
		if (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_DOWN && droite==0)
		{
			switch (i)
			{
				case 0:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg1,NULL,screen,&pos);
					SDL_Flip(screen);
					i=1;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 1:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg2,NULL,screen,&pos);
					SDL_Flip(screen);		
					i=2;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;		
				}
				case 2:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg3,NULL,screen,&pos);
					SDL_Flip(screen);
					i=3;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 3:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg4,NULL,screen,&pos);
					SDL_Flip(screen);
					i=4; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 4:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg5,NULL,screen,&pos);
					SDL_Flip(screen);
					i=5; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 5:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg6,NULL,screen,&pos);
					SDL_Flip(screen);
					i=6; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 6:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg7,NULL,screen,&pos);
					SDL_Flip(screen);
					i=7; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 7:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg8,NULL,screen,&pos);
					SDL_Flip(screen);
					i=8; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 8:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg9,NULL,screen,&pos);
					SDL_Flip(screen);
					i=9;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 9:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg10,NULL,screen,&pos);
					SDL_Flip(screen);
					i=10;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 10:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg11,NULL,screen,&pos);
					SDL_Flip(screen);
					i=11;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 11:
				{
					pos.y=pos.y+y;
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg12,NULL,screen,&pos);
					SDL_Flip(screen);
					i=12;
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 12:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg13,NULL,screen,&pos);
					SDL_Flip(screen);
					i=13; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
				case 13:
				{
					if (pos.y<175)
					{
						pos.y=pos.y+y;
					}
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(mvtg0,NULL,screen,&pos);
					SDL_Flip(screen);
					i=0; 
					do
					{
						actuel=SDL_GetTicks();
					}
					while (actuel-precedent<70);
					precedent=actuel;
					break;
				}
			}

		}
	}
	while (continuer==1);








	SDL_FreeSurface(screen);
	SDL_FreeSurface(back);
	SDL_FreeSurface(mvt0);
	SDL_FreeSurface(mvt13);
	SDL_FreeSurface(mvt12);
	SDL_FreeSurface(mvt11);
	SDL_FreeSurface(mvt10);
	SDL_FreeSurface(mvt9);
	SDL_FreeSurface(mvt8);
	SDL_FreeSurface(mvt7);
	SDL_FreeSurface(mvt6);
	SDL_FreeSurface(mvt5);
	SDL_FreeSurface(mvt4);
	SDL_FreeSurface(mvt3);
	SDL_FreeSurface(mvt2);
	SDL_FreeSurface(mvt1);
	SDL_FreeSurface(mvtg0);
	SDL_FreeSurface(mvtg1);
	SDL_FreeSurface(mvtg2);
	SDL_FreeSurface(mvtg3);
	SDL_FreeSurface(mvtg4);
	SDL_FreeSurface(mvtg5);
	SDL_FreeSurface(mvtg6);
	SDL_FreeSurface(mvtg7);
	SDL_FreeSurface(mvtg8);
	SDL_FreeSurface(mvtg9);
	SDL_FreeSurface(mvtg10);
	SDL_FreeSurface(mvtg11);
	SDL_FreeSurface(mvtg12);
	SDL_FreeSurface(mvtg13);
	SDL_Quit();
	return 0;
}