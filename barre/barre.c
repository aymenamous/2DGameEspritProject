#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


int main(int argc, char *argv[])
{
	SDL_Surface *screen=NULL, *barre=NULL, *vie=NULL, *mana=NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Rect pos;
	barre=IMG_Load("barre.png");
	vie=IMG_Load("vie.png");
	pos.x=0;
	pos.y=0;
	pos.w=200;
	pos.h=768;
	screen=SDL_SetVideoMode(800,600,32,SDL_SWSURFACE);
	SDL_BlitSurface(barre,NULL,screen,NULL);
	SDL_BlitSurface(vie,&pos,screen,NULL);
	SDL_Flip(screen);
	SDL_Delay(3000);
	SDL_Quit();


	return 0;
}