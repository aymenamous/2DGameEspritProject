#include <SDL/SDL.h>
#include <SDL/SDL_image.h>




int main(int argc, char  *argv[])
{
	SDL_Surface *pose_cbt=NULL, *attaque1=NULL, *screen=NULL, *back=NULL, *trai[4]={NULL};
	int continuer=1;
	SDL_Event event;
	SDL_Rect pos_trait;



	SDL_Init(SDL_INIT_EVERYTHING);
	screen=SDL_SetVideoMode(1280,768,32,SDL_SWSURFACE);
	back=IMG_Load("Untitled-1.png");
	trai[0]=IMG_Load("attack1 trait1.png");
	trai[1]=IMG_Load("attack1 trait2.png");
	trai[2]=IMG_Load("attack1 trait3.png");
	trai[3]=IMG_Load("attack1 trait4.png");
	pose_cbt=IMG_Load("pose combat_raiden.png");
	attaque1=IMG_Load("attaque 1 .png");
	SDL_BlitSurface(back,NULL,screen,NULL);
	SDL_BlitSurface(pose_cbt,NULL,screen,NULL);
	SDL_Flip(screen);
	
	do
	{
		SDL_PollEvent(&event);
		if (event.type==SDL_QUIT)
		{
			continuer=0;
		}
		else if (event.type==SDL_KEYDOWN)
		{
			pos_trait.x=500;
			pos_trait.y=200;
			SDL_BlitSurface(back,NULL,screen,NULL);
			SDL_BlitSurface(attaque1,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(100);
			SDL_BlitSurface(back,NULL,screen,NULL);
			SDL_BlitSurface(pose_cbt,NULL,screen,NULL);
			SDL_BlitSurface(trai[0],NULL,screen,&pos_trait);
			SDL_Flip(screen);
			do
			{
				pos_trait.x=pos_trait.x+20;
				SDL_BlitSurface(back,NULL,screen,NULL);
				SDL_BlitSurface(pose_cbt,NULL,screen,NULL);
				if (pos_trait.x<760)
					{
						SDL_BlitSurface(trai[0],NULL,screen,&pos_trait);
					}
				else if (pos_trait.x<900)
				{
					SDL_BlitSurface(trai[1],NULL,screen,&pos_trait);
				}
				else  if (pos_trait.x<1000)
				{
					SDL_BlitSurface(trai[2],NULL,screen,&pos_trait);
				}
				else
				{
					SDL_BlitSurface(trai[3],NULL,screen,&pos_trait);
				}
				SDL_Flip(screen);
			}
			while(pos_trait.x<1280);
		}


	}
	while (continuer==1);

	SDL_FreeSurface(back);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(trai[0]);
	SDL_FreeSurface(trai[1]);
	SDL_FreeSurface(trai[2]);
	SDL_FreeSurface(trai[3]);
	SDL_FreeSurface(pose_cbt);
	SDL_FreeSurface(attaque1);
	SDL_Quit();	
	return 0;
}