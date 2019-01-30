#include "cbt.h"
#include "var.h"



int cbt (int nbr_archer, int nbr_guerrier, SDL_Surface *screen, SDL_Surface *back, SDL_Rect pos_map, int *sound, int *fullscreen, int lvl)
{
	SDL_Surface  *archer_img[4]={NULL}, *war_img[9]={NULL}, *barre_ennemy[6]={NULL}, *vie_ennemy[6]={NULL}, *degat=NULL, *game_over=NULL;
	SDL_Rect slot[6], barre_ennemy_pos[6];
	int i,continuer=1,j,nbr_ennemies=nbr_archer+nbr_guerrier,cible=0,tour=1,appui=0,morts=0,afficher=0,win=1,rep,cible_ennemi;
	hero raiden, slendy, hero_cible;
	perso ennemy[nbr_ennemies];
	SDL_Event event,event1;
	Mix_Chunk *arrow_sound, *blood_explosion, *warrior_sound;
	TTF_Font *police;

	TTF_Init();

	police=TTF_OpenFont("Ace Records.ttf",70); // police affichage dégât
	arrow_sound=Mix_LoadWAV("tir fleche.ogg"); // son flèche
	blood_explosion=Mix_LoadWAV("blood explosion.ogg"); //son pour la mort d'un personnage
	warrior_sound=Mix_LoadWAV("warrior sound.ogg"); // son attaque guerrier
	raiden=Init_raiden(lvl); // Initialisation de Raiden
	slendy=Init_slendy(lvl);
	if (*sound==0) //desactivation du son
	{
		Mix_VolumeChunk(arrow_sound, 0);
		Mix_VolumeChunk(blood_explosion, 0); 
		Mix_VolumeChunk(warrior_sound, 0); 
		Mix_VolumeChunk(raiden.sound[0], 0); 
		Mix_VolumeChunk(raiden.sound[1], 0); 
		Mix_VolumeChunk(raiden.sound[2], 0);
		Mix_VolumeChunk(slendy.sound[0], 0);
		Mix_VolumeChunk(slendy.sound[1], 0);
		Mix_VolumeChunk(slendy.sound[2], 0);
	}
	game_over=SDL_DisplayFormatAlpha(IMG_Load("game over.png")); //image game over

	// les images du guerrier illustrant tous ses mouvement (de 0 a 8)
	war_img[0]=SDL_DisplayFormatAlpha(IMG_Load("war mvt 1.png")); 
	war_img[1]=SDL_DisplayFormatAlpha(IMG_Load("war mvt 2.png"));
	war_img[2]=SDL_DisplayFormatAlpha(IMG_Load("war mvt 3.png"));
	war_img[3]=SDL_DisplayFormatAlpha(IMG_Load("war mvt 4.png"));
	war_img[4]=SDL_DisplayFormatAlpha(IMG_Load("war mvt 5.png"));
	war_img[5]=SDL_DisplayFormatAlpha(IMG_Load("war mvt 6.png"));
	war_img[6]=SDL_DisplayFormatAlpha(IMG_Load("war mvt 7.png"));
	war_img[7]=SDL_DisplayFormatAlpha(IMG_Load("war mvt 8.png"));
	war_img[8]=SDL_DisplayFormatAlpha(IMG_Load("war select.png"));

	// les images de l'archer illustrant tous ses mouvement (de 0 a 3)
	archer_img[0]=SDL_DisplayFormatAlpha(IMG_Load("archer mvt 1.png")); 
	archer_img[1]=SDL_DisplayFormatAlpha(IMG_Load("archer mvt 2.png"));
	archer_img[2]=SDL_DisplayFormatAlpha(IMG_Load("archet mvt 3.png"));
	archer_img[3]=SDL_DisplayFormatAlpha(IMG_Load("archer select.png"));

	// barre de vie vide de chaque ennemi (de 0 a 5)
	barre_ennemy[0]=SDL_DisplayFormatAlpha(IMG_Load("barre vide ennemie 1.png")); 
	barre_ennemy[1]=SDL_DisplayFormatAlpha(IMG_Load("barre vide ennemie 2.png"));
	barre_ennemy[2]=SDL_DisplayFormatAlpha(IMG_Load("barre vide ennemie 3.png"));
	barre_ennemy[3]=SDL_DisplayFormatAlpha(IMG_Load("barre vide ennemie 4.png"));
	barre_ennemy[4]=SDL_DisplayFormatAlpha(IMG_Load("barre vide ennemie 5.png"));
	barre_ennemy[5]=SDL_DisplayFormatAlpha(IMG_Load("barre vide ennemie 6.png"));

	// vie de chaque ennemi (image d'une petite barre rouge) (de 0 a 5)
	vie_ennemy[0]=SDL_DisplayFormatAlpha(IMG_Load("vie ennemie 1.png")); 
	vie_ennemy[1]=SDL_DisplayFormatAlpha(IMG_Load("vie ennemie 2.png"));
	vie_ennemy[2]=SDL_DisplayFormatAlpha(IMG_Load("vie ennemie 3.png"));
	vie_ennemy[3]=SDL_DisplayFormatAlpha(IMG_Load("vie ennemie 4.png"));
	vie_ennemy[4]=SDL_DisplayFormatAlpha(IMG_Load("vie ennemie 5.png"));
	vie_ennemy[5]=SDL_DisplayFormatAlpha(IMG_Load("vie ennemie 6.png"));

	// boucle d'initialisation des position de chauqe ennemi
	for (i=0;i<3;i++)   
	{
		slot[i].x=996;
	}
	for (i=3;i<6;i++)
	{
		slot[i].x=650;
	}
	slot[0].x=996;
	slot[0].y=3;
	slot[1].y=124;
	slot[2].y=247;
	slot[3].y=3;
	slot[4].y=124;
	slot[5].y=247;

	// Initialisation des ennemies
	for (i=0;i<nbr_archer;i++)
	{
		ennemy[i]=Init_archer(lvl,archer_img,barre_ennemy[i],vie_ennemy[i],slot[i]);
	}
	for (i=nbr_archer;i<nbr_ennemies;i++)
	{
		ennemy[i]=Init_war(lvl,war_img,barre_ennemy[i],vie_ennemy[i],slot[i]);
	}

	barre_init(nbr_ennemies,ennemy,&raiden,&slendy); //Initialisation des barres
	affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
	if (raiden.presence!=0)
	{
		SDL_BlitSurface(raiden.sorts,NULL,screen,NULL);
	} //affichage de la barre des sorts de Raiden
	else
	{
		SDL_BlitSurface(slendy.sorts,NULL,screen,NULL);
	}
	barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy); //affichages des tous les barres
	SDL_Flip(screen);
	
	do
	{
		SDL_WaitEvent(&event);
		if (tour==1)
		{
			SDL_BlitSurface(raiden.sorts,NULL,screen,NULL);
		}
		else if (tour==2)
		{
			SDL_BlitSurface(slendy.sorts,NULL,screen,NULL);
		}
		SDL_Flip(screen);
		if (raiden.presence==0)
		{
			tour=2;
		}
		if (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_BACKSPACE)
		{
			continuer=0;	
		}
		else if (event.key.keysym.sym==SDLK_ESCAPE) //affichage menu pause
		{
			rep=menu_pause(screen,sound,fullscreen);
			if (rep==0) //quitter
			{
				continuer=0;
				win=2;
			}
			else if (rep==1) //reprendre la partie
			{
				affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
				if (tour==1)
				{
					SDL_BlitSurface(raiden.sorts,NULL,screen,NULL);
				}
				else if (tour==2)
				{
					SDL_BlitSurface(slendy.sorts,NULL,screen,NULL);
				}
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				SDL_Flip(screen);
			}
			if (*sound==0) //verification si il y a eu des changement des options sonores si sound=0 alors le son sera descativé
			{
				Mix_VolumeChunk(arrow_sound, 0);
				Mix_VolumeChunk(blood_explosion, 0);
				Mix_VolumeChunk(warrior_sound, 0);
				Mix_VolumeChunk(raiden.sound[0], 0);
				Mix_VolumeChunk(raiden.sound[1], 0);
				Mix_VolumeChunk(raiden.sound[2], 0);
				Mix_VolumeChunk(slendy.sound[0], 0);
				Mix_VolumeChunk(slendy.sound[1], 0);
				Mix_VolumeChunk(slendy.sound[2], 0);
			}
		}
		else if (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_TAB && (tour==1 || tour==2) && appui==0) //choisir la cible (condition:tour de raiden)
		{
			appui=1;
			cible++;
			if (cible>nbr_ennemies)
			{
				cible=1;					
			}
			while (ennemy[cible-1].type==0)
			{
				cible++;
			}
		
			selection(back,screen,pos_map,cible,nbr_ennemies,ennemy,raiden,slendy);
			if (tour==1)
			{
				SDL_BlitSurface(raiden.sorts,NULL,screen,NULL);
			}
			else if (tour==2)
			{
				SDL_BlitSurface(slendy.sorts,NULL,screen,NULL);
			}
			barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		}
		else if (event.type==SDL_KEYUP && event.key.keysym.sym==SDLK_TAB)
		{
			appui=0;
		}
		else if (event.key.keysym.sym==SDLK_z && tour==1 && cible>0 && raiden.presence!=0) //Lancement de l'attaque 2
		{
			if (raiden.mana>=4)
			{
				attack2(back,screen,pos_map, cible,  nbr_ennemies, raiden,  slendy, ennemy);
				tour=2;
				raiden.mana=raiden.mana-4;  //diminution de la mana de Raiden
				if (raiden.mana<0)
				{
					raiden.mana=0;
				}
				ennemy[cible-1].life=ennemy[cible-1].life-raiden.attack2; //diminution de la vie de l'ennemi
				affich_degat(screen,degat,raiden.attack2,slot[cible-1],police);//afficher les dégâts causés par l'attaque
				if (ennemy[cible-1].life<0)
				{
					ennemy[cible-1].life=0;
				}
				if (cible>=1 && cible<=3) //reduction de la vie de la cible dans la barre
				{
					ennemy[cible-1].posbar.w=1050+ennemy[cible-1].rapport*ennemy[cible-1].life;
				}
				else if (cible>=4 && cible<=6)
				{
					ennemy[cible-1].posbar.w=795+ennemy[cible-1].rapport*ennemy[cible-1].life;
				}
				raiden.posbar[1].w=77+raiden.rapport[1]*raiden.mana; //nouvelle valeur de la mana de Raiden dans la barre
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				if (ennemy[cible-1].life<=0) //Au cas où la cible meurt
				{
					death_animation(back ,screen,pos_map,nbr_ennemies,cible,blood_explosion,raiden,slendy,ennemy);
					morts=morts+1;
				}
				cible=0;
			}
			else
			{
				affiche_msg(screen,police);
			}
		}
		else if (event.key.keysym.sym==SDLK_a && tour==1 && cible>0 && raiden.presence!=0) //Lancement de l'attaque 1
		{
				attack1(back,screen,pos_map,nbr_ennemies,cible,raiden,slendy,ennemy);
				tour=2;
				raiden.mana=raiden.mana+4; //Gain de mana
				if (raiden.mana>10)
				{
					raiden.mana=10;
				}
				ennemy[cible-1].life=ennemy[cible-1].life-raiden.attack1;
				affich_degat(screen,degat,raiden.attack1,slot[cible-1],police);
				if (ennemy[cible-1].life<0)
				{
					ennemy[cible-1].life=0;
				}
				if (cible>=1 && cible<=3)
					{
						ennemy[cible-1].posbar.w=1055+ennemy[cible-1].rapport*ennemy[cible-1].life;
					}
				else if (cible>=4 && cible<=6)
				{
					ennemy[cible-1].posbar.w=795+ennemy[cible-1].rapport*ennemy[cible-1].life;
				}
				raiden.posbar[1].w=77+raiden.rapport[1]*raiden.mana;
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				if (ennemy[cible-1].life<=0)
				{
					death_animation(back ,screen,pos_map,nbr_ennemies,cible,blood_explosion,raiden,slendy,ennemy);
					morts=morts+1;
				}
				cible=0;
		}
		else if (event.key.keysym.sym==SDLK_e  && tour==1 && raiden.presence!=0 && cible>0) //Lancement de l'attaque 3
		{
			if (raiden.mana>=6)
			{
				attack3(back,screen,pos_map,nbr_ennemies,raiden,slendy,ennemy);
				tour=2;
				raiden.mana=raiden.mana-6;
				if (raiden.mana<0)
				{
					raiden.mana=0;
				}
				raiden.posbar[1].w=77+raiden.rapport[1]*raiden.mana;
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				for (i=0;i<nbr_ennemies;i++)
				{
					ennemy[i].life=ennemy[i].life-raiden.attack3;
					if (ennemy[i].type!=0)
					{
						affich_degat(screen,degat,raiden.attack3,slot[i],police);
					}
					if (ennemy[i].life<0)
					{
						ennemy[i].life=0;
					}
					if (i>=0 && i<=2)
					{
						ennemy[i].posbar.w=1050+ennemy[i].rapport*ennemy[i].life;
					}
					else if (i>=3 && i<=5)
					{
						ennemy[i].posbar.w=795+ennemy[i].rapport*ennemy[i].life;
					}
					barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
					if (ennemy[i].life<=0 && ennemy[i].type!=0)
					{
						death_animation(back ,screen,pos_map,nbr_ennemies,i+1,blood_explosion,raiden,slendy,ennemy);
						morts=morts+1;
					}
				}
				cible=0;
			}
			else
			{
				affiche_msg(screen,police);
			}
		}
		if (morts>=nbr_ennemies) //Si tous les ennmies sont tués, on mets fin à la boucle = fin du combat
		{
			continuer=0;
		}
		if (event.key.keysym.sym==SDLK_a && tour==2 && cible>0 && slendy.presence!=0)
		{
				attack1_slendy(back,screen,pos_map,cible,nbr_ennemies,raiden,slendy,ennemy);
				tour=0;
				slendy.mana=slendy.mana+15;  //diminution de la mana de Raiden
				if (slendy.mana>40)
				{
					slendy.mana=40;
				}
				ennemy[cible-1].life=ennemy[cible-1].life-slendy.attack1; //diminution de la vie de l'ennemi
				affich_degat(screen,degat,slendy.attack1,slot[cible-1],police);//afficher les dégâts causés par l'attaque
				if (ennemy[cible-1].life<0)
				{
					ennemy[cible-1].life=0;
				}
				if (cible>=1 && cible<=3) //reduction de la vie de la cible dans la barre
				{
				ennemy[cible-1].posbar.w=1050+ennemy[cible-1].rapport*ennemy[cible-1].life;
				}
				else if (cible>=4 && cible<=6)
				{
					ennemy[cible-1].posbar.w=795+ennemy[cible-1].rapport*ennemy[cible-1].life;
				}
				slendy.posbar[1].w=411+slendy.rapport[1]*slendy.mana; //nouvelle valeur de la mana de Raiden dans la barre
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				if (ennemy[cible-1].life<=0) //Au cas où la cible meurt
				{
					death_animation(back ,screen,pos_map,nbr_ennemies,cible,blood_explosion,raiden,slendy,ennemy);
					morts=morts+1;
				}
			cible=0;
		}
		else if (event.key.keysym.sym==SDLK_z && tour==2 && slendy.presence!=0 && cible>0)
		{
			if (slendy.mana<25)
			{
				affiche_msg(screen,police);
			}
			else
			{
				attack2_slendy(back,screen,pos_map,nbr_ennemies,raiden,slendy,ennemy);
				tour=0;
				slendy.mana=slendy.mana-25;
				if (slendy.mana<0)
				{
					slendy.mana=0;
				}
				slendy.posbar[1].w=411+slendy.rapport[1]*slendy.mana;
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				for (i=0;i<nbr_ennemies;i++)
				{
					ennemy[i].life=ennemy[i].life-slendy.attack2;
					if (ennemy[i].type!=0)
					{
						affich_degat(screen,degat,slendy.attack2,slot[i],police);
					}
					if (ennemy[i].life<0)
					{
					ennemy[i].life=0;
					}
					if (i>=0 && i<=2)
					{
						ennemy[i].posbar.w=1050+ennemy[i].rapport*ennemy[i].life;
					}
					else if (i>=3 && i<=5)
					{
						ennemy[i].posbar.w=795+ennemy[i].rapport*ennemy[i].life;
					}
					barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
					if (ennemy[i].life<=0 && ennemy[i].type!=0)
					{
						death_animation(back ,screen,pos_map,nbr_ennemies,i+1,blood_explosion,raiden,slendy,ennemy);
						morts=morts+1;
					}
				}
			cible=0;
			}
		}
		else if (event.key.keysym.sym==SDLK_e && tour==2 && slendy.presence!=0 && cible>0)
		{
			if (slendy.mana<25)
			{
				affiche_msg(screen,police);
			}
			else
			{
				attack3_slendy(back,screen,pos_map,nbr_ennemies,raiden,slendy,ennemy);
				tour=0;
				slendy.mana=slendy.mana-25;
				if (slendy.mana<0)
				{
					slendy.mana=0;
				}
				slendy.posbar[1].w=411+slendy.rapport[1]*slendy.mana;
				if (raiden.presence!=0)
				{
					raiden.life=raiden.life+slendy.attack3;
					if (raiden.life>raiden.life_max)
					{
						raiden.life=raiden.life_max;
					}
					raiden.posbar[0].w=77+raiden.rapport[0]*raiden.life;
				}
				slendy.life=slendy.life+slendy.attack3;
				if (slendy.life>slendy.life_max)
				{
					slendy.life=slendy.life_max;
				}
				slendy.posbar[0].w=411+slendy.rapport[0]*slendy.life;
				affich_heal(screen,degat,slendy.attack3,slendy.pos,police);
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				cible=0;
			}
		}
		if (morts>=nbr_ennemies) //Si tous les ennmies sont tués, on mets fin à la boucle = fin du combat
		{
			continuer=0;
		}
		if (slendy.presence==0 && tour==2)
		{
			tour=0;
		}
		if (tour==0) //tour de l'ennemi
		{
			for (i=0;i<nbr_ennemies;i++)
			{
				if (ennemy[i].type==1 && (raiden.presence!=0 || slendy.presence!=0)) //si l'ennemi est un archer, et Raiden n'est pas mort
				{
					if (raiden.presence==0 && slendy.presence!=0)
					{
						cible_ennemi=2;
					}
					else if (raiden.presence!=0 && slendy.presence==0)
					{
						cible_ennemi=1;
					}
					else
					{
						cible_ennemi=(rand() % (2))+1;
					}
					attack_archer(screen,back,pos_map,nbr_ennemies,i,arrow_sound,raiden,slendy,ennemy,cible_ennemi); //attaque de l'archer
					if (cible_ennemi==1)
					{
						raiden.life=raiden.life-ennemy[i].attaque; //diminution de la vie de raiden
						if (raiden.life<0)
						{
							raiden.life=0;
						}
						raiden.posbar[0].w=77+raiden.rapport[0]*raiden.life;//nouvelle image de la barre de vie de raiden
						affich_degat(screen,degat,ennemy[i].attaque,raiden.pos,police); //affichage de dégât
						if (raiden.life<=0)
						{
							death_animationhero(back ,screen,pos_map,nbr_ennemies,blood_explosion,raiden,slendy,ennemy);// animation de la mort de raiden
							raiden.presence=0;
							affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
						}
					}
					else if (cible_ennemi==2)
					{
						slendy.life=slendy.life-ennemy[i].attaque; //diminution de la vie de slendy
						if (slendy.life<0)
						{
							slendy.life=0;
						}
						slendy.posbar[0].w=411+slendy.rapport[0]*slendy.life;//nouvelle image de la barre de vie de raiden
						affich_degat(screen,degat,ennemy[i].attaque,slendy.pos,police); //affichage de dégât
						if (slendy.life<=0)
						{
							death_animationhero(back ,screen,pos_map,nbr_ennemies,blood_explosion,raiden,slendy,ennemy);// animation de la mort de raiden
							slendy.presence=0;
							affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
						}
					}
					barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
					if (raiden.presence==0 && slendy.presence==0) //mort de Raiden
					{
						SDL_BlitSurface(game_over,NULL,screen,NULL);// affichage de "game over"
						SDL_Flip(screen);
						SDL_Delay(3000);
						continuer=0;
						win=0;
					}
				}
				else if (ennemy[i].type==2 && (raiden.presence!=0 || slendy.presence!=0))// si l'ennemi est un guerrier et raiden n'est pas mort
				{
					if (raiden.presence==0 && slendy.presence!=0)
					{
						cible_ennemi=2;
					}
					else if (raiden.presence!=0 && slendy.presence==0)
					{
						cible_ennemi=1;
					}
					else
					{
						cible_ennemi=(rand() % (2))+1;
					}
					attack_warrior(screen,back,pos_map,nbr_ennemies,i,warrior_sound,raiden,slendy,ennemy,cible_ennemi); //attaque du guerrier
					if (cible_ennemi==1)
					{
						raiden.life=raiden.life-ennemy[i].attaque; //diminution de la vie de raiden
						if (raiden.life<0)
						{
							raiden.life=0;
						}
						raiden.posbar[0].w=77+raiden.rapport[0]*raiden.life;//nouvelle image de la barre de vie de raiden
						affich_degat(screen,degat,ennemy[i].attaque,raiden.pos,police);
						if (raiden.life<=0)
						{
							death_animationhero(back ,screen,pos_map,nbr_ennemies,blood_explosion,raiden,slendy,ennemy);// animation de la mort de raiden
							raiden.presence=0;
							affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
						}
					}
					else if (cible_ennemi==2)
					{
						slendy.life=slendy.life-ennemy[i].attaque; //diminution de la vie de slendy
						if (slendy.life<0)
						{
							slendy.life=0;
						}
						slendy.posbar[0].w=411+slendy.rapport[0]*slendy.life;//nouvelle image de la barre de vie de raiden
						affich_degat(screen,degat,ennemy[i].attaque,slendy.pos,police);
						if (slendy.life<=0)
						{
							death_animationhero(back ,screen,pos_map,nbr_ennemies,blood_explosion,raiden,slendy,ennemy);// animation de la mort de raiden
							slendy.presence=0;
							affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
						}
					}
					barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
					if (raiden.presence==0 && slendy.presence==0)
					{
						SDL_BlitSurface(game_over,NULL,screen,NULL);
						SDL_Flip(screen);
						SDL_Delay(3000);
						continuer=0;
						win=0;
					}
				}
				tour=1;//changement de tour->tour du joueur
			}
			
		}

	}
	while (continuer==1);

	
	//partie de libération
	free_raiden(raiden);
	free_slendy(slendy);
	for (i=0;i<4;i++)
	{	
		SDL_FreeSurface(archer_img[i]);
	}
	for (i=0;i<9;i++)
	{
		SDL_FreeSurface(war_img[i]);
	}
	for (i=0;i<6;i++)
	{
		SDL_FreeSurface(vie_ennemy[i]);
		SDL_FreeSurface(barre_ennemy[i]);
	}
	SDL_FreeSurface(degat);
	SDL_FreeSurface(game_over);
	Mix_FreeChunk(arrow_sound);
	Mix_FreeChunk(blood_explosion);
	Mix_FreeChunk(warrior_sound);
	TTF_CloseFont(police);
	TTF_Quit();
	return win;
}










int cbt_boss (SDL_Surface *screen, SDL_Surface *back, SDL_Rect pos_map, int *sound, int *fullscreen, int lvl)
{
	SDL_Surface *barre_ennemy[6]={NULL}, *vie_ennemy[6]={NULL}, *degat=NULL, *game_over=NULL;
	SDL_Rect slot[6], barre_ennemy_pos[6];
	int i,continuer=1,j=0,nbr_ennemies=1,cible=0,tour=1,appui=0,morts=0,afficher=0,win=1,rep,cible_ennemi,attackealancer,degatboss;
	hero raiden, slendy, hero_cible;
	perso ennemy[nbr_ennemies];
	SDL_Event event,event1;
	Mix_Chunk *blood_explosion, *sound_boss3_4[2];
	TTF_Font *police;

	TTF_Init();

	police=TTF_OpenFont("Ace Records.ttf",70); // police affichage dégât
	blood_explosion=Mix_LoadWAV("blood explosion.ogg"); //son pour la mort d'un personnage
	raiden=Init_raiden(lvl); // Initialisation de Raiden
	slendy=Init_slendy(lvl); // Init de slendy
	if (lvl==3)
	{
		sound_boss3_4[0]=Mix_LoadWAV("water.ogg");
		sound_boss3_4[1]=Mix_LoadWAV("boule_feu_01.ogg");
	}
	else if (lvl==4)
	{
		sound_boss3_4[0]=Mix_LoadWAV("son cp attack1.ogg");
		sound_boss3_4[1]=Mix_LoadWAV("son cp attack2.ogg");
	}
	else if (lvl==5)
	{
		sound_boss3_4[0]=Mix_LoadWAV("son bleak attack1.ogg");
		sound_boss3_4[1]=Mix_LoadWAV("son bleack attack ult.ogg");
	}
	if (*sound==0) //desactivation du son
	{
		Mix_VolumeChunk(blood_explosion, 0); 
		Mix_VolumeChunk(raiden.sound[0], 0); 
		Mix_VolumeChunk(raiden.sound[1], 0); 
		Mix_VolumeChunk(raiden.sound[2], 0);
		Mix_VolumeChunk(slendy.sound[0], 0);
		Mix_VolumeChunk(slendy.sound[1], 0);
		Mix_VolumeChunk(slendy.sound[2], 0);
		Mix_VolumeChunk(sound_boss3_4[0], 0);
		Mix_VolumeChunk(sound_boss3_4[1], 0);
	}
	game_over=SDL_DisplayFormatAlpha(IMG_Load("game over.png")); //image game over

	// barre de vie vide de chaque ennemi (de 0 a 5)
	barre_ennemy[0]=SDL_DisplayFormatAlpha(IMG_Load("barre vide ennemie 1.png"));

	// vie de chaque ennemi (image d'une petite barre rouge) (de 0 a 5)
	vie_ennemy[0]=SDL_DisplayFormatAlpha(IMG_Load("vie ennemie 1.png"));

	// boucle d'initialisation des position de chauqe ennemi
	slot[0].x=996;
	slot[0].y=100;


	// Initialisation des ennemies
	if (lvl==3)
	{
		ennemy[0]=Init_boss_lvl3(lvl,barre_ennemy[0],vie_ennemy[0],slot[0]);
	}
	else if (lvl==4)
	{
		ennemy[0]=Init_boss_lvl4(lvl,barre_ennemy[0],vie_ennemy[0],slot[0]);
	}
	else if (lvl==5)
	{
		ennemy[0]=Init_boss_lvl5(lvl,barre_ennemy[0],vie_ennemy[0],slot[0]);
	}
	barre_init(nbr_ennemies,ennemy,&raiden,&slendy); //Initialisation des barres
	affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);

	SDL_BlitSurface(raiden.sorts,NULL,screen,NULL); //affichage de la barre des sorts de Raiden
	barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy); //affichages des tous les barres
	SDL_Flip(screen);
	
	do
	{
		SDL_WaitEvent(&event);
		if (tour==1)
		{
			SDL_BlitSurface(raiden.sorts,NULL,screen,NULL);
		}
		else if (tour==2)
		{
			SDL_BlitSurface(slendy.sorts,NULL,screen,NULL);
		}
		SDL_Flip(screen);
		if (raiden.presence==0)
		{
			tour=2;
		}
		if (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_BACKSPACE)
		{
			continuer=0;	
		}
		else if (event.key.keysym.sym==SDLK_ESCAPE) //affichage menu pause
		{
			rep=menu_pause(screen,sound,fullscreen);
			if (rep==0) //quitter
			{
				continuer=0;
				win=2;
			}
			else if (rep==1) //reprendre la partie
			{
				affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
				if (tour==1)	
				{
					SDL_BlitSurface(raiden.sorts,NULL,screen,NULL);
				}
				else if (tour==2)
				{
					SDL_BlitSurface(slendy.sorts,NULL,screen,NULL);
				}
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				SDL_Flip(screen);
			}
			if (*sound==0) //verification si il y a eu des changement des options sonores si sound=0 alors le son sera descativé
			{
				Mix_VolumeChunk(blood_explosion, 0);
				Mix_VolumeChunk(raiden.sound[0], 0);
				Mix_VolumeChunk(raiden.sound[1], 0);
				Mix_VolumeChunk(raiden.sound[2], 0);
				Mix_VolumeChunk(slendy.sound[0], 0);
				Mix_VolumeChunk(slendy.sound[1], 0);
				Mix_VolumeChunk(slendy.sound[2], 0);
				Mix_VolumeChunk(sound_boss3_4[0], 0);
				Mix_VolumeChunk(sound_boss3_4[1], 0);
			}
		}
		else if (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_TAB && (tour==1 || tour==2) && appui==0) //choisir la cible (condition:tour de raiden)
		{
			appui=1;
			cible++;
			if (cible>nbr_ennemies)
			{
				cible=1;					
			}
			while (ennemy[cible-1].type==0)
			{
				cible++;
			}
		
			selection(back,screen,pos_map,cible,nbr_ennemies,ennemy,raiden,slendy);
			if (tour==1)
			{
				SDL_BlitSurface(raiden.sorts,NULL,screen,NULL);
			}
			else if (tour==2)
			{
				SDL_BlitSurface(slendy.sorts,NULL,screen,NULL);
			}
			barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		}
		else if (event.type==SDL_KEYUP && event.key.keysym.sym==SDLK_TAB)
		{
			appui=0;
		}
		else if (event.key.keysym.sym==SDLK_z && tour==1 && cible>0 && raiden.presence!=0) //Lancement de l'attaque 2
		{
			if (raiden.mana>=4)
			{
				attack2(back,screen,pos_map, cible,  nbr_ennemies, raiden,  slendy, ennemy);
				tour=2;
				raiden.mana=raiden.mana-4;  //diminution de la mana de Raiden
				if (raiden.mana<0)
				{
					raiden.mana=0;
				}
				ennemy[cible-1].life=ennemy[cible-1].life-raiden.attack2; //diminution de la vie de l'ennemi
				affich_degat(screen,degat,raiden.attack2,slot[cible-1],police);//afficher les dégâts causés par l'attaque
				if (ennemy[cible-1].life<0)
				{
					ennemy[cible-1].life=0;
				}
				if (cible>=1 && cible<=3) //reduction de la vie de la cible dans la barre
				{
					ennemy[cible-1].posbar.w=1050+ennemy[cible-1].rapport*ennemy[cible-1].life;
				}
				else if (cible>=4 && cible<=6)
				{
					ennemy[cible-1].posbar.w=795+ennemy[cible-1].rapport*ennemy[cible-1].life;
				}
				raiden.posbar[1].w=77+raiden.rapport[1]*raiden.mana; //nouvelle valeur de la mana de Raiden dans la barre
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				if (ennemy[cible-1].life<=0) //Au cas où la cible meurt
				{
					death_animation(back ,screen,pos_map,nbr_ennemies,cible,blood_explosion,raiden,slendy,ennemy);
					morts=morts+1;
				}
				cible=0;
			}
			else
			{
				affiche_msg(screen,police);
			}
		}
		else if (event.key.keysym.sym==SDLK_a && tour==1 && cible>0 && raiden.presence!=0) //Lancement de l'attaque 1
		{
				attack1(back,screen,pos_map,nbr_ennemies,cible,raiden,slendy,ennemy);
				tour=2;
				raiden.mana=raiden.mana+4; //Gain de mana
				if (raiden.mana>10)
				{
					raiden.mana=10;
				}
				ennemy[cible-1].life=ennemy[cible-1].life-raiden.attack1;
				affich_degat(screen,degat,raiden.attack1,slot[cible-1],police);
				if (ennemy[cible-1].life<0)
				{
					ennemy[cible-1].life=0;
				}
				if (cible>=1 && cible<=3)
					{
						ennemy[cible-1].posbar.w=1055+ennemy[cible-1].rapport*ennemy[cible-1].life;
					}
				else if (cible>=4 && cible<=6)
				{
					ennemy[cible-1].posbar.w=795+ennemy[cible-1].rapport*ennemy[cible-1].life;
				}
				raiden.posbar[1].w=77+raiden.rapport[1]*raiden.mana;
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				if (ennemy[cible-1].life<=0)
				{
					death_animation(back ,screen,pos_map,nbr_ennemies,cible,blood_explosion,raiden,slendy,ennemy);
					morts=morts+1;
				}
				cible=0;
		}
		else if (event.key.keysym.sym==SDLK_e  && tour==1 && raiden.presence!=0 && cible>0) //Lancement de l'attaque 3
		{
			if (raiden.mana>=6)
			{
				attack3(back,screen,pos_map,nbr_ennemies,raiden,slendy,ennemy);
				tour=2;
				raiden.mana=raiden.mana-6;
				if (raiden.mana<0)
				{
					raiden.mana=0;
				}
				raiden.posbar[1].w=77+raiden.rapport[1]*raiden.mana;
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				for (i=0;i<nbr_ennemies;i++)
				{
					ennemy[i].life=ennemy[i].life-raiden.attack3;
					if (ennemy[i].type!=0)
					{
						affich_degat(screen,degat,raiden.attack3,slot[i],police);
					}
					if (ennemy[i].life<0)
					{
						ennemy[i].life=0;
					}
					if (i>=0 && i<=2)
					{
						ennemy[i].posbar.w=1050+ennemy[i].rapport*ennemy[i].life;
					}
					else if (i>=3 && i<=5)
					{
						ennemy[i].posbar.w=795+ennemy[i].rapport*ennemy[i].life;
					}
					barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
					if (ennemy[i].life<=0 && ennemy[i].type!=0)
					{
						death_animation(back ,screen,pos_map,nbr_ennemies,i+1,blood_explosion,raiden,slendy,ennemy);
						morts=morts+1;
					}
				}
				cible=0;
			}
			else
			{
				affiche_msg(screen,police);
			}
		}
		if (morts>=nbr_ennemies) //Si tous les ennmies sont tués, on mets fin à la boucle = fin du combat
		{
			continuer=0;
		}
		if (event.key.keysym.sym==SDLK_a && tour==2 && cible>0 && slendy.presence!=0)
		{
				attack1_slendy(back,screen,pos_map,cible,nbr_ennemies,raiden,slendy,ennemy);
				tour=0;
				slendy.mana=slendy.mana+15;  //diminution de la mana de Raiden
				if (slendy.mana>40)
				{
					slendy.mana=40;
				}
				ennemy[cible-1].life=ennemy[cible-1].life-slendy.attack1; //diminution de la vie de l'ennemi
				affich_degat(screen,degat,slendy.attack1,slot[cible-1],police);//afficher les dégâts causés par l'attaque
				if (ennemy[cible-1].life<0)
				{
					ennemy[cible-1].life=0;
				}
				if (cible>=1 && cible<=3) //reduction de la vie de la cible dans la barre
				{
				ennemy[cible-1].posbar.w=1050+ennemy[cible-1].rapport*ennemy[cible-1].life;
				}
				else if (cible>=4 && cible<=6)
				{
					ennemy[cible-1].posbar.w=795+ennemy[cible-1].rapport*ennemy[cible-1].life;
				}
				slendy.posbar[1].w=411+slendy.rapport[1]*slendy.mana; //nouvelle valeur de la mana de Raiden dans la barre
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				if (ennemy[cible-1].life<=0) //Au cas où la cible meurt
				{
					death_animation(back ,screen,pos_map,nbr_ennemies,cible,blood_explosion,raiden,slendy,ennemy);
					morts=morts+1;
				}
			cible=0;
		}
		else if (event.key.keysym.sym==SDLK_z && tour==2 && slendy.presence!=0 && cible>0)
		{
			if (slendy.mana<25)
			{
				affiche_msg(screen,police);
			}
			else
			{
				attack2_slendy(back,screen,pos_map,nbr_ennemies,raiden,slendy,ennemy);
				tour=0;
				slendy.mana=slendy.mana-25;
				if (slendy.mana<0)
				{
					slendy.mana=0;
				}
				slendy.posbar[1].w=411+slendy.rapport[1]*slendy.mana;
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				for (i=0;i<nbr_ennemies;i++)
				{
					ennemy[i].life=ennemy[i].life-slendy.attack2;
					if (ennemy[i].type!=0)
					{
						affich_degat(screen,degat,slendy.attack2,slot[i],police);
					}
					if (ennemy[i].life<0)
					{
					ennemy[i].life=0;
					}
					if (i>=0 && i<=2)
					{
						ennemy[i].posbar.w=1050+ennemy[i].rapport*ennemy[i].life;
					}
					else if (i>=3 && i<=5)
					{
						ennemy[i].posbar.w=795+ennemy[i].rapport*ennemy[i].life;
					}
					barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
					if (ennemy[i].life<=0 && ennemy[i].type!=0)
					{
						death_animation(back ,screen,pos_map,nbr_ennemies,i+1,blood_explosion,raiden,slendy,ennemy);
						morts=morts+1;
					}
				}
			}
			cible=0;
		}
		else if (event.key.keysym.sym==SDLK_e && tour==2 && slendy.presence!=0 && cible>0)
		{
			if (slendy.mana<25)
			{
				affiche_msg(screen,police);
			}
			else
			{
				attack3_slendy(back,screen,pos_map,nbr_ennemies,raiden,slendy,ennemy);
				tour=0;
				slendy.mana=slendy.mana-25;
				if (slendy.mana<0)
				{
					slendy.mana=0;
				}
				slendy.posbar[1].w=411+slendy.rapport[1]*slendy.mana;
				if (raiden.presence!=0)
				{
					raiden.life=raiden.life+slendy.attack3;
					if (raiden.life>raiden.life_max)
					{
						raiden.life=raiden.life_max;
					}
					raiden.posbar[0].w=77+raiden.rapport[0]*raiden.life;
				}
				slendy.life=slendy.life+slendy.attack3;
				if (slendy.life>slendy.life_max)
				{
					slendy.life=slendy.life_max;
				}
				slendy.posbar[0].w=411+slendy.rapport[0]*slendy.life;
				affich_heal(screen,degat,slendy.attack3,slendy.pos,police);
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
			}
			cible=0;
		}
		if (morts>=nbr_ennemies) //Si tous les ennmies sont tués, on mets fin à la boucle = fin du combat
		{
			continuer=0;
		}
		if (slendy.presence==0 && tour==2)
		{
			tour=0;
		}
		if (tour==0 && ennemy[0].type!=0 && lvl==5)
		{
			attackealancer=(rand() % 3) +1;
			if (raiden.presence==0 && slendy.presence!=0)
			{
				cible_ennemi=2;
				attackealancer=1;
			}
			else if (raiden.presence!=0 && slendy.presence==0)
			{
				cible_ennemi=1;
				attackealancer=1;
			}
			else
			{
				cible_ennemi=(rand() % (2))+1;
			}
			if (attackealancer==2)
			{
				Mix_PlayChannel(-1,sound_boss3_4[1],0);
				attack_boss5_ulti(screen,back,pos_map,nbr_ennemies,j,raiden,slendy,ennemy);
				tour=1;
				degatboss=ennemy[0].attaque_ultime;
				raiden.life=raiden.life-degatboss; //diminution de la vie de raiden
				if (raiden.life<0)
				{
					raiden.life=0;
				}
				raiden.posbar[0].w=77+raiden.rapport[0]*raiden.life;//nouvelle image de la barre de vie de raiden
				affich_degat(screen,degat,degatboss,raiden.pos,police);
				if (raiden.life<=0)
				{
					death_animationhero(back ,screen,pos_map,nbr_ennemies,blood_explosion,raiden,slendy,ennemy);// animation de la mort de raiden
					raiden.presence=0;
					affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
				}
				slendy.life=slendy.life-degatboss; //diminution de la vie de slendy
				if (slendy.life<0)
				{
					slendy.life=0;
				}
				slendy.posbar[0].w=411+slendy.rapport[0]*slendy.life;//nouvelle image de la barre de vie de raiden
				affich_degat(screen,degat,degatboss,slendy.pos,police);
				if (slendy.life<=0)
				{
					death_animationhero(back ,screen,pos_map,nbr_ennemies,blood_explosion,raiden,slendy,ennemy);// animation de la mort de raiden
					slendy.presence=0;
					affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
				}
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				if (raiden.presence==0 && slendy.presence==0)
				{
					SDL_BlitSurface(game_over,NULL,screen,NULL);
					SDL_Flip(screen);
					SDL_Delay(3000);
					continuer=0;
					win=0;
				}
				tour=1;
			}
			else
			{
				Mix_PlayChannel(-1,sound_boss3_4[0],0);
				SDL_Delay(700);
				attack_boss(screen,back,pos_map,nbr_ennemies,j,raiden, slendy,ennemy,cible_ennemi,attackealancer,lvl);
				degatboss=ennemy[0].attaque;
				if (cible_ennemi==1)
				{
					raiden.life=raiden.life-degatboss; //diminution de la vie de raiden
					if (raiden.life<0)
					{
						raiden.life=0;
					}
					raiden.posbar[0].w=77+raiden.rapport[0]*raiden.life;//nouvelle image de la barre de vie de raiden
					affich_degat(screen,degat,degatboss,raiden.pos,police);
					if (raiden.life<=0)
					{
						death_animationhero(back ,screen,pos_map,nbr_ennemies,blood_explosion,raiden,slendy,ennemy);// animation de la mort de raiden
						raiden.presence=0;
						affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
					}
				}
				if (cible_ennemi==2)
				{
					slendy.life=slendy.life-degatboss; //diminution de la vie de slendy
					if (slendy.life<0)
					{
						slendy.life=0;
					}
					slendy.posbar[0].w=411+slendy.rapport[0]*slendy.life;//nouvelle image de la barre de vie de raiden
					affich_degat(screen,degat,degatboss,slendy.pos,police);
					if (slendy.life<=0)
					{
						death_animationhero(back ,screen,pos_map,nbr_ennemies,blood_explosion,raiden,slendy,ennemy);// animation de la mort de raiden
						slendy.presence=0;
						affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
					}
				}
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				if (raiden.presence==0 && slendy.presence==0)
				{
					SDL_BlitSurface(game_over,NULL,screen,NULL);
					SDL_Flip(screen);
					SDL_Delay(3000);
					continuer=0;
					win=0;
				}
				tour=1;
			}
		}
		if (tour==0 && ennemy[0].type!=0 && (lvl==3 || lvl==4))
		{
			attackealancer=(rand() % 3) +1;
			if (raiden.presence==0 && slendy.presence!=0)
			{
				cible_ennemi=2;
				attackealancer=1;
			}
			else if (raiden.presence!=0 && slendy.presence==0)
			{
				cible_ennemi=1;
				attackealancer=1;
			}
			else
			{
				cible_ennemi=(rand() % (2))+1;
			}
			if (attackealancer==2)
			{
				Mix_PlayChannel(-1,sound_boss3_4[1],0);
			}
			else
			{
				Mix_PlayChannel(-1,sound_boss3_4[0],0);
			}
			attack_boss(screen,back,pos_map,nbr_ennemies,j,raiden, slendy,ennemy,cible_ennemi,attackealancer,lvl);
			if (attackealancer==2)
			{
				degatboss=ennemy[0].attaque_ultime;
				if (cible_ennemi==1 && slendy.presence!=0)
				{
					cible_ennemi=2;
					attack_boss(screen,back,pos_map,nbr_ennemies,j,raiden, slendy,ennemy,cible_ennemi,attackealancer,lvl);
					cible_ennemi=3;
				}
				else if (cible_ennemi==2 && raiden.presence!=0)
				{
					cible_ennemi=1;
					attack_boss(screen,back,pos_map,nbr_ennemies,j,raiden, slendy,ennemy,cible_ennemi,attackealancer,lvl);
					cible_ennemi=3;
				}
			}
			else
			{
				degatboss=ennemy[0].attaque;
			}
			if (cible_ennemi==1 || cible_ennemi==3)
			{
				raiden.life=raiden.life-degatboss; //diminution de la vie de raiden
				if (raiden.life<0)
				{
					raiden.life=0;
				}
				raiden.posbar[0].w=77+raiden.rapport[0]*raiden.life;//nouvelle image de la barre de vie de raiden
				affich_degat(screen,degat,degatboss,raiden.pos,police);
				if (raiden.life<=0)
				{
					death_animationhero(back ,screen,pos_map,nbr_ennemies,blood_explosion,raiden,slendy,ennemy);// animation de la mort de raiden
					raiden.presence=0;
					affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
				}
			}
			if (cible_ennemi==2 || cible_ennemi==3)
			{
				slendy.life=slendy.life-degatboss; //diminution de la vie de slendy
				if (slendy.life<0)
				{
					slendy.life=0;
				}
				slendy.posbar[0].w=411+slendy.rapport[0]*slendy.life;//nouvelle image de la barre de vie de raiden
				affich_degat(screen,degat,degatboss,slendy.pos,police);
				if (slendy.life<=0)
				{
					death_animationhero(back ,screen,pos_map,nbr_ennemies,blood_explosion,raiden,slendy,ennemy);// animation de la mort de raiden
					slendy.presence=0;
					affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
				}
			}
			barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
			if (raiden.presence==0 && slendy.presence==0)
			{
				SDL_BlitSurface(game_over,NULL,screen,NULL);
				SDL_Flip(screen);
				SDL_Delay(3000);
				continuer=0;
				win=0;
			}
			tour=1;
		}
	}
	while (continuer==1);

	
	//partie de libération
	free_boss(ennemy[0]);
	SDL_FreeSurface(barre_ennemy[0]);
	SDL_FreeSurface(vie_ennemy[0]);
	free_raiden(raiden);
	free_slendy(slendy);
	Mix_FreeChunk(sound_boss3_4[0]);
	Mix_FreeChunk(sound_boss3_4[1]);
	SDL_FreeSurface(degat);
	SDL_FreeSurface(game_over);
	Mix_FreeChunk(blood_explosion);
	TTF_CloseFont(police);
	TTF_Quit();
	return win;
}




























void attack1(SDL_Surface *back,SDL_Surface *screen,SDL_Rect pos_map,int nbr_ennemies,int cible,hero raiden,hero slendy,perso ennemy[nbr_ennemies])
{
	SDL_Surface *attack2_img[4]={NULL}, *sans_epee=NULL;
	int j,i,arrive=0;
	SDL_Rect pos;

	//position initiale de l'épée
	pos.x=300;
	pos.y=50;

	//les images de l'animation de l'atttaque
	attack2_img[0]=SDL_DisplayFormatAlpha(IMG_Load("rotation 1.png"));
	attack2_img[1]=SDL_DisplayFormatAlpha(IMG_Load("rotation 2.png"));
	attack2_img[2]=SDL_DisplayFormatAlpha(IMG_Load("rotation 3.png"));
	attack2_img[3]=SDL_DisplayFormatAlpha(IMG_Load("rotation 4.png"));
	sans_epee=SDL_DisplayFormatAlpha(IMG_Load("pose combat_raiden sans épée.png")); //Image de Raiden sans épée
	Mix_PlayChannel(-1,raiden.sound[0],0); //son de l'attaque
	for (j=0;j<4;j++)
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		SDL_BlitSurface(raiden.img[j],NULL,screen,&raiden.pos); //animation des mouvement de raiden dans la boucle
		if(slendy.presence!=0)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		for (i=0;i<nbr_ennemies;i++)
		{
			if (ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
			}
		}
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
	}
	j=0;
	do
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		SDL_BlitSurface(sans_epee,NULL,screen,&raiden.pos);
		if(slendy.presence!=0)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		for (i=0;i<nbr_ennemies;i=i+3)
		{
			if (ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
			}
		}

		//conditions pour un affichage optimale de l'épée
		if (cible==1 || cible==4)
		{
			SDL_BlitSurface(attack2_img[j],NULL,screen,&pos);//animation de l'attaque
		}
		for (i=1;i<nbr_ennemies;i=i+3)
		{
			if (ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
			}
		}
		if (cible==2 || cible==5)
		{
			pos.y=pos.y+20;	
			SDL_BlitSurface(attack2_img[j],NULL,screen,&pos);
		}

		for (i=2;i<nbr_ennemies;i=i+3)
		{
			if (ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
			}
		}
		if (cible==3 || cible==6)
		{
			pos.y=pos.y+35;
			SDL_BlitSurface(attack2_img[j],NULL,screen,&pos);
		}
		if (pos.x>=ennemy[cible-1].pos.x && pos.x<=ennemy[cible-1].pos.x+100)
		{
			arrive=1;
			blood2_animation (back ,screen,pos_map,nbr_ennemies,cible,raiden,slendy,ennemy);// effet de sang lorsque l'attaque atteint la cible
		}
		pos.x=pos.x+100;
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
		SDL_Delay(30);
		j++;
		if (j==4)
		{
			j=0;
		}
	}
	while(arrive==0); //arriver: quand l'épée atteint la cible
	SDL_Flip(screen);
	for (j=0;j<4;j++)
	{SDL_FreeSurface(attack2_img[j]);}
	SDL_FreeSurface(sans_epee);
}
















void attack2(SDL_Surface *back, SDL_Surface *screen, SDL_Rect pos_map,int cible, int nbr_ennemies,hero raiden, hero slendy,perso ennemy[nbr_ennemies])
{
	SDL_Surface *attack1_img=NULL;
	int j,i,arrive=0;
	SDL_Rect pos;

	//position initiale de l'onde
	pos.x=300;
	pos.y=50;
	attack1_img=SDL_DisplayFormatAlpha(IMG_Load("attack1 trait4.png")); //chargement de l'image de l'attaque
	Mix_PlayChannel(-1,raiden.sound[1],0); //son de l'attaque
	SDL_Delay(50);
	for (j=0;j<4;j++)
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		SDL_BlitSurface(raiden.img[j],NULL,screen,&raiden.pos);
		if(slendy.presence!=0)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		for (i=0;i<nbr_ennemies;i++)
		{
			if (ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
			}
		}
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
	}
	do
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
		if(slendy.presence!=0)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		for (i=0;i<nbr_ennemies;i=i+3)
		{
			if (ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
			}
		}
		if (cible==1 || cible==4)
		{
			SDL_BlitSurface(attack1_img,NULL,screen,&pos);
		}
		for (i=1;i<nbr_ennemies;i=i+3)
		{
			if (ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
			}
		}
		if (cible==2 || cible==5)
		{
			pos.y=pos.y+20;	
			SDL_BlitSurface(attack1_img,NULL,screen,&pos);
		}
		for (i=2;i<nbr_ennemies;i=i+3)
		{
			if (ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
			}
		}
		if (cible==3 || cible==6)
		{
			pos.y=pos.y+35;
			SDL_BlitSurface(attack1_img,NULL,screen,&pos);
		}
		if (pos.x>=ennemy[cible-1].pos.x && pos.x<=ennemy[cible-1].pos.x+100)
		{
			arrive=1;
			blood2_animation (back ,screen,pos_map,nbr_ennemies,cible,raiden,slendy,ennemy);// effet de sang lorsque l'attaque atteint la cible
		}
		pos.x=pos.x+100;
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
		SDL_Delay(30);
	}
	while(arrive==0);
	SDL_FreeSurface(attack1_img);
}



















void attack3(SDL_Surface *back, SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies,hero raiden, hero slendy,perso ennemy[nbr_ennemies])
{
	Mix_PlayChannel(-1,raiden.sound[2],0);
	SDL_Surface *attack3_img=NULL;
	int j,i,arrive=0;
	SDL_Rect pos;

	//position initiale de l'orbe
	pos.x=300;
	pos.y=50;
	attack3_img=SDL_DisplayFormatAlpha(IMG_Load("attaque ultime.png")); //chargement de l'image de l'attaque
	SDL_Delay(200);
	for (j=0;j<4;j++)
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		SDL_BlitSurface(raiden.img[j],NULL,screen,&raiden.pos);
		if(slendy.presence!=0)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		for (i=0;i<nbr_ennemies;i++)
		{
			if (ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
			}
		}
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
	}
	do
	{
		affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
		SDL_BlitSurface(attack3_img,NULL,screen,&pos);
		if (pos.x>=ennemy[0].pos.x && pos.x<=ennemy[0].pos.x+100)
		{
			arrive=1;
			blood3_animation (back ,screen,pos_map,nbr_ennemies,raiden,slendy,ennemy);//effet de sang de l'attaque 
		}
		pos.x=pos.x+100;
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
		SDL_Delay(30);
	}
	while(arrive==0);
	SDL_FreeSurface(attack3_img);
}











void attack1_slendy(SDL_Surface *back, SDL_Surface *screen, SDL_Rect pos_map,int cible, int nbr_ennemies,hero raiden, hero slendy,perso ennemy[nbr_ennemies])
{
	Mix_PlayChannel(-1,slendy.sound[0],0); //son de l'attaque
	SDL_Surface *attack1_img=NULL;
	int j,i,arrive=0;
	SDL_Rect pos;

	//position initiale du laser
	pos.x=310;
	pos.y=140;
	attack1_img=SDL_DisplayFormatAlpha(IMG_Load("laser.png")); //chargement de l'image de l'attaque
	SDL_Delay(100);
	do
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		if(raiden.presence!=0)
		{
			SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
		}
		SDL_BlitSurface(slendy.img[1],NULL,screen,&slendy.pos);
		for (i=0;i<nbr_ennemies;i=i+3)
		{
			if (ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
			}
		}
		if (cible==1 || cible==4)
		{
			pos.y=pos.y-10;
			SDL_BlitSurface(attack1_img,NULL,screen,&pos);
		}
		for (i=1;i<nbr_ennemies;i=i+3)
		{
			if (ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
			}
		}
		if (cible==2 || cible==5)
		{
			pos.y=pos.y-5;
			SDL_BlitSurface(attack1_img,NULL,screen,&pos);
		}
		for (i=2;i<nbr_ennemies;i=i+3)
		{
			if (ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
			}
		}
		if (cible==3 || cible==6)
		{
			pos.y=pos.y+5;
			SDL_BlitSurface(attack1_img,NULL,screen,&pos);
		}
		if (pos.x>=ennemy[cible-1].pos.x && pos.x<=ennemy[cible-1].pos.x+100)
		{
			arrive=1;
			blood2_animation (back ,screen,pos_map,nbr_ennemies,cible,raiden,slendy,ennemy);// effet de sang lorsque l'attaque atteint la cible
		}
		pos.x=pos.x+50;
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
	}
	while(arrive==0);
	SDL_FreeSurface(attack1_img);
}








void attack2_slendy(SDL_Surface *back, SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies,hero raiden, hero slendy,perso ennemy[nbr_ennemies])
{
	Mix_PlayChannel(-1,slendy.sound[1],0);
	SDL_Surface *attack3_img=NULL;
	int j,i,arrive=0;
	SDL_Rect pos;

	//position initiale de l'orbe
	pos.x=300;
	pos.y=50;
	attack3_img=SDL_DisplayFormatAlpha(IMG_Load("ultime.png")); //chargement de l'image de l'attaque
	SDL_Delay(200);
	do
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		if(raiden.presence!=0)
		{
			SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
		}
		SDL_BlitSurface(slendy.img[2],NULL,screen,&slendy.pos);
		for (i=0;i<nbr_ennemies;i++)
		{
			if (ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
			}
		}
		SDL_BlitSurface(attack3_img,NULL,screen,&pos);
		if (pos.x>=ennemy[0].pos.x && pos.x<=ennemy[0].pos.x+100)
		{
			arrive=1;
			blood3_animation (back ,screen,pos_map,nbr_ennemies,raiden,slendy,ennemy);//effet de sang de l'attaque 
		}
		pos.x=pos.x+100;
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
		SDL_Delay(30);
	}
	while(arrive==0);
	SDL_FreeSurface(attack3_img);
}

void attack3_slendy(SDL_Surface *back, SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies,hero raiden, hero slendy,perso ennemy[nbr_ennemies])
{
	int i;
	Mix_PlayChannel(-1,slendy.sound[2],0);
	SDL_BlitSurface(back,&pos_map,screen,NULL);
	if(raiden.presence!=0)
	{
		SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
	}
	SDL_BlitSurface(slendy.img[3],NULL,screen,&slendy.pos);
	for (i=0;i<nbr_ennemies;i++)
	{
		if (ennemy[i].type!=0)
		{
			SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
		}
	}
	barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
	SDL_Flip(screen);
	SDL_Delay(1000);
}

















void selection(SDL_Surface *back, SDL_Surface *screen, SDL_Rect pos_map, int cible,int nbr_ennemies,perso ennemy[nbr_ennemies], hero raiden, hero slendy)
{
	int i;
	SDL_BlitSurface(back,&pos_map,screen,NULL);
	if (raiden.presence!=0)
	{
		SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
	}
	if(slendy.presence!=0)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
	//affichage d'une nouvelle image a la place de la cible pour montrer qu'elle est ciblée
	for (i=0;i<nbr_ennemies;i++)
		{	
			if (i==cible-1 && ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[0],NULL,screen,&ennemy[i].pos);
			}
			else if (i!=cible-1 && ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
			}
		}
}






















void attack_archer(SDL_Surface *screen, SDL_Surface *back, SDL_Rect pos_map, int nbr_ennemies, int j, Mix_Chunk *arrow_sound,hero raiden, hero slendy,perso ennemy[nbr_ennemies], int cible_ennemi)
{
	SDL_Surface *arrow=NULL;
	int i,k;
	SDL_Rect arr;

	arrow=SDL_DisplayFormatAlpha(IMG_Load("fleche1.png")); //chargement de l'image de la flèche
	Mix_PlayChannel(-1,arrow_sound,0); //son flèche
	SDL_Delay(50);
	for (i=2;i<4;i++)
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		if (raiden.presence!=0)
		{
			SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
		}
		if(slendy.presence!=0)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		for (k=0;k<j;k++)
		{
			if (ennemy[k].type!=0)
			{
				SDL_BlitSurface(ennemy[k].img[1],NULL,screen,&ennemy[k].pos);
			}
		}
		SDL_BlitSurface(ennemy[j].img[i],NULL,screen,&ennemy[j].pos);
		for (k=j+1;k<nbr_ennemies;k++)
		{
			if (ennemy[k].type!=0)
			{
				SDL_BlitSurface(ennemy[k].img[1],NULL,screen,&ennemy[k].pos);
			}
		}
		if (i==2)
		{
			//position de la flèche
			arr.x=ennemy[j].pos.x;
			arr.y=150+ennemy[j].pos.y;
			do
			{
				SDL_BlitSurface(back,&pos_map,screen,NULL);
				SDL_BlitSurface(arrow,NULL,screen,&arr);
				if (raiden.presence!=0)
				{
					SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
				}
				if(slendy.presence!=0)
				{
					SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
				}
				for (k=0;k<j;k++)
				{
					if (ennemy[k].type!=0)
					{
						SDL_BlitSurface(ennemy[k].img[1],NULL,screen,&ennemy[k].pos);
					}
				}
				SDL_BlitSurface(ennemy[j].img[i],NULL,screen,&ennemy[j].pos);
				for (k=j+1;k<nbr_ennemies;k++)
				{
					if (ennemy[k].type!=0)
					{
						SDL_BlitSurface(ennemy[k].img[1],NULL,screen,&ennemy[k].pos);
					}
				}
				arr.x=arr.x-200;
				arr.y=arr.y+10;
				if (cible_ennemi==2)
				{
					arr.y=arr.y+40;
				}
				barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
				SDL_Flip(screen);
			}
			while (arr.x>-50);
			blood1_animation(back ,screen,pos_map,nbr_ennemies,j,raiden,slendy,ennemy,cible_ennemi);
		}
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
	}
	affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
	barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
	SDL_Flip(screen);
}













void attack_warrior(SDL_Surface *screen, SDL_Surface *back, SDL_Rect pos_map, int nbr_ennemies, int j,  Mix_Chunk *warrior_sound,hero raiden, hero slendy,perso ennemy[nbr_ennemies],int cible_ennemi)
{
	int i,k;
	SDL_Rect pos_warrior;

	//position initiale du guerrier
	pos_warrior.x=ennemy[j].pos.x;
	pos_warrior.y=ennemy[j].pos.y;
	Mix_PlayChannel(-1,warrior_sound,0); //son attaque
	for (i=2;i<9;i++)
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		if (raiden.presence!=0)
		{
			SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
		}
		if(slendy.presence!=0 && cible_ennemi==2)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		for (k=0;k<j;k++)
		{
			if (ennemy[k].type!=0)
			{
				SDL_BlitSurface(ennemy[k].img[1],NULL,screen,&ennemy[k].pos);
			}
		}
		if (i==3)
		{
			if (cible_ennemi==1)
			{
				pos_warrior.x=raiden.pos.x+200;
				pos_warrior.y=raiden.pos.y;
			}	
			else if (cible_ennemi==2)
			{
				pos_warrior.x=slendy.pos.x+200;
				pos_warrior.y=slendy.pos.y;
			}
		}
		
		SDL_BlitSurface(ennemy[j].img[i],NULL,screen,&pos_warrior);
		if(slendy.presence!=0 && cible_ennemi==1)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		for (k=j+1;k<nbr_ennemies;k++)
		{
			if (ennemy[k].type!=0)
			{
				SDL_BlitSurface(ennemy[k].img[1],NULL,screen,&ennemy[k].pos);
			}
		}
		if (i==8)
		{
			blood4_animation (back ,screen,pos_warrior,pos_map,nbr_ennemies,  j,raiden,slendy,ennemy,cible_ennemi);
		}
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
		SDL_Delay(60);
		if (i==5)
		{
			SDL_Delay(70);
		}
	}
	for (i=2;i<6;i++)
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		if (raiden.presence!=0)
		{
			SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
		}
		if(slendy.presence!=0)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		for (k=0;k<j;k++)
		{
			if (ennemy[k].type!=0)
			{
				SDL_BlitSurface(ennemy[k].img[1],NULL,screen,&ennemy[k].pos);
			}
		}
		if (i==3)
		{
			pos_warrior.x=ennemy[j].pos.x;
			pos_warrior.y=ennemy[j].pos.y;
		}
		if (i==5)
		{
			SDL_BlitSurface(ennemy[j].img[1],NULL,screen,&pos_warrior);
		}
		else 
			{
				SDL_BlitSurface(ennemy[j].img[i],NULL,screen,&pos_warrior);
			}
		for (k=j+1;k<nbr_ennemies;k++)
		{
			if (ennemy[k].type!=0)
			{
				SDL_BlitSurface(ennemy[k].img[1],NULL,screen,&ennemy[k].pos);
			}
		}
 		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
		SDL_Delay(60);
	}
	SDL_Delay(200);
}



























void death_animation(SDL_Surface *back ,SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies, int cible, Mix_Chunk *blood_explosion,hero raiden, hero slendy,perso ennemy[nbr_ennemies])
{
	Mix_PlayChannel(-1,blood_explosion,0);
	SDL_Surface *blood[6]={NULL};
	int i,j;

	//chargement des images illustrant l'animation du sang
	blood[0]=SDL_DisplayFormatAlpha(IMG_Load("blood_d_0001.png"));
	blood[1]=SDL_DisplayFormatAlpha(IMG_Load("blood_d_0002.png"));
	blood[2]=SDL_DisplayFormatAlpha(IMG_Load("blood_d_0003.png"));
	blood[3]=SDL_DisplayFormatAlpha(IMG_Load("blood_d_0004.png"));
	blood[4]=SDL_DisplayFormatAlpha(IMG_Load("blood_d_0005.png"));
	blood[5]=SDL_DisplayFormatAlpha(IMG_Load("blood_d_0006.png"));
	ennemy[cible-1].type=0; //changement de l'état de l'ennemi à "mort"
	SDL_Delay(50);
	for (i=0;i<6;i++)
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		if (raiden.presence!=0)
		{
			SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
		}
		if(slendy.presence!=0)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		for (j=0;j<cible-1;j++)
		{
			if (ennemy[j].type!=0)
			{
				SDL_BlitSurface(ennemy[j].img[1],NULL,screen,&ennemy[j].pos);
			}
		}
		SDL_BlitSurface(blood[i],NULL,screen,&ennemy[cible-1].pos);
		for (j=cible;j<nbr_ennemies;j++)
		{
			if (ennemy[j].type!=0)
			{
				SDL_BlitSurface(ennemy[j].img[1],NULL,screen,&ennemy[j].pos);
			}
		}
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Delay(30);
		SDL_Flip(screen);
	}
	for (i=0;i<6;i++)
	{
		SDL_FreeSurface(blood[i]);
	}
	affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
	barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
	SDL_Flip(screen);
}





















void blood1_animation(SDL_Surface *back ,SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies, int attaquant,hero raiden, hero slendy,perso ennemy[nbr_ennemies], int cible_ennemi)
{
	SDL_Surface *blood[6]={NULL};
	int i,j;
	SDL_Rect pos_blood;

	//chargement des images de l'animation du sang
	blood[0]=SDL_DisplayFormatAlpha(IMG_Load("blood_b_0001.png"));
	blood[1]=SDL_DisplayFormatAlpha(IMG_Load("blood_b_0002.png"));
	blood[2]=SDL_DisplayFormatAlpha(IMG_Load("blood_b_0003.png"));
	blood[3]=SDL_DisplayFormatAlpha(IMG_Load("blood_b_0004.png"));
	blood[4]=SDL_DisplayFormatAlpha(IMG_Load("blood_b_0005.png"));
	blood[5]=SDL_DisplayFormatAlpha(IMG_Load("blood_b_0006.png"));
	pos_blood.x=slendy.pos.x+150;
	pos_blood.y=ennemy[attaquant].pos.y+125;
	 if (cible_ennemi==2)
	{
		pos_blood.y=ennemy[attaquant].pos.y+300;
	}
	for (i=0;i<6;i++)
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		if (raiden.presence!=0)
		{
			SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
		}
		if(slendy.presence!=0 && cible_ennemi==2)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		for (j=0;j<nbr_ennemies;j++)
		{
			if (ennemy[j].type!=0)
			{
				if (j==attaquant)
				{
					SDL_BlitSurface(ennemy[j].img[2],NULL,screen,&ennemy[j].pos);
				}
				else 
				{
					SDL_BlitSurface(ennemy[j].img[1],NULL,screen,&ennemy[j].pos);
				}
			}
		}
		SDL_BlitSurface(blood[i],NULL,screen,&pos_blood);
		if(slendy.presence!=0 && cible_ennemi==1)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
	}
	for (i=0;i<6;i++)
	{
		SDL_FreeSurface(blood[i]);
	}
	
}















void death_animationhero(SDL_Surface *back ,SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies, Mix_Chunk *blood_explosion,hero raiden, hero slendy,perso ennemy[nbr_ennemies])
{
	Mix_PlayChannel(-1,blood_explosion,0);
	SDL_Surface *blood[6]={NULL};

	int i,j;
	blood[0]=SDL_DisplayFormatAlpha(IMG_Load("blood_c_0001.png"));
	blood[1]=SDL_DisplayFormatAlpha(IMG_Load("blood_c_0002.png"));
	blood[2]=SDL_DisplayFormatAlpha(IMG_Load("blood_c_0003.png"));
	blood[3]=SDL_DisplayFormatAlpha(IMG_Load("blood_c_0004.png"));
	blood[4]=SDL_DisplayFormatAlpha(IMG_Load("blood_c_0005.png"));
	blood[5]=SDL_DisplayFormatAlpha(IMG_Load("blood_c_0006.png"));
	for (j=0;j<6;j++)
	{
		if (raiden.life<=0 && raiden.presence!=0)
		{
			SDL_BlitSurface(back,&pos_map,screen,NULL);
			SDL_BlitSurface(blood[j],NULL,screen,&raiden.pos);
			if (slendy.presence!=0)
			{
				SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
			}
		}
		else if (slendy.life<=0 && slendy.presence!=0)
		{
			SDL_BlitSurface(back,&pos_map,screen,NULL);
			if (raiden.presence!=0)
			{
				SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
			}
			SDL_BlitSurface(blood[j],NULL,screen,&slendy.pos);
		}
		for (i=0;i<nbr_ennemies;i++)
		{
			if (ennemy[i].type!=0)
			{
				SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
			}
		}
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
		SDL_Delay(30);
	}
	barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
	SDL_Flip(screen);
	for (i=0;i<6;i++)
	{
		SDL_FreeSurface(blood[i]);
	}
}

















void blood2_animation (SDL_Surface *back ,SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies, int cible,hero raiden, hero slendy,perso ennemy[nbr_ennemies])
{
	SDL_Surface *blood[6]={NULL};

	int i,j;
	blood[0]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0001.png"));
	blood[1]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0002.png"));
	blood[2]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0003.png"));
	blood[3]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0004.png"));
	blood[4]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0005.png"));
	blood[5]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0006.png"));
	SDL_Rect pos_blood;
	pos_blood.x=ennemy[cible-1].pos.x+75;
	pos_blood.y=ennemy[cible-1].pos.y+100;
	for (i=0;i<6;i++)
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		if (raiden.presence!=0)
		{
			SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
		}
		if(slendy.presence!=0)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		for (j=0;j<=cible-1;j++)
		{
			if (ennemy[j].type!=0)
			{
				SDL_BlitSurface(ennemy[j].img[1],NULL,screen,&ennemy[j].pos);
			}
		}
		SDL_BlitSurface(blood[i],NULL,screen,&pos_blood);
		for (j=cible;j<nbr_ennemies;j++)
		{
			if (ennemy[j].type!=0)
			{
				SDL_BlitSurface(ennemy[j].img[1],NULL,screen,&ennemy[j].pos);
			}
		}
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
	}
	affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
	barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
	SDL_Flip(screen);
	for (i=0;i<6;i++)
	{
		SDL_FreeSurface(blood[i]);
	}
}










void blood3_animation(SDL_Surface *back ,SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies,hero raiden, hero slendy,perso ennemy[nbr_ennemies])
{
	SDL_Surface *blood[6]={NULL};

	int i,j;
	blood[0]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0001.png"));
	blood[1]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0002.png"));
	blood[2]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0003.png"));
	blood[3]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0004.png"));
	blood[4]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0005.png"));
	blood[5]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0006.png"));
	SDL_Rect pos_blood;
	for (i=0;i<6;i++)
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		if (raiden.presence!=0)
		{
			SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
		}
		if(slendy.presence!=0)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		for (j=0;j<nbr_ennemies;j++)
		{
			if (ennemy[j].type!=0)
			{
				pos_blood.x=ennemy[j].pos.x+75;
				pos_blood.y=ennemy[j].pos.y+100;
				SDL_BlitSurface(ennemy[j].img[1],NULL,screen,&ennemy[j].pos);
				SDL_BlitSurface(blood[i],NULL,screen,&pos_blood);
			}
		}
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
	}
	affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
	barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
	SDL_Flip(screen);
	for (i=0;i<6;i++)
	{
		SDL_FreeSurface(blood[i]);
	}
}






void blood4_animation (SDL_Surface *back ,SDL_Surface *screen, SDL_Rect pos_warrior, SDL_Rect pos_map, int nbr_ennemies, int attaquant,hero raiden, hero slendy,perso ennemy[nbr_ennemies],int cible_ennemi)
{
	SDL_Surface *blood[6]={NULL};

	int i,j;
	blood[0]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0001.png"));
	blood[1]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0002.png"));
	blood[2]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0003.png"));
	blood[3]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0004.png"));
	blood[4]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0005.png"));
	blood[5]=SDL_DisplayFormatAlpha(IMG_Load("blood_a_0006.png"));
	SDL_Rect pos_blood;
	if (cible_ennemi==1)
	{
		pos_blood.x=100;
		pos_blood.y=150;
	}
	else if (cible_ennemi==2)
	{
		pos_blood.x=90;
		pos_blood.y=300;
	}
	for (i=0;i<6;i++)
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		if (raiden.presence!=0)
		{
			SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
		}
		if(slendy.presence!=0)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		for (j=0;j<nbr_ennemies;j++)
		{
			if (j!=attaquant && ennemy[j].type!=0)
			{
				SDL_BlitSurface(ennemy[j].img[1],NULL,screen,&ennemy[j].pos);
			}
		}
		SDL_BlitSurface(ennemy[attaquant].img[8],NULL,screen,&pos_warrior);
		SDL_BlitSurface(blood[i],NULL,screen,&pos_blood);
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
	}
	for (i=0;i<6;i++)
	{
		SDL_FreeSurface(blood[i]);
	}
}




void barre_bliting(SDL_Surface *screen, int nbr_ennemies,hero raiden, hero slendy,perso ennemy[nbr_ennemies])
{
	int i,x1=1135,x2=875,y1=7,y2=32,y3=57;
	char jomla[9],jomla1[9];
	TTF_Font *police;
	SDL_Surface *carac=NULL;
	SDL_Color blanc={255,255,255};
	SDL_Rect pos[2], pos1[6];

	//initialisation des positions des barres
	pos[0].x=160;
	pos[0].y=30;
	pos[1].x=175;
	pos[1].y=44;
	pos1[0].x=x1;
	pos1[0].y=y1;
	pos1[1].x=x1;
	pos1[1].y=y2;
	pos1[2].x=x1;
	pos1[2].y=y3;
	pos1[3].x=x2;
	pos1[3].y=y1;
	pos1[4].x=x2;
	pos1[4].y=y2;
	pos1[5].x=x2;
	pos1[5].y=y3;

	police=TTF_OpenFont("GenBasB.ttf",13);
	if (raiden.presence!=0)
	{
		sprintf(jomla,"%d",raiden.life);
		sprintf(jomla1,"%d",raiden.life_max);
		strcat(jomla,"/");
		strcat(jomla,jomla1);
		carac=SDL_DisplayFormatAlpha(TTF_RenderText_Blended(police,jomla,blanc));
		SDL_BlitSurface(raiden.barre[0],NULL,screen,NULL);//affichage de la barre vide
		SDL_BlitSurface(raiden.barre[1],&raiden.posbar[0],screen,NULL);//affichage de la barre de vie
		SDL_BlitSurface(carac,NULL,screen,&pos[0]); //affichage de la vie en numéros sur la barre
		sprintf(jomla,"%d",raiden.mana);
		sprintf(jomla1,"%d",raiden.mana_max);
		strcat(jomla,"/");
		strcat(jomla,jomla1);
		carac=SDL_DisplayFormatAlpha(TTF_RenderText_Blended(police,jomla,blanc));
		SDL_BlitSurface(raiden.barre[2],&raiden.posbar[1],screen,NULL);//affichage de la barre de mana
		SDL_BlitSurface(carac,NULL,screen,&pos[1]);//affichage de la mana en numéros sur la barre
	}

	if (slendy.presence!=0)
	{
		pos[0].x=pos[0].x+350;
		pos[1].x=pos[1].x+350;
		sprintf(jomla,"%d",slendy.life);
		sprintf(jomla1,"%d",slendy.life_max);
		strcat(jomla,"/");
		strcat(jomla,jomla1);
		carac=SDL_DisplayFormatAlpha(TTF_RenderText_Blended(police,jomla,blanc));
		SDL_BlitSurface(slendy.barre[0],NULL,screen,NULL);//affichage de la barre vide
		SDL_BlitSurface(slendy.barre[1],&slendy.posbar[0],screen,NULL);//affichage de la barre de vie
		SDL_BlitSurface(carac,NULL,screen,&pos[0]); //affichage de la vie en numéros sur la barre
		sprintf(jomla,"%d",slendy.mana);
		sprintf(jomla1,"%d",slendy.mana_max);
		strcat(jomla,"/");
		strcat(jomla,jomla1);
		carac=SDL_DisplayFormatAlpha(TTF_RenderText_Blended(police,jomla,blanc));
		SDL_BlitSurface(slendy.barre[2],&slendy.posbar[1],screen,NULL);//affichage de la barre de mana
		SDL_BlitSurface(carac,NULL,screen,&pos[1]);//affichage de la mana en numéros sur la barre
	}

	//même suivi pour les barres des ennemies
	for (i=0;i<nbr_ennemies;i++)
	{
		if (ennemy[i].type==1 || ennemy[i].type==2 || ennemy[i].type==3)
		{
			SDL_BlitSurface(ennemy[i].barre[0],NULL,screen,NULL);
			SDL_BlitSurface(ennemy[i].barre[1],&ennemy[i].posbar,screen,NULL);
			sprintf(jomla,"%d",ennemy[i].life);
			sprintf(jomla1,"%d",ennemy[i].life_max);
			strcat(jomla,"/");
			strcat(jomla,jomla1);
			carac=SDL_DisplayFormatAlpha(TTF_RenderText_Blended(police,jomla,blanc));
			SDL_BlitSurface(carac,NULL,screen,&pos1[i]);
		}
	}
	SDL_Flip(screen);
	TTF_CloseFont(police);
	SDL_FreeSurface(carac);
}





void barre_init(int nbr_ennemies,perso ennemy[nbr_ennemies],hero *raiden, hero *slendy)
{
	int i;
	//initialisation des barres des ennemies (position,largeur et longueur)
	for (i=0;i<nbr_ennemies;i++)
	{
		ennemy[i].posbar.x=0;
		ennemy[i].posbar.y=0;
		ennemy[i].posbar.w=1280;
		ennemy[i].posbar.h=768;

	}
	
	//initialisation des barres de raiden et slendy (position,largeur et longueur)
	for (i=0;i<2;i++)
	{
		slendy->posbar[i].x=0;
		slendy->posbar[i].y=0;
		slendy->posbar[i].w=1280;
		slendy->posbar[i].h=768;
		raiden->posbar[i].x=0;
		raiden->posbar[i].y=0;
		raiden->posbar[i].w=1280;
		raiden->posbar[i].h=768;
		if (i==1)
		{
			raiden->posbar[i].w=0;
		}
	}
}
void affich_degat(SDL_Surface *screen, SDL_Surface *degat, int dps, SDL_Rect pos, TTF_Font *police)
{
	SDL_Color rouge={255,0,0};
	char c[10];
	sprintf(c,"%d",dps);
	degat=SDL_DisplayFormatAlpha(TTF_RenderText_Blended(police,c,rouge));
	pos.x=pos.x+100;
	pos.y=pos.y+100;
	SDL_BlitSurface(degat,NULL,screen,&pos); //affiche la valeur des dégâts
	SDL_Flip(screen);
	SDL_Delay(200);
}

void affich_heal(SDL_Surface *screen, SDL_Surface *degat, int dps, SDL_Rect pos, TTF_Font *police)
{
	SDL_Color rouge={0,255,0};
	char c[10];
	sprintf(c,"%d",dps);
	degat=SDL_DisplayFormatAlpha(TTF_RenderText_Blended(police,c,rouge));
	pos.x=pos.x+100;
	pos.y=pos.y+100;
	SDL_BlitSurface(degat,NULL,screen,&pos); //affiche la valeur des dégâts
	SDL_Flip(screen);
	SDL_Delay(200);
}


void affiche_personnnages(SDL_Surface *back, SDL_Surface *screen, hero raiden, hero slendy, int nbr_ennemies,perso ennemy[nbr_ennemies], SDL_Rect pos_map)
{
	int i;
	SDL_BlitSurface(back,&pos_map,screen,NULL); //affichage de l'arrière plan
	if (raiden.presence!=0)
	{
		SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos); // affichage de l'image de Raiden
	}
	if (slendy.presence!=0)
	{
		SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
	}

	//affichage des ennemies
	for (i=0;i<nbr_ennemies;i++)
	{	
		if (ennemy[i].type!=0)
		{
			SDL_BlitSurface(ennemy[i].img[1],NULL,screen,&ennemy[i].pos);
		}
	}
}

void affiche_msg(SDL_Surface *screen,TTF_Font *police)
{
	SDL_Color bleu={0,0,255};
	SDL_Surface *msg;
	SDL_Rect pos;
	msg=SDL_DisplayFormatAlpha(TTF_RenderText_Blended(police,"No Mana",bleu));
	pos.x=300;
	pos.y=500;
	SDL_BlitSurface(msg,NULL,screen,&pos); //affiche la valeur des dégâts
	SDL_Flip(screen);
	SDL_FreeSurface(msg);
}








void attack_boss(SDL_Surface *screen, SDL_Surface *back, SDL_Rect pos_map, int nbr_ennemies, int j,hero raiden, hero slendy,perso ennemy[nbr_ennemies], int cible_ennemi, int attackealancer,int lvl)
{
	int i;
	SDL_Surface *arrow=NULL;
	SDL_Rect arr;
	if (attackealancer==2)
	{
		arrow=ennemy[0].img[5]; //chargement de l'image de la flèche
	}
	else
	{
		arrow=ennemy[0].img[4];
	}
	SDL_BlitSurface(back,&pos_map,screen,NULL);
	if (raiden.presence!=0)
	{
		SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
	}
	if(slendy.presence!=0)
	{
		SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
	}
	SDL_BlitSurface(ennemy[0].img[2],NULL,screen,&ennemy[0].pos);
	barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
	SDL_Flip(screen);
	SDL_Delay(500);
	arr.x=ennemy[j].pos.x;
	arr.y=200+ennemy[j].pos.y;
	if (lvl==5)
	{
		arr.x=arr.x-100;
		arr.y=arr.y-125;
	}
	do
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		SDL_BlitSurface(arrow,NULL,screen,&arr);
		if (raiden.presence!=0)
		{
			SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
		}
		if(slendy.presence!=0)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		SDL_BlitSurface(ennemy[j].img[2],NULL,screen,&ennemy[j].pos);
		arr.x=arr.x-100	 ;
		if (cible_ennemi==2)
		{
			arr.y=arr.y+15;
		}
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		SDL_Flip(screen);
	}
	while (arr.x>50);
	blood1_animation(back ,screen,pos_map,nbr_ennemies,j,raiden,slendy,ennemy,cible_ennemi);
	barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
	SDL_Flip(screen);
	affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
	barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
	SDL_Flip(screen);
}












void attack_boss5_ulti(SDL_Surface *screen, SDL_Surface *back, SDL_Rect pos_map, int nbr_ennemies, int j,hero raiden, hero slendy,perso ennemy[nbr_ennemies])
{
	int i=0;
	SDL_Rect arr;
	SDL_BlitSurface(back,&pos_map,screen,NULL);
	if (raiden.presence!=0)
	{
		SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
	}
	if(slendy.presence!=0)
	{
		SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
	}
	SDL_BlitSurface(ennemy[0].img[3],NULL,screen,&ennemy[0].pos);
	barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
	SDL_Flip(screen);
	arr.x=ennemy[j].pos.x-180;
	arr.y=0;
	do
	{
		SDL_BlitSurface(back,&pos_map,screen,NULL);
		if (raiden.presence!=0)
		{
			SDL_BlitSurface(raiden.img[0],NULL,screen,&raiden.pos);
		}
		SDL_BlitSurface(ennemy[0].img[5],NULL,screen,&arr);
		if(slendy.presence!=0)
		{
			SDL_BlitSurface(slendy.img[0],NULL,screen,&slendy.pos);
		}
		SDL_BlitSurface(ennemy[j].img[3],NULL,screen,&ennemy[j].pos);
		arr.x=arr.x-50;
		arr.y=arr.y+20;
		barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
		if (i==0)
		{
			SDL_Delay(1150);
			i++;
		}
		SDL_Flip(screen);
	}
	while (arr.x>-50);
	blood1_animation(back ,screen,pos_map,nbr_ennemies,j,raiden,slendy,ennemy,1);
	blood1_animation(back ,screen,pos_map,nbr_ennemies,j,raiden,slendy,ennemy,2);
	barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
	SDL_Flip(screen);
	affiche_personnnages(back,screen,raiden,slendy,nbr_ennemies,ennemy,pos_map);
	barre_bliting(screen,nbr_ennemies,raiden,slendy,ennemy);
	SDL_Flip(screen);
}