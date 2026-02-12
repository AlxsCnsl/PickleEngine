#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <iostream>
#include<memory>


class WindowRender {
public:

    WindowRender(const WindowRender&) = delete;
    WindowRender& operator=(const WindowRender&) = delete;
    WindowRender(WindowRender&&) = default;
    WindowRender& operator=(WindowRender&&) = default;


    struct ClearRGB{
        Uint8 red;
        Uint8 green;
        Uint8 blue;
        Uint8 alpha;
        ClearRGB() : red(0), green(0), blue(0), alpha(255)  {}
        ClearRGB(Uint8 r, Uint8 g, Uint8 b) : red(r), green(g), blue(b), alpha(255) {}
        ClearRGB(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : red(r), green(g), blue(b), alpha(a) {}
    };

    WindowRender(const std::string& title, int width, int height);
    WindowRender(const std::string& title, int width, int height, Uint8 rgb[4]);

    ~WindowRender();

    bool init();
    void renderClear();
    void renderPresent();
    void shutdown();

    SDL_Window* getWindow() const { return window.get(); }
    SDL_Renderer* getRenderer() const { return renderer.get(); }

    void setClearRGB(Uint8 r, Uint8 g, Uint8 b);
    void setClearRGBA(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void setClearRGBA(SDL_Color rgb);

    ClearRGB getClearRGB() const {return clear_rgb;}

private:


    ClearRGB clear_rgb;

    std::string title;
    int width;
    int height;

    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window{nullptr, SDL_DestroyWindow};
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer{nullptr, SDL_DestroyRenderer};

};
