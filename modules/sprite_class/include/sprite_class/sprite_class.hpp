#pragma once
#include <window_render/window_render.hpp>
#include <SDL3_image/SDL_image.h>

class Sprite{
public:
    Sprite(WindowRender* window, std::string path_name,SDL_ScaleMode scale_mode);
    ~Sprite();

    void draw_sprite(WindowRender* win, SDL_FRect rect);

    void set_scale_mode( SDL_ScaleMode mode);
    
private:
    void set_texture(WindowRender* window, std::string path_name);
    SDL_Texture* texture;
};


