#ifndef CBT_H_
#define CBT_H_
#include "var.h"

//fonction de combat
int cbt (int nbr_archer, int nbr_guerrier, SDL_Surface *screen, SDL_Surface *back, SDL_Rect pos_map, int *sound, int *fullscreen, int lvl);

//fonction de combat contre un boss
int cbt_boss (SDL_Surface *screen, SDL_Surface *back, SDL_Rect pos_map, int *sound, int *fullscreen, int lvl);

//animation de l'attaque 1 de Raiden
void attack1(SDL_Surface *back,SDL_Surface *screen,SDL_Rect pos_map,int nbr_ennemies,int cible,hero raiden,hero slendy,perso ennemy[nbr_ennemies]);

//animation de l'attaque 2 de Raiden
void attack2(SDL_Surface *back, SDL_Surface *screen, SDL_Rect pos_map,int cible, int nbr_ennemies,hero raiden, hero slendy,perso ennemy[nbr_ennemies]);

//animation de l'attaque 3 de Raiden
void attack3(SDL_Surface *back, SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies,hero raiden, hero slendy,perso ennemy[nbr_ennemies]);

//animation de l'attaque 1 de slendy
void attack1_slendy(SDL_Surface *back, SDL_Surface *screen, SDL_Rect pos_map,int cible, int nbr_ennemies,hero raiden, hero slendy,perso ennemy[nbr_ennemies]);

//animation de l'attaque 2  de slendy
void attack2_slendy(SDL_Surface *back, SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies,hero raiden, hero slendy,perso ennemy[nbr_ennemies]);

//animation de l'attaque 3 de slendy
void attack3_slendy(SDL_Surface *back, SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies,hero raiden, hero slendy,perso ennemy[nbr_ennemies]);

//fonction de ciblage (choix de la cible)
void selection(SDL_Surface *back, SDL_Surface *screen, SDL_Rect pos_map, int cible,int nbr_ennemies,perso ennemy[nbr_ennemies], hero raiden, hero slendy);

//animation de l'attaque de l'archer
void attack_archer(SDL_Surface *screen, SDL_Surface *back, SDL_Rect pos_map, int nbr_ennemies, int j, Mix_Chunk *arrow_sound,hero raiden, hero slendy,perso ennemy[nbr_ennemies], int cible_ennemi);

//animation de l'attaque du guerrier
void attack_warrior(SDL_Surface *screen, SDL_Surface *back, SDL_Rect pos_map, int nbr_ennemies, int j,  Mix_Chunk *warrior_sound,hero raiden, hero slendy,perso ennemy[nbr_ennemies], int cible_ennemi);

//animation de la mort d'un ennemi
void death_animation(SDL_Surface *back ,SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies, int cible, Mix_Chunk *blood_explosion,hero raiden, hero slendy,perso ennemy[nbr_ennemies]);

//animation d'écoulement de sang (utilisée pour l'effet de l'attaque de l'archer)
void blood1_animation(SDL_Surface *back ,SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies, int attaquant,hero raiden, hero slendy,perso ennemy[nbr_ennemies], int cible_ennemi);

//animation de la mort de raiden
void death_animationhero(SDL_Surface *back ,SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies, Mix_Chunk *blood_explosion,hero raiden, hero slendy,perso ennemy[nbr_ennemies]);

//animation d'écoulement de sang (utilisée pour l'effet de l'attaque 1 et 2 de raiden)
void blood2_animation (SDL_Surface *back ,SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies, int cible,hero raiden, hero slendy,perso ennemy[nbr_ennemies]);

//animation d'écoulement de sang de tous les ennemies au même temps (utilisée pour l'effet de l'attaque 3 de raiden)
void blood3_animation(SDL_Surface *back ,SDL_Surface *screen, SDL_Rect pos_map, int nbr_ennemies,hero raiden, hero slendy,perso ennemy[nbr_ennemies]);

//animation d'écoulement de sang (utilisée pour l'effet de l'attaque du guerrier)
void blood4_animation (SDL_Surface *back ,SDL_Surface *screen, SDL_Rect pos_warrior, SDL_Rect pos_map, int nbr_ennemies, int attaquant,hero raiden, hero slendy,perso ennemy[nbr_ennemies], int cible_ennemi);

//fonction de l'affichage des barres de vies
void barre_bliting(SDL_Surface *screen, int nbr_ennemies,hero raiden, hero slendy,perso ennemy[nbr_ennemies]);

//fonction de l'initialisation des barres de vies
void barre_init(int nbr_ennemies,perso ennemy[nbr_ennemies],hero *raiden, hero *slendy);

//fonction pour afficher les dégats causés
void affich_degat(SDL_Surface *screen, SDL_Surface *degat, int dps, SDL_Rect pos, TTF_Font *police);

void affich_heal(SDL_Surface *screen, SDL_Surface *degat, int dps, SDL_Rect pos, TTF_Font *police);

void affiche_personnnages(SDL_Surface *back, SDL_Surface *screen, hero raiden, hero slendy, int nbr_ennemies,perso ennemy[nbr_ennemies], SDL_Rect pos_map);

void affiche_msg(SDL_Surface *screen,TTF_Font *police);

void attack_boss(SDL_Surface *screen, SDL_Surface *back, SDL_Rect pos_map, int nbr_ennemies, int j,hero raiden, hero slendy,perso ennemy[nbr_ennemies], int cible_ennemi, int attackealancer,int lvl);

void attack_boss5_ulti(SDL_Surface *screen, SDL_Surface *back, SDL_Rect pos_map, int nbr_ennemies, int j,hero raiden, hero slendy,perso ennemy[nbr_ennemies]);
#endif