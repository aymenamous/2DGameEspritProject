#include "menu.h"
#include "lvl1.h"


int main ()
{
	int valeur,sound=1, fullscreen=0,passage,video;
	SDL_Surface *screen=NULL, *stage1=NULL,*stage2=NULL, *stage3=NULL, *stage4=NULL, *stage5=NULL;
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        exit(EXIT_FAILURE);
    }
	SDL_WM_SetIcon(IMG_Load("phoenix.png"), NULL);//icone du jeu
	screen=SDL_SetVideoMode(1280,768,32,SDL_SWSURFACE | SDL_DOUBLEBUF );
	if (screen == NULL)
    {
        exit(EXIT_FAILURE);
    }
	SDL_WM_SetCaption("The Legend Of The Phoenix",NULL);
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
	Mix_AllocateChannels(10);
	Mix_VolumeMusic(128);
	stage1=SDL_DisplayFormatAlpha(IMG_Load("lvl1.png"));
	stage2=SDL_DisplayFormatAlpha(IMG_Load("back lvl2.jpg"));
	stage3=SDL_DisplayFormatAlpha(IMG_Load("back lvl3.png"));
	stage4=SDL_DisplayFormatAlpha(IMG_Load("lvl1.png"));
	stage5=SDL_DisplayFormatAlpha(IMG_Load("back lvl5.jpg"));
	

	do
	{
		valeur=menu(screen,&sound,&fullscreen);//ouvertue du menu et retour d'une valeur,1=New game, 0=quit->sortie de la boucle et fin du programme
		if (valeur==1)
		{
			passage=lvl_1(screen,stage1,&sound,&fullscreen);
			if (passage==1)
			{
				passage=lvl_2(screen,stage2,&sound,&fullscreen);
				if (passage==1)
				{
					passage=lvl_3(screen,stage3,&sound,&fullscreen);
					if (passage==1)
					{
						passage=lvl_4(screen,stage4,&sound,&fullscreen);
						if (passage==1)
						{
							passage=lvl_5(screen,stage5,&sound,&fullscreen);
						}
					}
				}
			}
		}
		if (valeur==2)
		{
			passage=lvl_1(screen,stage1,&sound,&fullscreen);
			if (passage==1)
			{
				passage=lvl_2(screen,stage2,&sound,&fullscreen);
				if (passage==1)
				{
					passage=lvl_3(screen,stage3,&sound,&fullscreen);
					if (passage==1)
					{
						passage=lvl_4(screen,stage4,&sound,&fullscreen);
						if (passage==1)
						{
							passage=lvl_5(screen,stage5,&sound,&fullscreen);
						}
					}
				}
			}
		}
		if (valeur==3)
		{
			passage=lvl_2(screen,stage2,&sound,&fullscreen);
			if (passage==1)
			{
				passage=lvl_3(screen,stage3,&sound,&fullscreen);
				if (passage==1)
				{
					passage=lvl_4(screen,stage4,&sound,&fullscreen);
					if (passage==1)
					{
						passage=lvl_5(screen,stage5,&sound,&fullscreen);
					}
				}
			}
		}
		if (valeur==4)
		{
			passage=lvl_3(screen,stage3,&sound,&fullscreen);
			if (passage==1)
			{
				passage=lvl_4(screen,stage4,&sound,&fullscreen);
				if (passage==1)
				{
					passage=lvl_5(screen,stage5,&sound,&fullscreen);
				}
			}
		}
		if (valeur==5)
		{
			passage=lvl_4(screen,stage4,&sound,&fullscreen);
			if (passage==1)
			{
				passage=lvl_5(screen,stage5,&sound,&fullscreen);
			}
		}
		if (valeur==6)
		{
			passage=lvl_5(screen,stage5,&sound,&fullscreen);
		}
	}
	while (valeur!=0);


	SDL_FreeSurface(stage1);
	SDL_FreeSurface(stage2);
	SDL_FreeSurface(stage3);
	SDL_FreeSurface(stage4);
	SDL_FreeSurface(stage5);
	SDL_FreeSurface(screen);
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}