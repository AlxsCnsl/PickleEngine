#include "../../headers/system/game_input.h"

int keyboard_press_check(SDL_Scancode key_check){
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if (keystates[key_check]){
        return 1;
    }
    return 0;
}
