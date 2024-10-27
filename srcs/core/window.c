#include "../../headers/core/window.h"

char WIN_TITLE[128] = "Pickle Jumper";
SDL_Window* window = NULL;

void window_init() {
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
    }
    // Créer une fenêtre
    window = SDL_CreateWindow(WIN_TITLE, //c'est une const
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
    }
}

void update_window_size_parameter(SDL_Window* window, WindowParameter* wp){
    SDL_GetWindowSize(window, &wp->x_size, &wp->y_size);
    wp->x_center = wp->x_size/2;
    wp->y_center = wp->y_size/2;
}

void toggle_full_screen(SDL_Window* window, WindowParameter* wp){
    if (wp->is_full_screen) {
        // Revenir en mode fenêtre
        SDL_SetWindowFullscreen(window, 0); // 0 = mode fenêtre
        wp->is_full_screen = 0;
    } else {
        // Passer en plein écran
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); // SDL_WINDOW_FULLSCREEN = plein écran exclusif
        wp->is_full_screen = 1;
    }
    update_window_size_parameter(window, wp);
}

void window_parameter_init(SDL_Window* window, WindowParameter* wp){
    wp->runing = 1;
    wp->is_full_screen = 0;
    wp->max_fps = 60;
    update_window_size_parameter(window, wp);
}
