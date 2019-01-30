#include "menu.h"
#include "var.h"




int  menu(SDL_Surface *screen, int *sound, int *fullscreen)
{
	SDL_Surface *back=NULL, *menu=NULL, *new=NULL, *choose_lvl=NULL, *option=NULL, *quit=NULL, *fullscreen_on=NULL, *fullscreen_on_appui=NULL, *fullscreen_off=NULL,*fullscreen_off_appui=NULL,*sound_on=NULL,*sound_on_appui=NULL,*sound_off=NULL,*sound_off_appui=NULL,*retour=NULL,*retour_appui=NULL, *page_lvl[6]={NULL};
	SDL_Event event;
	int x=0,i,j,appui=1,page=1,appui_full=0,appui_sound=0,appui_retour=0,valeur;
	Mix_Music *musique;

	
	musique=Mix_LoadMUS("11 Don_t Die With A Clean Sword.mp3");//musique du menu
	back=SDL_DisplayFormatAlpha(IMG_Load("Interfaz.jpg")); //background
	menu=SDL_DisplayFormatAlpha(IMG_Load("menu interface.png")); //menu
	new=SDL_DisplayFormatAlpha(IMG_Load("menu interface new game.png"));// New gam en rouge (quand le curseur est sur cette case)
	choose_lvl=SDL_DisplayFormatAlpha(IMG_Load("choose lvl.png"));// choose_lvl en rouge
	option=SDL_DisplayFormatAlpha(IMG_Load("menu interface option.png"));// option en rouge
	quit=SDL_DisplayFormatAlpha(IMG_Load("menu interface quit.png"));//quit en rouge
	fullscreen_off=SDL_DisplayFormatAlpha(IMG_Load("option fullscreen off.png"));//image fullscreen off
	fullscreen_off_appui=SDL_DisplayFormatAlpha(IMG_Load("option fullscreen off apui.png"));//image fullscreen off rouge
	fullscreen_on=SDL_DisplayFormatAlpha(IMG_Load("option fullscreen on.png")); //image fullscreen on
	fullscreen_on_appui=SDL_DisplayFormatAlpha(IMG_Load("option fullscreen on appui.png"));//image fullscreen on rouge
	sound_off=SDL_DisplayFormatAlpha(IMG_Load("option sound off.png"));//image sound off
	sound_off_appui=SDL_DisplayFormatAlpha(IMG_Load("option sound off appui.png"));//image sound off rouge
	sound_on=SDL_DisplayFormatAlpha(IMG_Load("option sound on.png"));//image sound on rouge
	sound_on_appui=SDL_DisplayFormatAlpha(IMG_Load("option sound on appui.png"));//image sound on rouge
	retour=SDL_DisplayFormatAlpha(IMG_Load("fleche retour.png")); //flèche de retour
	retour_appui=SDL_DisplayFormatAlpha(IMG_Load("fleche retour appui.png"));//flèche de retour rouge
	page_lvl[0]=SDL_DisplayFormatAlpha(IMG_Load("interface lvl.png"));
	page_lvl[1]=SDL_DisplayFormatAlpha(IMG_Load("lv1.png"));
	page_lvl[2]=SDL_DisplayFormatAlpha(IMG_Load("lv2.png"));
	page_lvl[3]=SDL_DisplayFormatAlpha(IMG_Load("lv3.png"));
	page_lvl[4]=SDL_DisplayFormatAlpha(IMG_Load("lv4.png"));
	page_lvl[5]=SDL_DisplayFormatAlpha(IMG_Load("final.png"));
	SDL_BlitSurface(back,NULL,screen,NULL);// affichage de la background
	SDL_BlitSurface(menu,NULL,screen,NULL);//affichage du menu
	SDL_Flip(screen);
	
	Mix_PlayMusic(musique,-1);

	do
	{
		SDL_WaitEvent(&event);
		if (event.type==SDL_QUIT || event.type==SDL_MOUSEBUTTONUP && event.button.button==SDL_BUTTON_LEFT && event.button.x>503 && event.button.x<738 && event.button.y>595 && event.button.y<642 && page==1) //si on appui sur quitter ou sur la croix en haut a gauche->fermuture du jeu
		{
			x=1;
			valeur=0;
		}
		if (page==0) //page vide (retour en arrière depuis le menu option)->affichage du menu de départ
		{
			SDL_BlitSurface(back,NULL,screen,NULL);
			SDL_BlitSurface(menu,NULL,screen,NULL);
			SDL_Flip(screen);
			page=1;
		}
		else if (page==1) //menu de départ affiché
		{
			if (event.button.x>504 && event.button.x <764 && event.button.y>334 && event.button.y<373)//position du curseur sur New game
			{
				SDL_BlitSurface(new,NULL,screen,NULL);
				SDL_Flip(screen);
				appui=0;
			}
			else if (event.button.x>500 && event.button.x <756 && event.button.y>426 && event.button.y<462)//position du curseur sur choose_lvl
			{
				SDL_BlitSurface(choose_lvl,NULL,screen,NULL);
				SDL_Flip(screen);
				appui=0;
			}
			else if (event.button.x>520 && event.button.x <742 && event.button.y>515 && event.button.y<550) //position du curseur sur option
			{
				SDL_BlitSurface(option,NULL,screen,NULL);
				SDL_Flip(screen);
				appui=0;
			}
			else if (event.button.x>537 && event.button.x <716 && event.button.y>606 && event.button.y<634) //position du curseur sur quit
			{
				SDL_BlitSurface(quit,NULL,screen,NULL);
				SDL_Flip(screen);
				appui=0;
			}
			else
			{
				if (appui==0) //si une case est appuiée et le curseur n'est plus sur cette case->réaffichage du menu sans cases rouges
				{
					SDL_BlitSurface(menu,NULL,screen,NULL);
					SDL_Flip(screen);
					appui=1;
				}
			}
		}
		if (event.button.x>520 && event.button.x <742 && event.button.y>515 && event.button.y<550  && event.type==SDL_MOUSEBUTTONUP && event.button.button==SDL_BUTTON_LEFT && page==1 ) //si on appuie sur option
		{
			page=2; //position: menu option
			SDL_BlitSurface(back,NULL,screen,NULL);
			SDL_BlitSurface(retour,NULL,screen,NULL);// afficher la flèche de retour qui permet de retourner au menu précedent
			if (*fullscreen==1) //vérification de l'état de fullscreen afin d'afficher l'image correspondante (on ou off)
			{
				SDL_BlitSurface(fullscreen_on,NULL,screen,NULL);
			}
			else 
			{
				SDL_BlitSurface(fullscreen_off,NULL,screen,NULL);
			}
			if (*sound==1) //même chose pour sound
			{
				SDL_BlitSurface(sound_on,NULL,screen,NULL);
			}
			else
			{
				SDL_BlitSurface(sound_off,NULL,screen,NULL);
			}
			SDL_Flip(screen);
		}
		else if (event.button.x>500 && event.button.x <756 && event.button.y>426 && event.button.y<462 && event.type==SDL_MOUSEBUTTONUP && event.button.button==SDL_BUTTON_LEFT && page==1)
		{
			page=3;
			SDL_BlitSurface(back,NULL,screen,NULL);
			SDL_BlitSurface(page_lvl[0],NULL,screen,NULL);
			SDL_BlitSurface(retour,NULL,screen,NULL);
			SDL_Flip(screen);
		}
		else if (event.button.x>504 && event.button.x <764 && event.button.y>334 && event.button.y<373 && event.type==SDL_MOUSEBUTTONUP && event.button.button==SDL_BUTTON_LEFT && page==1)// si on appui sur New game, sortie de la boucle et valeur 1 signifie commencer le jeu
		{
			x=1;
			valeur=1;
		}
		if (page==2) //menu option
		{
			if (event.button.x>492 && event.button.x<762 && event.button.y>304 && event.button.y<356) //si curseur sur fullscreen->affichage de ce dernier en rouge
			{
				if (*fullscreen==1)
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
			else if (event.button.x>518 && event.button.x<736 && event.button.y>531 && event.button.y<588)//si curseur sur sound->affichage de ce dernier en rouge
			{
				if (*sound==1)
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
			else if (event.button.x>0 && event.button.x<104 && event.button.y>0 && event.button.y<80)//si curseur sur la flèche de retour
			{
				SDL_BlitSurface(retour_appui,NULL,screen,NULL);
				SDL_Flip(screen);
				appui_retour=1;
			}
			else 
			{
				if (appui_full==1)//si une case est en rouge et le curseur n'est plus sur cette case ->revenir a l'état par défault (appui_full=case fullscreen en rouge)
				{
					if (*fullscreen==1)
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
				if (appui_sound==1) //si une case est en rouge et le curseur n'est plus sur cette case ->revenir a l'état par défault (appui_sound=case sound en rouge)
				{
					if (*sound==1)
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
				if (appui_retour==1)//si une case est en rouge et le curseur n'est plus sur cette case ->revenir a l'état par défault (appui_retour=case retour en rouge)
				{
					SDL_BlitSurface(retour,NULL,screen,NULL);
					SDL_Flip(screen);
					appui_retour=0;
				}
			}
			if (event.button.x>492 && event.button.x<762 && event.button.y>304 && event.button.y<356 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)//si on appuie sur "fullscreen"->changement d'état
			{
				if (*fullscreen==1)
				{
					screen=SDL_SetVideoMode(1280,768,32,SDL_SWSURFACE | SDL_DOUBLEBUF);
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(fullscreen_off,NULL,screen,NULL);
					SDL_BlitSurface(retour,NULL,screen,NULL);
					*fullscreen=0;
					if (*sound==1)
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
					screen=SDL_SetVideoMode(1280,768,32,SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(fullscreen_on,NULL,screen,NULL);
					SDL_BlitSurface(retour,NULL,screen,NULL);
					*fullscreen=1;
					if (*sound==1)
					{
						SDL_BlitSurface(sound_on,NULL,screen,NULL);
					}
					else 
					{
						SDL_BlitSurface(sound_off,NULL,screen,NULL);
					}

				}
				SDL_Flip(screen);
			}
			else if (event.button.x>518 && event.button.x<736 && event.button.y>531 && event.button.y<588 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)// si on appuie sur sound->changement d'état
			{
				if (*sound==1)
				{
					SDL_BlitSurface(sound_off,NULL,screen,NULL);
					*sound=0;
					Mix_VolumeMusic(0);
				}
				else
				{
					SDL_BlitSurface(sound_on,NULL,screen,NULL);
					*sound=1;
					Mix_VolumeMusic(128);
				}
				SDL_Flip(screen);
			}
			else if (event.button.x>0 && event.button.x<104 && event.button.y>0 && event.button.y<80 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)//si on appuie sur la flèche de retour->retour au menu initial
			{
				page=0;
			}
		}
		if (page==3)
		{
			if (event.button.x>520 && event.button.x<733 && event.button.y>239 && event.button.y<278)
			{
				SDL_BlitSurface(page_lvl[1],NULL,screen,NULL);
				SDL_Flip(screen);
			}
			else if (event.button.x>520 && event.button.x<733 && event.button.y>322 && event.button.y<367)
			{
				SDL_BlitSurface(page_lvl[2],NULL,screen,NULL);
				SDL_Flip(screen);
			}
			else if (event.button.x>520 && event.button.x<733 && event.button.y>416 && event.button.y<458)
			{
				SDL_BlitSurface(page_lvl[3],NULL,screen,NULL);
				SDL_Flip(screen);
			}
			else if (event.button.x>520 && event.button.x<733 && event.button.y>512 && event.button.y<550)
			{
				SDL_BlitSurface(page_lvl[4],NULL,screen,NULL);
				SDL_Flip(screen);
			}
			else if (event.button.x>520 && event.button.x<733 && event.button.y>596 && event.button.y<635)
			{
				SDL_BlitSurface(page_lvl[5],NULL,screen,NULL);
				SDL_Flip(screen);
			}
			else if (event.button.x>0 && event.button.x<104 && event.button.y>0 && event.button.y<80)
			{
				SDL_BlitSurface(retour_appui,NULL,screen,NULL);
				SDL_Flip(screen);
			}
			else
			{
				SDL_BlitSurface(page_lvl[0],NULL,screen,NULL);
				SDL_BlitSurface(retour,NULL,screen,NULL);
				SDL_Flip(screen);
			}
			if (event.button.x>0 && event.button.x<104 && event.button.y>0 && event.button.y<80 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)
			{
				page=0;
			}
			if (event.button.x>520 && event.button.x<733 && event.button.y>239 && event.button.y<278 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)
			{
				valeur=2;
				x=1;
			}
			else if (event.button.x>520 && event.button.x<733 && event.button.y>322 && event.button.y<367 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)
			{
				valeur=3;
				x=1;
			}
			else if (event.button.x>520 && event.button.x<733 && event.button.y>416 && event.button.y<458 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)
			{
				valeur=4;
				x=1;
			}
			else if (event.button.x>520 && event.button.x<733 && event.button.y>512 && event.button.y<550 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)
			{
				valeur=5;
				x=1;
			}
			else if (event.button.x>520 && event.button.x<733 && event.button.y>596 && event.button.y<635 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)
			{
				valeur=6;
				x=1;
			}
		}
	}
	while (x==0);

	//partie libération
	SDL_FreeSurface(back);
	SDL_FreeSurface(new);
	SDL_FreeSurface(choose_lvl);
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
	for (i=0;i<6;i++)
	{
		SDL_FreeSurface(page_lvl[i]);
	}
	SDL_FreeSurface(retour_appui);
	SDL_FreeSurface(retour);
	Mix_FreeMusic(musique);
	return valeur;
}









int  menu_pause(SDL_Surface *screen, int *sound, int *fullscreen)
{
	SDL_Surface *back=NULL, *menu=NULL, *resume=NULL, *help=NULL, *option=NULL, *quit=NULL, *fullscreen_on=NULL, *fullscreen_on_appui=NULL, *fullscreen_off=NULL,*fullscreen_off_appui=NULL,*sound_on=NULL,*sound_on_appui=NULL,*sound_off=NULL,*sound_off_appui=NULL,*retour=NULL,*retour_appui=NULL, *page_help=NULL;
	SDL_Event event;
	int x=0,i,j,appui=1,page=1,appui_full=0,appui_sound=0,appui_retour=0,valeur;

	
	back=SDL_DisplayFormatAlpha(IMG_Load("back.png"));
	menu=SDL_DisplayFormatAlpha(IMG_Load("pause.png"));
	resume=SDL_DisplayFormatAlpha(IMG_Load("resume.png"));
	help=SDL_DisplayFormatAlpha(IMG_Load("help.png"));
	option=SDL_DisplayFormatAlpha(IMG_Load("options.png"));
	quit=SDL_DisplayFormatAlpha(IMG_Load("quit.png"));
	page_help=SDL_DisplayFormatAlpha(IMG_Load("page help.png"));
	fullscreen_off=SDL_DisplayFormatAlpha(IMG_Load("option fullscreen off.png"));
	fullscreen_off_appui=SDL_DisplayFormatAlpha(IMG_Load("option fullscreen off apui.png"));
	fullscreen_on=SDL_DisplayFormatAlpha(IMG_Load("option fullscreen on.png"));
	fullscreen_on_appui=SDL_DisplayFormatAlpha(IMG_Load("option fullscreen on appui.png"));
	sound_off=SDL_DisplayFormatAlpha(IMG_Load("option sound off.png"));
	sound_off_appui=SDL_DisplayFormatAlpha(IMG_Load("option sound off appui.png"));
	sound_on=SDL_DisplayFormatAlpha(IMG_Load("option sound on.png"));
	sound_on_appui=SDL_DisplayFormatAlpha(IMG_Load("option sound on appui.png"));
	retour=SDL_DisplayFormatAlpha(IMG_Load("fleche retour.png"));
	retour_appui=SDL_DisplayFormatAlpha(IMG_Load("fleche retour appui.png"));
	SDL_BlitSurface(back,NULL,screen,NULL);
	SDL_BlitSurface(menu,NULL,screen,NULL);
	SDL_Flip(screen);
	

	do
	{
		SDL_WaitEvent(&event);
		if (event.type==SDL_QUIT || event.type==SDL_MOUSEBUTTONUP && event.button.button==SDL_BUTTON_LEFT && event.button.x>503 && event.button.x<738 && event.button.y>595 && event.button.y<642 && page==1)
		{
			x=1;
			valeur=0;
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
				SDL_BlitSurface(resume,NULL,screen,NULL);
				SDL_Flip(screen);
				appui=0;
			}
			else if (event.button.x>500 && event.button.x <756 && event.button.y>426 && event.button.y<462)
			{
				SDL_BlitSurface(help,NULL,screen,NULL);
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
		if (event.button.x>520 && event.button.x <742 && event.button.y>515 && event.button.y<550  && event.type==SDL_MOUSEBUTTONUP && event.button.button==SDL_BUTTON_LEFT && page==1 )
		{
			page=2;
			SDL_BlitSurface(back,NULL,screen,NULL);
			SDL_BlitSurface(retour,NULL,screen,NULL);
			if (*fullscreen==1)
			{
				SDL_BlitSurface(fullscreen_on,NULL,screen,NULL);
			}
			else 
			{
				SDL_BlitSurface(fullscreen_off,NULL,screen,NULL);
			}
			if (*sound==1)
			{
				SDL_BlitSurface(sound_on,NULL,screen,NULL);
			}
			else
			{
				SDL_BlitSurface(sound_off,NULL,screen,NULL);
			}
			SDL_Flip(screen);
		}
		else if (event.button.x>504 && event.button.x <764 && event.button.y>334 && event.button.y<373 && event.type==SDL_MOUSEBUTTONUP && event.button.button==SDL_BUTTON_LEFT && page==1)
		{
			x=1;
			valeur=1;
		}
		else if (event.button.x>500 && event.button.x <756 && event.button.y>426 && event.button.y<462 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT && page==1)
		{
			page=3;
			SDL_BlitSurface(page_help,NULL,screen,NULL);
			SDL_BlitSurface(retour,NULL,screen,NULL);
			SDL_Flip(screen);

		}
		if (page==2)
		{
			if (event.button.x>492 && event.button.x<762 && event.button.y>304 && event.button.y<356)
			{
				if (*fullscreen==1)
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
				if (*sound==1)
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
					if (*fullscreen==1)
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
					if (*sound==1)
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
				if (*fullscreen==1)
				{
					screen=SDL_SetVideoMode(1280,768,32,SDL_SWSURFACE | SDL_DOUBLEBUF);
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(fullscreen_off,NULL,screen,NULL);
					SDL_BlitSurface(retour,NULL,screen,NULL);
					*fullscreen=0;
					if (*sound==1)
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
					screen=SDL_SetVideoMode(1280,768,32,SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
					SDL_BlitSurface(back,NULL,screen,NULL);
					SDL_BlitSurface(fullscreen_on,NULL,screen,NULL);
					SDL_BlitSurface(retour,NULL,screen,NULL);
					*fullscreen=1;
					if (*sound==1)
					{
						SDL_BlitSurface(sound_on,NULL,screen,NULL);
					}
					else 
					{
						SDL_BlitSurface(sound_off,NULL,screen,NULL);
					}

				}
				SDL_Flip(screen);
			}
			else if (event.button.x>518 && event.button.x<736 && event.button.y>531 && event.button.y<588 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)
			{
				if (*sound==1)
				{
					SDL_BlitSurface(sound_off,NULL,screen,NULL);
					*sound=0;
					Mix_VolumeMusic(0);
				}
				else
				{
					SDL_BlitSurface(sound_on,NULL,screen,NULL);
					*sound=1;
					Mix_VolumeMusic(128);
				}
				SDL_Flip(screen);
			}
			else if (event.button.x>0 && event.button.x<104 && event.button.y>0 && event.button.y<80 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)
			{
				page=0;
			}
		}
		if (page==3)
		{
			if (event.button.x>0 && event.button.x<104 && event.button.y>0 && event.button.y<80)
			{
				SDL_BlitSurface(retour_appui,NULL,screen,NULL);
				SDL_Flip(screen);
				appui_retour=1;
			}
			else if (appui_retour==1)
			{
				SDL_BlitSurface(retour,NULL,screen,NULL);
				SDL_Flip(screen);
				appui_retour=0;
			}
			if (event.button.x>0 && event.button.x<104 && event.button.y>0 && event.button.y<80 && event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT)
			{
				page=0;
			}
		}
	}
	while (x==0);


	SDL_FreeSurface(back);
	SDL_FreeSurface(resume);
	SDL_FreeSurface(help);
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
	SDL_FreeSurface(retour_appui);
	SDL_FreeSurface(retour);
	SDL_FreeSurface(page_help);
	return valeur;
}















