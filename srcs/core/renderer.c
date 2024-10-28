//rendere.c===
#include "../../headers/core/renderer.h"

SDL_Renderer* renderer = NULL;

void rederer_init(){
    // Initialiser SDL_image
    if ((IMG_Init(IMG_INIT_PNG) == 0) && IMG_INIT_PNG) {
        printf("Erreur lors de l'initialisation de SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
    }
    // Créer un rendu
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);//window est la const
    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);//window est la const
        IMG_Quit();
        SDL_Quit();
    }
}
//===