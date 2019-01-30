#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include "smpeg.h"


intro( SDL_Surface *ecran)
{
	SDL_Surface *surfaceVideo = NULL;

	SMPEG_Info mpg_info;
    SMPEG *mpg = NULL;
    int maxW, maxH;
   
    mpg = SMPEG_new("cinematique.mpg", &mpg_info, 2);
    
    if (SMPEG_error(mpg))
    {
                fprintf(stderr, "Impossible de charge la video video.mpg");
        exit(EXIT_FAILURE);
    }

    ecran = SDL_SetVideoMode(0, 0, 0, SDL_FULLSCREEN | SDL_DOUBLEBUF);
    if (ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    surfaceVideo = SDL_AllocSurface(SDL_HWSURFACE, mpg_info.width, mpg_info.height , ecran->format->BitsPerPixel, ecran->format->Rmask, ecran->format->Gmask, ecran->format->Bmask, ecran->format->Amask);
    if (surfaceVideo == NULL)
    {
                fprintf(stderr, "Impossible d'allouer la surface vidéo");
        exit(EXIT_FAILURE);
    }
    const SDL_VideoInfo *videoInfo;
 
    videoInfo=SDL_GetVideoInfo();
    maxW=videoInfo->current_w;
    maxH=videoInfo->current_h;
    SMPEG_scaleXY( mpg, maxW, maxH);
    SMPEG_setdisplay(mpg, surfaceVideo, NULL,NULL);
    SMPEG_play(mpg);
    while (SMPEG_status(mpg) == SMPEG_PLAYING)
    {
    SDL_BlitSurface(surfaceVideo, NULL, ecran, NULL);
    SDL_Flip(ecran);
	}
    SMPEG_stop(mpg);
    SMPEG_delete(mpg);
    mpg = NULL;
    surfaceVideo = NULL;
    return 0 ;
    SDL_Quit();
}
