#include <window_render/window_render.hpp>

WindowRender::WindowRender(const std::string& title, int width, int height)
:title(title), width(width), height(height), clear_rgb() {}

WindowRender::WindowRender(const std::string& title, int width, int height, Uint8 rgb[4])
:title(title), width(width), height(height), clear_rgb(rgb[0] ,rgb[1], rgb[2], rgb[3]) {}


WindowRender::~WindowRender() {
    shutdown();
}



bool WindowRender::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title.c_str(), width, height, SDL_WINDOW_OPENGL);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return false;
    } 

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}


void WindowRender::renderClear() {
    std::cout << "Rendering frame..." << std::endl;
    SDL_SetRenderDrawColor(renderer, clear_rgb.red, clear_rgb.green, clear_rgb.blue, 255);
    SDL_RenderClear(renderer);
}

void WindowRender::renderPresent(){
    SDL_RenderPresent(renderer);
}


void WindowRender::shutdown() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}


void WindowRender::setClearRGB(Uint8 r, Uint8 g, Uint8 b){
    clear_rgb.red = r;
    clear_rgb.green = g;
    clear_rgb.blue = b;
}


void WindowRender::setClearRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    setClearRGB(r, g, b);
    clear_rgb.aplpha = a;
}

void WindowRender::setClearRGBA(SDL_Color rgb){
    clear_rgb.red = rgb.r;
    clear_rgb.green = rgb.g;
    clear_rgb.blue = rgb.b;
    clear_rgb.aplpha = rgb.a;
}