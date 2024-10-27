#include "../../headers/core/sprite.h"

SDL_Texture* make_texture(char name_img[]){
    // Charger une image depuis un fichier et créer une texture
    SDL_Surface* imageSurface = IMG_Load(name_img);
    if (!imageSurface) {
        printf("Erreur lors du chargement de l'image : %s\n", IMG_GetError());
    }
    // Convertir l'image en texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if (!texture) {
        printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
    }
    // Libérer la surface une fois la texture créée
    SDL_FreeSurface(imageSurface);
    return texture;
}

void sprite_init(Sprite* sprite, char* path_name, int x, int y, int width, int height){
    sprite->x_size = width;
    sprite->y_size = height;
    sprite->x_pose = x;
    sprite->y_pose = y;
    sprite->texture = make_texture(path_name);
}

void display_sprite(Sprite sprite, int x_pose, int y_pose){
    SDL_Rect destinationRect = {sprite.x_pose, sprite.y_pose, sprite.x_size, sprite.y_size };// x, y, width, height
    SDL_RenderCopy(renderer, sprite.texture, NULL, &destinationRect);
}

// ========= futur gride.h =======================

