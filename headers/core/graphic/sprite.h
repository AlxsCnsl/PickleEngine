#ifndef SPRITE_H
#define SPRITE_H

#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<string.h>
#include"../renderer.h"


typedef struct {
    int x_size;
    int y_size;
    int x_pose;
    int y_pose;
    SDL_Texture* texture;
}Sprite;

SDL_Texture* make_texture(char name_img[]);
Sprite* sprite_init(char* path_name, int x, int y, int width, int height);
void display_sprite(Sprite* sprite);

#endif //SPRITE_H