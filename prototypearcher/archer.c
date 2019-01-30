#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

int main(int argc, char *argv[])
{
	SDL_Surface *pose[3]={NULL}, *back=NULL, *screen=NULL, *arrow =NULL;
	int i=0,continuer=1,precedent=0,actuel=0;
	SDL_Event event;
	SDL_Rect pos,arr;

	SDL_Init(SDL_INIT_EVERYTHING);
	screen=SDL_SetVideoMode(1280,768,32,SDL_SWSURFACE);
	SDL_WM_SetCaption("archer",NULL);
	pose[0]=IMG_Load("archer mvt1.png");
	pose[1]=IMG_Load("archer first mvt.png");
	pose[2]=IMG_Load("archer final mvt.png");
	back=IMG_Load("lvl1.jpg");
	arrow=IMG_Load("fleche1.png");
	SDL_BlitSurface(back,NULL,screen,NULL);
	pos.x=800;
	pos.y=100;
	SDL_BlitSurface(pose[i],NULL,screen,&pos);
	SDL_Flip(screen);
	arr.x=180;
	arr.y=0;
	
	do
	{
		SDL_PollEvent(&event);
		if (event.type==SDL_QUIT)
		{
			continuer=0;
		}

		if (event.type==SDL_KEYDOWN)
		{
			for (i=0;i<3;i++)
			{
				SDL_BlitSurface(back,NULL,screen,NULL);
				SDL_BlitSurface(pose[i],NULL,screen,&pos);
				if (i==2)
				{
					SDL_BlitSurface(arrow,NULL,screen,&arr);
				}
				SDL_Flip(screen);
				SDL_Delay(100);
			}
		}
	}
	while (continuer==1);

	SDL_FreeSurface(back);
	SDL_FreeSurface(screen);
	SDL_FreeSurface(pose[0]);
	SDL_FreeSurface(pose[1]);
	SDL_FreeSurface(pose[2]);
	SDL_FreeSurface(arrow);

	return 0;
}