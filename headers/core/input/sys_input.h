#ifndef SYS_INPUT_H
#define SYS_INPUT_H

#include<stdio.h>
#include<SDL2/SDL.h>
#include<string.h>
#include "../window.h"

void get_sys_input(SDL_Window* window, WindowParameter *wp);

#endif //SYS_INPUT_H