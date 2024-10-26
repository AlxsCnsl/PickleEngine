#include "../../headers/core/renderer.h"

SDL_Renderer* rederer_init(SDL_Window* window){
    // Initialiser SDL_image
    if (IMG_Init(IMG_INIT_PNG) == 0 & IMG_INIT_PNG) {
        printf("Erreur lors de l'initialisation de SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
    }
    // Créer un rendu
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    }
    return renderer;
}