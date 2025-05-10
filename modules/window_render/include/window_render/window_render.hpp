#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <iostream>

class WindowRender {
public:
    WindowRender(const std::string& title, int width, int height);
    ~WindowRender();

    bool init();
    void render();
    void shutdown();

    SDL_Window* getWindow() const { return window; }
    SDL_Renderer* getRenderer() const { return renderer; }

private:
    std::string title;
    int width;
    int height;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
