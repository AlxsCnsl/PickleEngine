#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <iostream>



class WindowRender {
public:

    struct ClearRGB{
        int red;
        int green;
        int blue;
        int aplpha;
        ClearRGB() : red(1), green(0), blue(0), aplpha(255)  {}
        ClearRGB(int r, int g, int b) : red(r), green(g), blue(b), aplpha(255) {}
        ClearRGB(int r, int g, int b, int a) : red(r), green(g), blue(b), aplpha(a) {}
    };

    WindowRender(const std::string& title, int width, int height);
    WindowRender(const std::string& title, int width, int height, int rgb[4]);

    ~WindowRender();

    bool init();
    void renderClear();
    void renderPresent();
    void shutdown();

    SDL_Window* getWindow() const { return window; }
    SDL_Renderer* getRenderer() const { return renderer; }

    void setClearRGB(int r, int g, int b);
    void setClearRGBA(int r, int g, int b, int a);

    ClearRGB getClearRGB() const {return clear_rgb;}

private:


    ClearRGB clear_rgb;

    std::string title;
    int width;
    int height;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
