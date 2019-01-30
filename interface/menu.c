#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>




int main(int argc, char  *argv[])
{
	SDL_Surface *back=NULL, *menu=NULL, *new=NULL, *continu=NULL, *option=NULL, *quit=NULL, *screen=NULL, *fullscreen_on=NULL, *fullscreen_on_appui=NULL, *fullscreen_off=NULL,*fullscreen_off_appui=NULL,*sound_on=NULL,*sound_on_appui=NULL,*sound_off=NULL,*sound_off_appui=NULL,*retour=NULL,*retour_appui=NULL;
	SDL_Event event;
	int x=0,i,j,sound=1,fullscreen=1,appui=1,page=1,appui_full=0,appui_sound=0,appui_retour=0;
	Mix_Music *musique;

	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
	screen=SDL_SetVideoMode(1280,768,32,SDL_HWSURFACE | SDL_DOUBLEBUF );
	musique=Mix_LoadMUS("chat.ogg");
	back=IMG_Load("Interfaz.jpg");
	menu=IMG_Load("menu interface.png");
	new=IMG_Load("menu interface new game.png");
	continu=IMG_Load("menu interface continue.png");
	option=IMG_Load("menu interface option.png");
	quit=IMG_Load("menu interface quit.png");
	fullscreen_off=IMG_Load("option fullscreen off.png");
	fullscreen_off_appui=IMG_Load("option fullscreen off apui.png");
	fullscreen_on=IMG_Load("option fullscreen on.png");
	fullscreen_on_appui=IMG_Load("option fullscreen on appui.png");
	sound_off=IMG_Load("option sound off.png");
	sound_off_appui=IMG_Load("option sound off appui.png");
	sound_on=IMG_Load("option sound on.png");
	sound_on_appui=IMG_Load("option sound on appui.png");
	retour=IMG_Load("fleche retour.png");
	retour_appui=IMG_Load("fleche retour appui.png");
	SDL_BlitSurface(back,NULL,screen,NULL);
	SDL_BlitSurface(menu,NULL,screen,NULL);
	SDL_Flip(screen);
	

	Mix_VolumeMusic(128);
	Mix_PlayMusic(musique,-1);

	do
	{
		SDL_PollEvent(&event);
		if (event.type==SDL_QUIT || event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE || event.type==SDL_MOUSEBUTTONUP && event.button.button==SDL_BUTTON_LEFT && event.button.x>503 && event.button.x<738 && event.button.y>595 && event.button.y<642)
		{
			x=1;
		}
		if (page==0)
		{
			SDL_BlitSurface(back,NULL,screen,NULL);
			SDL_BlitSurface(menu,NULL,screen,NULL);
			SDL_Flip(screen);
			page=1;
		}
		else if (page==1)
		{
			if (event.button.x>504 && event.button.x <764 && event.button.y>334 && event.button.y<373)
			{
				SDL_BlitSurface(new,NULL,screen,NULL);
				SDL_Flip(screen);
				appui=0;
			}
			else if (event.button.x>500 && event.button.x <756 && event.button.y>426 && event.button.y<462)
			{
				SDL_BlitSurface(continu,NULL,screen,NULL);
				SDL_Flip(screen);
				appui=0;
			}
			else if (event.button.x>520 && event.button.x <742 && event.button.y>515 && event.button.y<550)
			{
				SDL_BlitSurface(option,NULL,screen,NULL);
				SDL_Flip(screen);
				appui=0;
			}
			else if (event.button.x>537 && event.button.x <716 && event.button.y>606 && event.button.y<634)
			{
				SDL_BlitSurface(quit,NULL,screen,NULL);
				SDL_Flip(screen);
				appui=0;
			}
			else
			{
				if (appui==0)
				{
					SDL_BlitSurface(menu,NULL,screen,NULL);
					SDL_Flip(screen);
					appui=1;
				}
			}
		}
		if (event.button.x>520 && event.button.x <742 && event.button.y>515 && event.button.y<550  && event.type==SDL_MOUSEBUTTONUP && event.button.button==SDL_BUTTON_LEFT )
		{
			page=2;
			SDL_BlitSurface(back,NULL,screen,NULL);
			SDL_BlitSurface(retour,NULL,screen,NULL);
			if (fullscreen==1)
			{
				SDL_BlitSurface(fullscreen_on,NULL,screen,NULL);
			}
			else 
			{
				SDL_BlitSurface(fullscreen_off,NULL,screen,NULL);
			}
			if (sound==1)
			{
				SDL_BlitSurface(sound_on,NULL,screen,NULL);
			}
			else
			{
				SDL_BlitSurface(sound_off,NULL,screen,NULL);
			}
			SDL_Flip(screen);
		}
		if (page==2)
		{
			if (event.button.x>492 && event.button.x<762 && event.button.y>304 && event.button.y<356)
			{
				if (fullscreen==1)
				{
					SDL_BlitSurface(fullscreen_on_appui,NULL,screen,NULL);
				}
				else 
				{
					SDL_BlitSurface(fullscreen_off_appui,NULL,screen,NULL);
				}
				SDL_Flip(screen);
				appui_full=1;
			}
			else if (event.button.x>518 && event.button.x<736 && event.button.y>531 && event.button.y<588)
			{
				if (sound==1)
				{
					SDL_BlitSurface(sound_on_appui,NULL,screen,NULL);
				}
				else
				{
					SDL_BlitSurface(sound_off_appui,NULL,screen,NULL);
				}
				SDL_Flip(screen);
				appui_sound=1;
			}
			else if (event.button.x>0 && event.button.x<104 && event.button.y>0 && event.button.y<80)
			{
				SDL_BlitSurface(retour_appui,NULL,screen,NULL);
				SDL_Flip(screen);
				appui_retour=1;
			}
			else 
			{
				if (appui_full==1)
				{
					if (fullscreen==1)
					{
						SDL_BlitSurface(fullscreen_on,NULL,screen,NULL);
					}
					else 
					{
						SDL_BlitSurface(fullscreen_off,NULL,screen,NULL);
					}
					SDL_Flip(screen);
					appui_full=0;
				}
				if (appui_sound==1)
				{
					if (sound==1)
					{
						SDL_BlitSurface(sound_on,NULL,screen,NULL);
					}
					else
					{
						SDL_BlitSurface(sound_off,NULL,screen,NULL);
					}
					SDL_Flip(screen);
					appui_sound=0;
				}
				if (appui_retour==1)
				{
					SDL_BlitSurface(retour,NULL,screen,NULL);
					SDL_Flip(screen);
					appui_retour=0;
				}
			}
			if (event.button.x>492 && event.button.x<762 && event.button.y>304 && event.button.y<356 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)
			{
				if (fullscreen==1)
				{
					screen=SDL_SetVideoMode(1280,768,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(fullscreen_off,NULL,screen,NULL);
					SDL_BlitSurface(retour,NULL,screen,NULL);
					fullscreen=0;
					if (sound==1)
					{
						SDL_BlitSurface(sound_on,NULL,screen,NULL);
					}
					else 
					{
						SDL_BlitSurface(sound_off,NULL,screen,NULL);
					}
				}
				else 
				{
					screen=SDL_SetVideoMode(1280,768,32,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(fullscreen_on,NULL,screen,NULL);
					SDL_BlitSurface(retour,NULL,screen,NULL);
					fullscreen=1;
					if (sound==1)
					{
						SDL_BlitSurface(sound_on,NULL,screen,NULL);
					}
					else 
					{
						SDL_BlitSurface(sound_off,NULL,screen,NULL);
					}

				}
				SDL_Flip(screen);
				SDL_Delay(100);
			}
			else if (event.button.x>518 && event.button.x<736 && event.button.y>531 && event.button.y<588 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)
			{
				if (sound==1)
				{
					SDL_BlitSurface(sound_off,NULL,screen,NULL);
					sound=0;
					Mix_VolumeMusic(0);
				}
				else
				{
					SDL_BlitSurface(sound_on,NULL,screen,NULL);
					sound=1;
					Mix_VolumeMusic(128);
				}
				SDL_Flip(screen);
				SDL_Delay(100);
			}
			else if (event.button.x>0 && event.button.x<104 && event.button.y>0 && event.button.y<80 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)
			{
				page=0;
			}
		}
	}
	while (x==0);

	SDL_FreeSurface(screen);
	SDL_FreeSurface(back);
	SDL_FreeSurface(new);
	SDL_FreeSurface(continu);
	SDL_FreeSurface(option);
	SDL_FreeSurface(quit);
	SDL_FreeSurface(menu);
	SDL_FreeSurface(sound_on);
	SDL_FreeSurface(sound_on_appui);
	SDL_FreeSurface(sound_off);
	SDL_FreeSurface(sound_off_appui);
	SDL_FreeSurface(fullscreen_on);
	SDL_FreeSurface(fullscreen_on_appui);
	SDL_FreeSurface(fullscreen_off);
	SDL_FreeSurface(fullscreen_off_appui);
	SDL_Quit();
	Mix_FreeMusic(musique);
	Mix_CloseAudio();
	return 0;
}