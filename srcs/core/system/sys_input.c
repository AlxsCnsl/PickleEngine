#include "../../../headers/core/system/sys_input.h"

void get_sys_input(){
    while (SDL_PollEvent(&win_parameter->event)) {
        if (win_parameter->event.type == SDL_QUIT) {// Si on appuie sur la croix pour close la fenêtre
            win_parameter->runing = 0;
        } else if (win_parameter->event.type == SDL_KEYDOWN) {
            if (win_parameter->event.key.keysym.sym == SDLK_F11) {// Si on appuie sur F12, basculer entre plein écran et fenêtre
                toggle_full_screen(win_parameter);
            }
        }
    }  
}