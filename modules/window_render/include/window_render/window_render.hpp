#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <iostream>



class WindowRender {
public:

    struct ClearRGB{
        Uint8 red;
        Uint8 green;
        Uint8 blue;
        Uint8 aplpha;
        ClearRGB() : red(0), green(0), blue(0), aplpha(255)  {}
        ClearRGB(Uint8 r, Uint8 g, Uint8 b) : red(r), green(g), blue(b), aplpha(255) {}
        ClearRGB(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : red(r), green(g), blue(b), aplpha(a) {}
    };

    WindowRender(const std::string& title, int width, int height);
    WindowRender(const std::string& title, int width, int height, Uint8 rgb[4]);

    ~WindowRender();

    bool init();
    void renderClear();
    void renderPresent();
    void shutdown();

    SDL_Window* getWindow() const { return window; }
    SDL_Renderer* getRenderer() const { return renderer; }

    void setClearRGB(Uint8 r, Uint8 g, Uint8 b);
    void setClearRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void setClearRGBA(SDL_Color rgb);

    ClearRGB getClearRGB() const {return clear_rgb;}

private:


    ClearRGB clear_rgb;

    std::string title;
    int width;
    int height;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
