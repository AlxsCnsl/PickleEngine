#ifndef SPRITE_H
#define SPRITE_H

#include<stdio.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<string.h>


typedef struct {
    int x_size;
    int y_size;
    int x_pose;
    int y_pose;
    SDL_Texture* texture;
}Sprite;

SDL_Texture* make_texture(SDL_Renderer* renderer, char name_img[]);

void sprite_init(SDL_Renderer* renderer, Sprite* sprite, char* path_name, int x, int y, int width, int height);
void display_sprite(SDL_Renderer* renderer, Sprite sprite, int x_pose, int y_pose);

// ========= futur gride.h =======================


#endif //SPRITE_H