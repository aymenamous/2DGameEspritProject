#include "lvl1.h"
#include "menu.h"
#include "mouvement.h"
#include "cbt.h"
#include "var.h"



int lvl_1(SDL_Surface *screen, SDL_Surface *back, int *sound, int *fullscreen)
{
	SDL_Surface *mvt[14]={NULL},*mvtg[14]={NULL}, *stage_cleared=NULL, *prepare=NULL, *scene[3]={NULL};
	int continuer=1,i=0,x=70,precedent=0,actuel=0,y=20,droite=1,limite=8000,vitesse=50,combat=0,win,rep,presence_slendy=0;
	SDL_Event event;
	SDL_Rect pos, pos_map;
	Mix_Music *son;
	Mix_Chunk *sword_sound;



	son=Mix_LoadMUS("ambiance lvl1.ogg");//musique du lvl
	Mix_PlayMusic(son,-1);
	sword_sound=Mix_LoadWAV("clash of sword.ogg");//son jouée lors du commencement d'un combat
	prepare=SDL_DisplayFormatAlpha(IMG_Load("prepare to battle.jpg"));// image affichée lors du commencement d'un combat
	stage_cleared=SDL_DisplayFormatAlpha(IMG_Load("stage 1 cleared.png"));//image affichée à la fin du lvl

	//images des bulles
	scene[0]=SDL_DisplayFormatAlpha(IMG_Load("scenes/scene 1.png"));
	scene[1]=SDL_DisplayFormatAlpha(IMG_Load("scenes/scene 2.png"));
	scene[2]=SDL_DisplayFormatAlpha(IMG_Load("scenes/scene 3.png"));

	//images des mouvements de raiden vers la droite
	mvt[0]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 0.png"));
	mvt[1]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 1.png"));
	mvt[2]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 2.png"));
	mvt[3]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 3.png"));
	mvt[4]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 4.png"));
	mvt[5]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 5.png"));
	mvt[6]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 6.png"));
	mvt[7]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 0.png"));
	mvt[8]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 8.png"));
	mvt[9]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 9.png"));
	mvt[10]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 10.png"));
	mvt[11]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 11.png"));
	mvt[12]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 12.png"));
	mvt[13]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 13.png"));

	//images de mouvements de raiden vers la gauche
	mvtg[0]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 0.png"));
	mvtg[1]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 1.png"));
	mvtg[2]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 2.png"));
	mvtg[3]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 3.png"));
	mvtg[4]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 4.png"));
	mvtg[5]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche5.png"));
	mvtg[6]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche6.png"));
	mvtg[7]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 0.png"));
	mvtg[8]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche8.png"));
	mvtg[9]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche9.png"));
	mvtg[10]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche10.png"));
	mvtg[11]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche11.png"));
	mvtg[12]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche12.png"));
	mvtg[13]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche13.png"));

	//position initiale de la map(utilisés pour le scrolling)
	pos_map.x=0;
	pos_map.y=0;
	pos_map.w=10000;
	pos_map.h=768;

	//position initiale de raiden
	pos.x=0;
	pos.y=0;
	pos.w=1280;
	pos.h=768;

	SDL_BlitSurface(back,&pos_map,screen,NULL);//affichage du background
	SDL_BlitSurface(mvt[0],&pos,screen,NULL);// affichage de l'image par défault de raiden (dirigée vers la droite)
	SDL_BlitSurface(scene[0],NULL,screen,NULL);
	SDL_Flip(screen);
	SDL_Delay(1000);
	SDL_EnableKeyRepeat(1,1);
	do
	{
		SDL_WaitEvent(&event);
		if (event.type==SDL_QUIT)
		{
			continuer=0;
		}
		else  if (event.key.keysym.sym==SDLK_ESCAPE)//appui sur échap->menu pause
		{
			rep=menu_pause(screen,sound,fullscreen);//valeur prise depuis le menu pause, si rep==0 alors ça veut dire qu'on a cliqué sur quit et si rep==1 ça veut dire qu'on a appuié sur resume
			if (rep==0)
			{
				win=0;
				continuer=0;
			}
			else if (rep==1)
			{
				SDL_BlitSurface(back,&pos_map,screen,NULL);
				SDL_BlitSurface(mvt[i],&pos,screen,NULL);
				SDL_Flip(screen);
			}
		}
		if (pos_map.x>=2000 && combat==0) //lorsque raiden arrive à une certaine position, le premier combat commence
		{
			Mix_PlayChannel(-1,sword_sound,0);
			SDL_BlitSurface(prepare,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(1000);
			win=cbt (1,0,screen,back,pos_map,sound,fullscreen,1);
			if (win==0)//le joueur a perdu le combat (il commencera par défault la ou il était lors de la phase de mouvement->si il avance, il recommencera le combat)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
			}
			else if (win==1)//si il gagne
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
				combat=1;//passage au combat suivant
				SDL_BlitSurface(scene[1],NULL,screen,NULL);
				SDL_Flip(screen);
				SDL_Delay(3000);
			}
			else if (win==2)
			{
				combat=-1;
				continuer=0;
			}
		}
		else if (pos_map.x>=4000 && combat==1)
		{
			Mix_PlayChannel(-1,sword_sound,0);
			SDL_BlitSurface(prepare,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(3000);
			win=cbt (0,1,screen,back,pos_map,sound,fullscreen,1);
			if (win==0)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
			}
			else if (win==1)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
				combat=2;
				SDL_BlitSurface(scene[2],NULL,screen,NULL);
				SDL_Flip(screen);
				SDL_Delay(3000);
			}
			else if (win==2)
			{
				combat=-1;
				continuer=0;
			}
		}
		else if (pos_map.x>=6000 && combat==2)
		{
			Mix_PlayChannel(-1,sword_sound,0);
			SDL_BlitSurface(prepare,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(1000);
			win=cbt (1,1,screen,back,pos_map,sound,fullscreen,1);
			if (win==0)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
			}
			else if (win==1)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
				combat=3;
			}
			else if (win==2)
			{
				combat=-1;
				continuer=0;
			}

		}
		else if (pos_map.x>6600 && combat==3)//si il arrive à la fin de la map et il a remporté le 3 combat, alors affichage de "stage cleared"+sortie de la boucle
		{
			SDL_BlitSurface(stage_cleared,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(3000);
			continuer=0;
		}
		if (event.type==SDL_KEYDOWN && combat!=-1)//appui sur une touche
		{
			if (event.key.keysym.sym==SDLK_RIGHT)//appui sur la touche directionnelle droite
			{
				mvt_droite(&droite,&pos_map,limite,&pos,y,back,screen,mvt[i],&i);//déplacement à droite
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
			else if (event.key.keysym.sym==SDLK_LEFT)//appui sur la touche directionnelle gauche
			{
				mvt_gauche(&droite,&pos_map,limite,&pos,y,back,screen,mvtg[i],&i);//déplacement à gauche
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
			else if (event.key.keysym.sym==SDLK_UP) //appui sur la touche directionnelle haut
			{
				mvt_haut(pos_map,&pos,y,back,screen,mvt[i],mvtg[i],&i,droite);//déplacement vers le haut
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
			else if (event.key.keysym.sym==SDLK_DOWN)//appui sur la touche directionnelle bas
			{
				mvt_bas(pos_map,&pos,y,back,screen,mvt[i],mvtg[i],&i,droite);//déplacement vers le bas
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
		}

	}
	while (continuer==1);

	//liberation
	SDL_FreeSurface(stage_cleared);
	SDL_FreeSurface(prepare);
	for (i=0;i<14;i++)
	{
		SDL_FreeSurface(mvt[i]);
		SDL_FreeSurface(mvtg[i]);
	}
	for (i=0;i<3;i++)
	{
		SDL_FreeSurface(scene[i]);
	}
	Mix_FreeMusic(son);
	Mix_FreeChunk(sword_sound);
	return win;
}











int lvl_2(SDL_Surface *screen, SDL_Surface *back, int *sound, int *fullscreen)
{
	SDL_Surface *mvt[14]={NULL},*mvtg[14]={NULL}, *stage_cleared=NULL, *prepare=NULL, *scene[3]={NULL};
	int continuer=1,i=0,x=70,precedent=0,actuel=0,y=20,droite=1,limite=8000,vitesse=50,combat=0,win,rep,presence_slendy=0;
	SDL_Event event;
	SDL_Rect pos, pos_map;
	Mix_Music *son;
	Mix_Chunk *sword_sound;



	son=Mix_LoadMUS("ambiance lvl1.mp3");//musique du lvl
	Mix_PlayMusic(son,-1);
	sword_sound=Mix_LoadWAV("clash of sword.ogg");//son jouée lors du commencement d'un combat
	prepare=SDL_DisplayFormatAlpha(IMG_Load("prepare to battle.jpg"));// image affichée lors du commencement d'un combat
	stage_cleared=SDL_DisplayFormatAlpha(IMG_Load("stage 1 cleared.png"));//image affichée à la fin du lvl
	//images des bulles
	scene[0]=SDL_DisplayFormatAlpha(IMG_Load("scenes/scene 4.png"));
	scene[1]=SDL_DisplayFormatAlpha(IMG_Load("scenes/scene 5.png"));
	scene[2]=SDL_DisplayFormatAlpha(IMG_Load("scenes/scene 6.png"));

	//images des mouvements de raiden vers la droite
	mvt[0]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 0.png"));
	mvt[1]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 1.png"));
	mvt[2]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 2.png"));
	mvt[3]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 3.png"));
	mvt[4]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 4.png"));
	mvt[5]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 5.png"));
	mvt[6]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 6.png"));
	mvt[7]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 0.png"));
	mvt[8]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 8.png"));
	mvt[9]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 9.png"));
	mvt[10]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 10.png"));
	mvt[11]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 11.png"));
	mvt[12]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 12.png"));
	mvt[13]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 13.png"));

	//images de mouvements de raiden vers la gauche
	mvtg[0]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 0.png"));
	mvtg[1]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 1.png"));
	mvtg[2]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 2.png"));
	mvtg[3]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 3.png"));
	mvtg[4]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 4.png"));
	mvtg[5]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche5.png"));
	mvtg[6]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche6.png"));
	mvtg[7]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 0.png"));
	mvtg[8]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche8.png"));
	mvtg[9]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche9.png"));
	mvtg[10]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche10.png"));
	mvtg[11]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche11.png"));
	mvtg[12]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche12.png"));
	mvtg[13]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche13.png"));

	//position initiale de la map(utilisés pour le scrolling)
	pos_map.x=0;
	pos_map.y=0;
	pos_map.w=10000;
	pos_map.h=768;

	//position initiale de raiden
	pos.x=0;
	pos.y=0;
	pos.w=1280;
	pos.h=768;

	SDL_BlitSurface(back,&pos_map,screen,NULL);//affichage du background
	SDL_BlitSurface(mvt[0],&pos,screen,NULL);// affichage de l'image par défault de raiden (dirigée vers la droite)
	SDL_BlitSurface(scene[0],NULL,screen,NULL);
	SDL_Flip(screen);
	SDL_Delay(3000);
	SDL_EnableKeyRepeat(1,1);
	do
	{
		SDL_WaitEvent(&event);
		if (event.type==SDL_QUIT)
		{
			continuer=0;
		}
		else  if (event.key.keysym.sym==SDLK_ESCAPE)//appui sur échap->menu pause
		{
			rep=menu_pause(screen,sound,fullscreen);//valeur prise depuis le menu pause, si rep==0 alors ça veut dire qu'on a cliqué sur quit et si rep==1 ça veut dire qu'on a appuié sur resume
			if (rep==0)
			{
				continuer=0;
				win=0;
			}
			else if (rep==1)
			{
				SDL_BlitSurface(back,&pos_map,screen,NULL);
				SDL_BlitSurface(mvt[i],&pos,screen,NULL);
				SDL_Flip(screen);
			}
		}
		if (pos_map.x>=2000 && combat==0) //lorsque raiden arrive à une certaine position, le premier combat commence
		{
			Mix_PlayChannel(-1,sword_sound,0);
			SDL_BlitSurface(prepare,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(1000);
			win=cbt (1,0,screen,back,pos_map,sound,fullscreen,2);
			if (win==0)//le joueur a perdu le combat (il commencera par défault la ou il était lors de la phase de mouvement->si il avance, il recommencera le combat)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
			}
			else if (win==1)//si il gagne
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
				combat=1;//passage au combat suivant
				SDL_BlitSurface(scene[1],NULL,screen,NULL);
				SDL_Flip(screen);
				SDL_Delay(3000);
			}
			else if (win==2)
			{
				combat=-1;
				continuer=0;
			}
		}
		else if (pos_map.x>=4000 && combat==1)
		{
			Mix_PlayChannel(-1,sword_sound,0);
			SDL_BlitSurface(prepare,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(1000);
			win=cbt (0,1,screen,back,pos_map,sound,fullscreen,2);
			if (win==0)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
			}
			else if (win==1)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
				combat=2;
				SDL_BlitSurface(scene[2],NULL,screen,NULL);
				SDL_Flip(screen);
				SDL_Delay(3000);
			}
			else if (win==2)
			{
				combat=-1;
				continuer=0;
			}
		}
		else if (pos_map.x>=6000 && combat==2)
		{
			Mix_PlayChannel(-1,sword_sound,0);
			SDL_BlitSurface(prepare,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(1000);
			win=cbt (1,1,screen,back,pos_map,sound,fullscreen,2);
			if (win==0)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
			}
			else if (win==1)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
				combat=3;
			}
			else if (win==2)
			{
				combat=-1;
				continuer=0;
			}

		}
		else if (pos_map.x>6600 && combat==3)//si il arrive à la fin de la map et il a remporté le 3 combat, alors affichage de "stage cleared"+sortie de la boucle
		{
			SDL_BlitSurface(stage_cleared,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(3000);
			continuer=0;
		}
		if (event.type==SDL_KEYDOWN && combat!=-1)//appui sur une touche
		{
			if (event.key.keysym.sym==SDLK_RIGHT)//appui sur la touche directionnelle droite
			{
				mvt_droite(&droite,&pos_map,limite,&pos,y,back,screen,mvt[i],&i);//déplacement à droite
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
			else if (event.key.keysym.sym==SDLK_LEFT)//appui sur la touche directionnelle gauche
			{
				mvt_gauche(&droite,&pos_map,limite,&pos,y,back,screen,mvtg[i],&i);//déplacement à gauche
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
			else if (event.key.keysym.sym==SDLK_UP) //appui sur la touche directionnelle haut
			{
				mvt_haut(pos_map,&pos,y,back,screen,mvt[i],mvtg[i],&i,droite);//déplacement vers le haut
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
			else if (event.key.keysym.sym==SDLK_DOWN)//appui sur la touche directionnelle bas
			{
				mvt_bas(pos_map,&pos,y,back,screen,mvt[i],mvtg[i],&i,droite);//déplacement vers le bas
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
		}

	}
	while (continuer==1);

	//liberation
	SDL_FreeSurface(stage_cleared);
	SDL_FreeSurface(prepare);
	for (i=0;i<14;i++)
	{
		SDL_FreeSurface(mvt[i]);
		SDL_FreeSurface(mvtg[i]);
	}
	for (i=0;i<3;i++)
	{
		SDL_FreeSurface(scene[i]);
	}
	Mix_FreeMusic(son);
	Mix_FreeChunk(sword_sound);
	return win;
}










int lvl_3(SDL_Surface *screen, SDL_Surface *back, int *sound, int *fullscreen)
{
	SDL_Surface *mvt[14]={NULL},*mvtg[14]={NULL}, *stage_cleared=NULL, *prepare=NULL,*scene[3]={NULL};
	int continuer=1,i=0,x=70,precedent=0,actuel=0,y=20,droite=1,limite=8000,vitesse=50,combat=0,win,rep,presence_slendy=0;
	SDL_Event event;
	SDL_Rect pos, pos_map;
	Mix_Music *son;
	Mix_Chunk *sword_sound;



	son=Mix_LoadMUS("ambiance lvl1.mp3");//musique du lvl
	Mix_PlayMusic(son,-1);
	sword_sound=Mix_LoadWAV("clash of sword.ogg");//son jouée lors du commencement d'un combat
	prepare=SDL_DisplayFormatAlpha(IMG_Load("prepare to battle.jpg"));// image affichée lors du commencement d'un combat
	stage_cleared=SDL_DisplayFormatAlpha(IMG_Load("stage 1 cleared.png"));//image affichée à la fin du lvl
	//images des bulles
	scene[0]=SDL_DisplayFormatAlpha(IMG_Load("scenes/scene 7.png"));
	scene[1]=SDL_DisplayFormatAlpha(IMG_Load("scenes/scene 8.png"));
	scene[2]=SDL_DisplayFormatAlpha(IMG_Load("scenes/scene 9.png"));

	//images des mouvements de raiden vers la droite
	mvt[0]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 0.png"));
	mvt[1]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 1.png"));
	mvt[2]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 2.png"));
	mvt[3]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 3.png"));
	mvt[4]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 4.png"));
	mvt[5]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 5.png"));
	mvt[6]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 6.png"));
	mvt[7]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 0.png"));
	mvt[8]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 8.png"));
	mvt[9]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 9.png"));
	mvt[10]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 10.png"));
	mvt[11]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 11.png"));
	mvt[12]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 12.png"));
	mvt[13]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 13.png"));

	//images de mouvements de raiden vers la gauche
	mvtg[0]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 0.png"));
	mvtg[1]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 1.png"));
	mvtg[2]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 2.png"));
	mvtg[3]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 3.png"));
	mvtg[4]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 4.png"));
	mvtg[5]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche5.png"));
	mvtg[6]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche6.png"));
	mvtg[7]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 0.png"));
	mvtg[8]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche8.png"));
	mvtg[9]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche9.png"));
	mvtg[10]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche10.png"));
	mvtg[11]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche11.png"));
	mvtg[12]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche12.png"));
	mvtg[13]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche13.png"));

	//position initiale de la map(utilisés pour le scrolling)
	pos_map.x=0;
	pos_map.y=0;
	pos_map.w=10000;
	pos_map.h=768;

	//position initiale de raiden
	pos.x=0;
	pos.y=0;
	pos.w=1280;
	pos.h=768;

	SDL_BlitSurface(back,&pos_map,screen,NULL);//affichage du background
	SDL_BlitSurface(mvt[0],&pos,screen,NULL);// affichage de l'image par défault de raiden (dirigée vers la droite)
	SDL_BlitSurface(scene[0],NULL,screen,NULL);
	SDL_Flip(screen);
	SDL_Delay(3000);
	SDL_EnableKeyRepeat(1,1);
	do
	{
		SDL_WaitEvent(&event);
		if (event.type==SDL_QUIT)
		{
			continuer=0;
		}
		else  if (event.key.keysym.sym==SDLK_ESCAPE)//appui sur échap->menu pause
		{
			rep=menu_pause(screen,sound,fullscreen);//valeur prise depuis le menu pause, si rep==0 alors ça veut dire qu'on a cliqué sur quit et si rep==1 ça veut dire qu'on a appuié sur resume
			if (rep==0)
			{
				win=0;
				continuer=0;
			}
			else if (rep==1)
			{
				SDL_BlitSurface(back,&pos_map,screen,NULL);
				SDL_BlitSurface(mvt[i],&pos,screen,NULL);
				SDL_Flip(screen);
			}
		}
		if (pos_map.x>=1500 && combat==0) //lorsque raiden arrive à une certaine position, le premier combat commence
		{
			Mix_PlayChannel(-1,sword_sound,0);
			SDL_BlitSurface(prepare,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(1000);
			win=cbt (2,0,screen,back,pos_map,sound,fullscreen,3);
			if (win==0)//le joueur a perdu le combat (il commencera par défault la ou il était lors de la phase de mouvement->si il avance, il recommencera le combat)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
			}
			else if (win==1)//si il gagne
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
				combat=1;//passage au combat suivant
				SDL_BlitSurface(scene[1],NULL,screen,NULL);
				SDL_Flip(screen);
				SDL_Delay(3000);
			}
			else if (win==2)
			{
				combat=-1;
				continuer=0;
			}
		}
		else if (pos_map.x>=3000 && combat==1)
		{
			Mix_PlayChannel(-1,sword_sound,0);
			SDL_BlitSurface(prepare,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(1000);
			win=cbt (2,1,screen,back,pos_map,sound,fullscreen,3);
			if (win==0)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
			}
			else if (win==1)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
				combat=2;
			}
			else if (win==2)
			{
				combat=-1;
				continuer=0;
			}
		}
		else if (pos_map.x>=5000 && combat==2)
		{
			Mix_PlayChannel(-1,sword_sound,0);
			SDL_BlitSurface(prepare,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(1000);
			win=cbt (2,2,screen,back,pos_map,sound,fullscreen,3);
			if (win==0)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
			}
			else if (win==1)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
				combat=3;
			}
			else if (win==2)
			{
				combat=-1;
				continuer=0;
			}

		}
		else if (pos_map.x>=6000 && combat==3)
		{
			SDL_BlitSurface(scene[2],NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(3000);
			Mix_PlayChannel(-1,sword_sound,0);
			SDL_BlitSurface(prepare,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(1000);
			win=cbt_boss (screen,back,pos_map,sound,fullscreen,3);
			if (win==0)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
			}
			else if (win==1)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
				combat=4;
			}
			else if (win==2)
			{
				combat=-1;
				continuer=0;
			}

		}
		else if (pos_map.x>6600 && combat==4)//si il arrive à la fin de la map et il a remporté le 3 combat, alors affichage de "stage cleared"+sortie de la boucle
		{
			SDL_BlitSurface(stage_cleared,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(3000);
			continuer=0;
		}
		if (event.type==SDL_KEYDOWN && combat!=-1)//appui sur une touche
		{
			if (event.key.keysym.sym==SDLK_RIGHT)//appui sur la touche directionnelle droite
			{
				mvt_droite(&droite,&pos_map,limite,&pos,y,back,screen,mvt[i],&i);//déplacement à droite
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
			else if (event.key.keysym.sym==SDLK_LEFT)//appui sur la touche directionnelle gauche
			{
				mvt_gauche(&droite,&pos_map,limite,&pos,y,back,screen,mvtg[i],&i);//déplacement à gauche
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
			else if (event.key.keysym.sym==SDLK_UP) //appui sur la touche directionnelle haut
			{
				mvt_haut(pos_map,&pos,y,back,screen,mvt[i],mvtg[i],&i,droite);//déplacement vers le haut
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
			else if (event.key.keysym.sym==SDLK_DOWN)//appui sur la touche directionnelle bas
			{
				mvt_bas(pos_map,&pos,y,back,screen,mvt[i],mvtg[i],&i,droite);//déplacement vers le bas
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
		}

	}
	while (continuer==1);

	//liberation
	SDL_FreeSurface(stage_cleared);
	SDL_FreeSurface(prepare);
	for (i=0;i<14;i++)
	{
		SDL_FreeSurface(mvt[i]);
		SDL_FreeSurface(mvtg[i]);
	}
	for (i=0;i<3;i++)
	{
		SDL_FreeSurface(scene[i]);
	}
	Mix_FreeMusic(son);
	Mix_FreeChunk(sword_sound);
	return win;
}














int lvl_4(SDL_Surface *screen, SDL_Surface *back, int *sound, int *fullscreen)
{
	SDL_Surface *mvt[14]={NULL},*mvtg[14]={NULL}, *stage_cleared=NULL, *prepare=NULL, *scene=NULL;
	int continuer=1,i=0,x=70,precedent=0,actuel=0,y=20,droite=1,limite=8000,vitesse=50,combat=0,win,rep,presence_slendy=0;
	SDL_Event event;
	SDL_Rect pos, pos_map;
	Mix_Music *son;
	Mix_Chunk *sword_sound;



	son=Mix_LoadMUS("ambiance lvl1.mp3");//musique du lvl
	Mix_PlayMusic(son,-1);
	sword_sound=Mix_LoadWAV("clash of sword.ogg");//son jouée lors du commencement d'un combat
	prepare=SDL_DisplayFormatAlpha(IMG_Load("prepare to battle.jpg"));// image affichée lors du commencement d'un combat
	stage_cleared=SDL_DisplayFormatAlpha(IMG_Load("stage 1 cleared.png"));//image affichée à la fin du lvl
	//images des bulles
	scene=SDL_DisplayFormatAlpha(IMG_Load("scenes/scene 10.png"));

	//images des mouvements de raiden vers la droite
	mvt[0]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 0.png"));
	mvt[1]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 1.png"));
	mvt[2]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 2.png"));
	mvt[3]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 3.png"));
	mvt[4]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 4.png"));
	mvt[5]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 5.png"));
	mvt[6]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 6.png"));
	mvt[7]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 0.png"));
	mvt[8]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 8.png"));
	mvt[9]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 9.png"));
	mvt[10]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 10.png"));
	mvt[11]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 11.png"));
	mvt[12]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 12.png"));
	mvt[13]=SDL_DisplayFormatAlpha(IMG_Load("mouvement droite 13.png"));

	//images de mouvements de raiden vers la gauche
	mvtg[0]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 0.png"));
	mvtg[1]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 1.png"));
	mvtg[2]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 2.png"));
	mvtg[3]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 3.png"));
	mvtg[4]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 4.png"));
	mvtg[5]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche5.png"));
	mvtg[6]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche6.png"));
	mvtg[7]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche 0.png"));
	mvtg[8]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche8.png"));
	mvtg[9]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche9.png"));
	mvtg[10]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche10.png"));
	mvtg[11]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche11.png"));
	mvtg[12]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche12.png"));
	mvtg[13]=SDL_DisplayFormatAlpha(IMG_Load("mouvement gauche13.png"));

	//position initiale de la map(utilisés pour le scrolling)
	pos_map.x=0;
	pos_map.y=0;
	pos_map.w=10000;
	pos_map.h=768;

	//position initiale de raiden
	pos.x=0;
	pos.y=0;
	pos.w=1280;
	pos.h=768;

	SDL_BlitSurface(back,&pos_map,screen,NULL);//affichage du background
	SDL_BlitSurface(mvt[0],&pos,screen,NULL);// affichage de l'image par défault de raiden (dirigée vers la droite)
	SDL_Flip(screen);
	SDL_EnableKeyRepeat(1,1);
	do
	{
		SDL_WaitEvent(&event);
		if (event.type==SDL_QUIT)
		{
			continuer=0;
		}
		else  if (event.key.keysym.sym==SDLK_ESCAPE)//appui sur échap->menu pause
		{
			rep=menu_pause(screen,sound,fullscreen);//valeur prise depuis le menu pause, si rep==0 alors ça veut dire qu'on a cliqué sur quit et si rep==1 ça veut dire qu'on a appuié sur resume
			if (rep==0)
			{
				continuer=0;
				win=0;
			}
			else if (rep==1)
			{
				SDL_BlitSurface(back,&pos_map,screen,NULL);
				SDL_BlitSurface(mvt[i],&pos,screen,NULL);
				SDL_Flip(screen);
			}
		}
		if (pos_map.x>=1500 && combat==0) //lorsque raiden arrive à une certaine position, le premier combat commence
		{
			Mix_PlayChannel(-1,sword_sound,0);
			SDL_BlitSurface(prepare,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(1000);
			win=cbt (2,2,screen,back,pos_map,sound,fullscreen,4);
			if (win==0)//le joueur a perdu le combat (il commencera par défault la ou il était lors de la phase de mouvement->si il avance, il recommencera le combat)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
			}
			else if (win==1)//si il gagne
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
				combat=1;//passage au combat suivant
			}
			else if (win==2)
			{
				combat=-1;
				continuer=0;
			}
		}
		else if (pos_map.x>=3000 && combat==1)
		{
			Mix_PlayChannel(-1,sword_sound,0);
			SDL_BlitSurface(prepare,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(1000);
			win=cbt (3,2,screen,back,pos_map,sound,fullscreen,4);
			if (win==0)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
			}
			else if (win==1)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
				combat=2;
			}
			else if (win==2)
			{
				combat=-1;
				continuer=0;
			}
		}
		else if (pos_map.x>=5000 && combat==2)
		{
			Mix_PlayChannel(-1,sword_sound,0);
			SDL_BlitSurface(prepare,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(1000);
			win=cbt (3,3,screen,back,pos_map,sound,fullscreen,4);
			if (win==0)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
			}
			else if (win==1)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
				combat=3;
			}
			else if (win==2)
			{
				combat=-1;
				continuer=0;
			}

		}
		else if (pos_map.x>=6000 && combat==3)
		{
			SDL_BlitSurface(scene,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(3000);
			Mix_PlayChannel(-1,sword_sound,0);
			SDL_BlitSurface(prepare,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(1000);
			win=cbt_boss (screen,back,pos_map,sound,fullscreen,4);
			if (win==0)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
			}
			else if (win==1)
			{
				fin_cbt(back,screen,mvt[i],pos_map,pos);
				combat=4;
			}
			else if (win==2)
			{
				combat=-1;
				continuer=0;
			}

		}
		else if (pos_map.x>6600 && combat==4)//si il arrive à la fin de la map et il a remporté le 3 combat, alors affichage de "stage cleared"+sortie de la boucle
		{
			SDL_BlitSurface(stage_cleared,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(3000);
			continuer=0;
		}
		if (event.type==SDL_KEYDOWN && combat!=-1)//appui sur une touche
		{
			if (event.key.keysym.sym==SDLK_RIGHT)//appui sur la touche directionnelle droite
			{
				mvt_droite(&droite,&pos_map,limite,&pos,y,back,screen,mvt[i],&i);//déplacement à droite
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
			else if (event.key.keysym.sym==SDLK_LEFT)//appui sur la touche directionnelle gauche
			{
				mvt_gauche(&droite,&pos_map,limite,&pos,y,back,screen,mvtg[i],&i);//déplacement à gauche
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
			else if (event.key.keysym.sym==SDLK_UP) //appui sur la touche directionnelle haut
			{
				mvt_haut(pos_map,&pos,y,back,screen,mvt[i],mvtg[i],&i,droite);//déplacement vers le haut
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
			else if (event.key.keysym.sym==SDLK_DOWN)//appui sur la touche directionnelle bas
			{
				mvt_bas(pos_map,&pos,y,back,screen,mvt[i],mvtg[i],&i,droite);//déplacement vers le bas
				boucle(vitesse,&actuel,&precedent);//vitesse
			}
		}

	}
	while (continuer==1);

	//liberation
	SDL_FreeSurface(stage_cleared);
	SDL_FreeSurface(prepare);
	for (i=0;i<14;i++)
	{
		SDL_FreeSurface(mvt[i]);
		SDL_FreeSurface(mvtg[i]);
	}
	SDL_FreeSurface(scene);
	Mix_FreeMusic(son);
	Mix_FreeChunk(sword_sound);
	return win;
}









int lvl_5(SDL_Surface *screen, SDL_Surface *back, int *sound, int *fullscreen)
{
	SDL_Surface *stage_cleared=NULL, *prepare=NULL, *scene[2]={NULL}, *perso[2]={NULL};
	int continuer=1,i=0,x=70,precedent=0,actuel=0,y=20,droite=1,limite=8000,vitesse=50,combat=0,win,rep;
	Mix_Music *son;
	Mix_Chunk *sword_sound;
	SDL_Rect pos_map,pos_perso;

	pos_map.x=0;
	pos_map.y=0;
	pos_map.h=5000;
	pos_map.w=5000;

	son=Mix_LoadMUS("ambiancebleak.ogg");//musique du lvl
	Mix_PlayMusic(son,-1);
	sword_sound=Mix_LoadWAV("clash of sword.ogg");//son jouée lors du commencement d'un combat
	prepare=SDL_DisplayFormatAlpha(IMG_Load("prepare to battle.jpg"));// image affichée lors du commencement d'un combat
	stage_cleared=SDL_DisplayFormatAlpha(IMG_Load("stage 1 cleared.png"));//image affichée à la fin du lvl
	perso[0]=SDL_DisplayFormatAlpha(IMG_Load("pose combat_raiden.png")); //image raiden
	perso[1]=SDL_DisplayFormatAlpha(IMG_Load("mode_cbt.png")); //image slendy

	//images des bulles
	scene[0]=SDL_DisplayFormatAlpha(IMG_Load("scenes/scene 11.png"));
	scene[1]=SDL_DisplayFormatAlpha(IMG_Load("scenes/scene 12.png"));
	SDL_BlitSurface(back,NULL,screen,NULL);
	pos_perso.x=0;
	pos_perso.y=0;
	SDL_BlitSurface(perso[0],NULL,screen,&pos_perso);
	pos_perso.x=0;
	pos_perso.y=200;
	SDL_BlitSurface(perso[1],NULL,screen,&pos_perso);
	SDL_BlitSurface(scene[0],NULL,screen,NULL);
	SDL_Flip(screen);
	SDL_Delay(2000);
	SDL_BlitSurface(scene[1],NULL,screen,NULL);
	SDL_Flip(screen);
	SDL_Delay(2000);
	do
	{
		Mix_PlayChannel(-1,sword_sound,0);
		SDL_BlitSurface(prepare,NULL,screen,NULL);
		SDL_Flip(screen);
		SDL_Delay(1000);
		win=cbt_boss(screen,back,pos_map,sound,fullscreen,5);
		if (win==1)//si il gagne
		{
			SDL_BlitSurface(stage_cleared,NULL,screen,NULL);
			SDL_Flip(screen);
			SDL_Delay(3000);
			continuer=0;
		}
		else if (win==2)
		{
			continuer=0;
		}
	}
	while (continuer==1);

	//liberation
	for (i=0;i<2;i++)
	{
		SDL_FreeSurface(scene[i]);
		SDL_Surface(perso[i]);
	}
	SDL_FreeSurface(stage_cleared);
	SDL_FreeSurface(prepare);
	Mix_FreeChunk(sword_sound);
	Mix_FreeMusic(son);
	return win;
}





void fin_cbt(SDL_Surface *back,SDL_Surface *screen, SDL_Surface *img, SDL_Rect pos_map, SDL_Rect pos)
{
	SDL_BlitSurface(back,&pos_map,screen,NULL);
	SDL_BlitSurface(img,&pos,screen,NULL);
	SDL_Flip(screen);
}