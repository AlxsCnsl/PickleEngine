#include <sprite_class/sprite_class.hpp>

#include <iostream>

Sprite::Sprite(WindowRender* window, std::string path_name, SDL_ScaleMode scale_mode) {
    set_texture(window, path_name);
    set_scale_mode(scale_mode);

}

Sprite::~Sprite() {
    free(texture);
}

void Sprite::draw_sprite(WindowRender* win, SDL_FRect rect){
    SDL_RenderTexture(win->getRenderer(), texture, nullptr, &rect);
}

void Sprite::set_scale_mode( SDL_ScaleMode mode){
    SDL_SetTextureScaleMode(texture, mode);
}


void Sprite::set_texture(WindowRender* window, std::string path_name){
    const char* base_path = SDL_GetBasePath();
    std::string asset_path = std::string(base_path) + path_name;
    texture = IMG_LoadTexture(window->getRenderer(), asset_path.c_str());
}
