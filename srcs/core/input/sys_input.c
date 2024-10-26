#include "../../../headers/core/input/sys_input.h"

void get_sys_input(SDL_Window* window, WindowParameter *wp){
    while (SDL_PollEvent(&wp->event)) {
        if (wp->event.type == SDL_QUIT) {// Si on appuie sur la croix pour close la fenêtre
            wp->runing = 0;
        } else if (wp->event.type == SDL_KEYDOWN) {
            if (wp->event.key.keysym.sym == SDLK_F11) {// Si on appuie sur F12, basculer entre plein écran et fenêtre
                toggle_full_screen(window, wp);
            }
        }
    }  
}