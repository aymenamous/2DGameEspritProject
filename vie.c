#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

int main(int argc, char const *argv[])
{
	SDL_Surface *screen=NULL, *barre=NULL, *bar=NULL;
	int continuer=1;
	SDL_Event event;
	SDL_Rect pos;
	SDL_Init(SDL_INIT_EVERYTHING);
	screen=SDL_SetVideoMode(800,600,32,SDL_SWSURFACE);
	barre=SDL_CreateRGBSurface(SDL_SWSURFACE,200,25,32,0,0,0,0);
	SDL_FillRect(barre,NULL,SDL_MapRGB(barre->format,255,255,255));
	SDL_BlitSurface(barre,NULL,screen,NULL);
	SDL_Flip(screen);
	pos.x=175;
	pos.y=0;
	do
	{
		SDL_WaitEvent(&event);
		if (event.type==SDL_KEYDOWN)
		{
			bar=SDL_CreateRGBSurface(SDL_SWSURFACE,25,25,32,0,0,0,0);
			SDL_FillRect(bar,NULL,SDL_MapRGB(bar->format,0,0,0));
			SDL_BlitSurface(bar,NULL,screen,&pos);
			SDL_Flip(screen);
			pos.x=pos.x-25;

		}
		else if (event.type==SDL_QUIT)
		{
			continuer=0;
		}
	} while (continuer==1);




	SDL_FreeSurface(screen);
	SDL_FreeSurface(barre);
	
	SDL_Quit();

	return 0;
}