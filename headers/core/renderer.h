#ifndef RENDERER_H
#define RENDERER_H

#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"window.h"

extern SDL_Renderer* renderer;

void rederer_init();

#endif //RENDERER_H