#include "var.h"



hero Init_raiden(int lvl)
{
	hero carac;
	carac.life=6000+1000*(lvl); //niveau de vie
	carac.life_max=carac.life; //niveau max de vie
	carac.attack1=500+110*(lvl); //dégât de l'attauqe 1
	carac.attack2=2000+400*(lvl); //dégât de l'attaque 2
	carac.attack3=1300+110*(lvl); //dégât de l'attaque 3
	carac.mana=0;//niveau de mana
	carac.mana_max=10;//niveau de mana max
	carac.pos.x=0;//position
	carac.pos.y=0;//position
	carac.img[0]=SDL_DisplayFormatAlpha(IMG_Load("pose combat_raiden.png")); //image de la pose de combat de raiden(posture par défault)
	carac.img[1]=SDL_DisplayFormatAlpha(IMG_Load("attaque 1 (0).png")); //mouvement 1 pendant une attaque
	carac.img[2]=SDL_DisplayFormatAlpha(IMG_Load("attaque 1 (1).png")); //mouvement 2 pendant une attaque
	carac.img[3]=SDL_DisplayFormatAlpha(IMG_Load("attaque 1(2) .png")); //mouvement 3 pendant une attaque
	carac.sorts=SDL_DisplayFormatAlpha(IMG_Load("sorts.png")); //image de la barre de sort
	carac.rapport[0]=(float)211/carac.life; // 211= pixels de la barre de vie, cette équation permet de donner une barre correcte qui dépend du niveau de vie
	carac.rapport[1]=(float)211/carac.mana_max; //même chose que la barre de vie
	carac.barre[0]=SDL_DisplayFormatAlpha(IMG_Load("barre raiden vide.png")); //barre vide
	carac.barre[1]=SDL_DisplayFormatAlpha(IMG_Load("vie raiden.png")); //barre de vie
	carac.barre[2]=SDL_DisplayFormatAlpha(IMG_Load("mana raiden.png"));//barre de mana
	carac.sound[0]=Mix_LoadWAV("attack1 raiden.ogg"); //son attaque 1
	carac.sound[1]=Mix_LoadWAV("attack2 raiden.ogg");//son attaque 2
	carac.sound[2]=Mix_LoadWAV("attaque ultime raiden.ogg"); //son attaque 3
	if (lvl==2)
	{
		carac.presence=0;
	}
	else
	{
		carac.presence=1;
	}
	return carac;
}
hero Init_slendy(int lvl)
{
	hero carac;
	carac.life=5500+750*(lvl); //niveau de vie
	carac.life_max=carac.life; //niveau max de vie
	carac.attack1=1200+110*(lvl); //dégât de l'attauqe 1
	carac.attack2=(900+110*(lvl)); //dégât de l'attauqe 2
	carac.attack3=(2700+400*(lvl)); //dégât de l'attauqe 3
	carac.mana=40;//niveau de mana
	carac.mana_max=40;//niveau de mana max
	carac.pos.x=0;//position
	carac.pos.y=150;//position
	carac.img[0]=SDL_DisplayFormatAlpha(IMG_Load("mode_cbt.png"));//image de la pose de combat de slendy(posture par défault)
	carac.img[1]=SDL_DisplayFormatAlpha(IMG_Load("attack1.png")); //mouvement 1 pendant une attaque
	carac.img[2]=SDL_DisplayFormatAlpha(IMG_Load("attack2.png")); //mouvement 2 pendant une attaque
	carac.img[3]=SDL_DisplayFormatAlpha(IMG_Load("attack3.png")); //mouvement 3 pendant une attaque
	carac.barre[0]=SDL_DisplayFormatAlpha(IMG_Load("barre vide slendy.png")); //barre vide
	carac.barre[1]=SDL_DisplayFormatAlpha(IMG_Load("vie slendy.png")); //barre de vie
	carac.barre[2]=SDL_DisplayFormatAlpha(IMG_Load("mana slendy.png"));//barre de mana
	carac.rapport[0]=(float)211/carac.life; // 211= pixels de la barre de vie, cette équation permet de donner une barre correcte qui dépend du niveau de vie
	carac.rapport[1]=(float)211/carac.mana_max; //même chose que la barre de vie
	carac.sound[0]=Mix_LoadWAV("attack1_slendy.ogg"); //son attaque 1
	carac.sound[1]=Mix_LoadWAV("attack2_slendy.ogg");//son attaque 2
	carac.sound[2]=Mix_LoadWAV("attack3_slendy.ogg"); //son attaque 3
	carac.sorts=SDL_DisplayFormatAlpha(IMG_Load("barre sorts slendy.png"));
	if (lvl==1)
	{
		carac.presence=0;
	}
	else
	{
		carac.presence=1;
	}
	return carac;
}


perso Init_archer(int lvl, SDL_Surface *archer_img[4], SDL_Surface *barre, SDL_Surface *vie, SDL_Rect slot)
{
	int i;
	perso carac;
	carac.life=2000+(250*(lvl)); //niveau de vie de l'archer
	carac.life_max=carac.life; //niveau de vie max de l'archer
	carac.attaque=(300+110*(lvl))*2 ; //dégât de l'attaque de l'archer
	carac.type=1; //type de l'ennemi, 0=mort, 1=archer, 2=guerrier
	for (i=1;i<4;i++)
	{
		carac.img[i]=archer_img[i-1]; //images animation attaque
	}
	carac.img[0]=archer_img[3]; //affichée quand cet individu est ciblé
	carac.rapport=(float)203/carac.life;
	carac.pos=slot; //position
	carac.barre[0]=barre; //barre vide
	carac.barre[1]=vie; //barre de vie
	return carac;
}
perso Init_war(int lvl, SDL_Surface *war_img[9], SDL_Surface *barre, SDL_Surface *vie,SDL_Rect slot)
{
	int i;
	perso carac;
	carac.life=3500+(400*(lvl));
	carac.life_max=carac.life;
	carac.attaque=300+110*(lvl);
	carac.type=2;
	for (i=1;i<9;i++)
	{
		carac.img[i]=war_img[i-1];
	}
	carac.img[0]=war_img[8];
	carac.rapport=(float)203/carac.life;
	carac.pos=slot;
	carac.pos.x=carac.pos.x-50;
	carac.barre[0]=barre;
	carac.barre[1]=vie;
	return carac;
}


perso Init_boss_lvl4(int lvl, SDL_Surface *barre, SDL_Surface *vie,SDL_Rect slot)
{
	int i;
	perso carac;
	carac.life=19000;
	carac.life_max=carac.life;
	carac.attaque=4500;
	carac.attaque_ultime=3000;
	carac.type=3;
	carac.img[0]=SDL_DisplayFormatAlpha(IMG_Load("cp select.png"));
	carac.img[1]=SDL_DisplayFormatAlpha(IMG_Load("cp default.png"));
	carac.img[2]=SDL_DisplayFormatAlpha(IMG_Load("cp attack1.png"));
	carac.img[3]=SDL_DisplayFormatAlpha(IMG_Load("cd attack2.png"));
	carac.img[4]=SDL_DisplayFormatAlpha(IMG_Load("attack 1 cp.png"));
	carac.img[5]=SDL_DisplayFormatAlpha(IMG_Load("attack 2  cp.png"));
	carac.rapport=(float)203/carac.life;
	carac.pos=slot;
	carac.barre[0]=barre;
	carac.barre[1]=vie;
	return carac;
}
perso Init_boss_lvl3(int lvl, SDL_Surface *barre, SDL_Surface *vie,SDL_Rect slot)
{
	int i;
	perso carac;
	carac.life=11000;
	carac.life_max=carac.life;
	carac.attaque=1500;
	carac.attaque_ultime=2000;
	carac.type=3;
	carac.img[0]=SDL_DisplayFormatAlpha(IMG_Load("umber select.png"));
	carac.img[1]=SDL_DisplayFormatAlpha(IMG_Load("umber psoture default.png"));
	carac.img[2]=SDL_DisplayFormatAlpha(IMG_Load("umber attack1.png"));
	carac.img[3]=SDL_DisplayFormatAlpha(IMG_Load("umber attack2.png"));
	carac.img[4]=SDL_DisplayFormatAlpha(IMG_Load("umber attack meduse.png"));
	carac.img[5]=SDL_DisplayFormatAlpha(IMG_Load("umber attack feu"));
	carac.rapport=(float)203/carac.life;
	carac.pos=slot;
	carac.barre[0]=barre;
	carac.barre[1]=vie;
	return carac;
}
perso Init_boss_lvl5(int lvl, SDL_Surface *barre, SDL_Surface *vie,SDL_Rect slot)
{
	int i;
	perso carac;
	carac.life=25000;
	carac.life_max=carac.life;
	carac.attaque=5000;
	carac.attaque_ultime=4200;
	carac.type=3;
	carac.img[0]=SDL_DisplayFormatAlpha(IMG_Load("bleack select.png"));
	carac.img[1]=SDL_DisplayFormatAlpha(IMG_Load("bleak posture default.png"));
	carac.img[2]=SDL_DisplayFormatAlpha(IMG_Load("bleak attack1.png"));
	carac.img[3]=SDL_DisplayFormatAlpha(IMG_Load("bleack ulti.png"));
	carac.img[4]=SDL_DisplayFormatAlpha(IMG_Load("bleak boule.png"));
	carac.img[5]=SDL_DisplayFormatAlpha(IMG_Load("bleack boule ulti.png"));
	carac.rapport=(float)203/carac.life;
	carac.pos.x=slot.x-100;
	carac.pos.y=slot.y;
	carac.barre[0]=barre;
	carac.barre[1]=vie;
	return carac;
}
void free_raiden(hero carac)
{
	int i;
	for (i=0;i<3;i++)
	{
		SDL_FreeSurface(carac.barre[i]);
	}
	for (i=0;i<4;i++)
	{
		SDL_FreeSurface(carac.img[i]);
	}
	for (i=0;i<3;i++)
	{
		Mix_FreeChunk(carac.sound[i]);
	}
	SDL_FreeSurface(carac.sorts);
}
void free_slendy(hero carac)
{
	int i;
	for (i=0;i<4;i++)
	{
		SDL_FreeSurface(carac.img[i]);
		if (i!=3)
		{
			SDL_FreeSurface(carac.barre[i]);
		}
	}
	for (i=0;i<3;i++)
	{
		Mix_FreeChunk(carac.sound[i]);
	}
	SDL_FreeSurface(carac.sorts);
}
void free_boss(perso carac)
{
	int i;
	for (i=0;i<6;i++)
	{
		SDL_FreeSurface(carac.img[i]);
	}
}
