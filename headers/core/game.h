#ifndef GAME_H
#define GAME_H

#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"window.h"
#include"renderer.h"
#include"deltatime.h"
#include"sprite.h"
#include"input/sys_input.h"

void game_test();

void run(DeltaTime *dt, WindowParameter *wp);

#endif //GAME_H