#pragma once

#include <vector>
#include <map>
#include <functional>
#include <chrono>
#include <SDL3/SDL.h>
#include <window_render/window_render.hpp>

class AppLoop{
public:
    AppLoop(WindowRender* win);
    ~AppLoop();

    using Callback = std::function<void(float)>;
    using EventCallback = std::function<void(const SDL_Event&)>;

    void setOnInit(Callback cb)       { onInit = cb; }
    void setOnUpdate(Callback cb)     { onUpdate = cb; }
    void setOnRender(Callback cb)     { onRender = cb; }
    void setOnShutdown(Callback cb)   { onShutdown = cb; }
    void setOnEvent(EventCallback cb) { onEvent = cb; }

    void run(); // Only returns when the game is finished

    WindowRender* getWindow() const {return window;}

private:
    Callback onInit     = nullptr;
    Callback onUpdate   = nullptr;
    Callback onRender   = nullptr;
    Callback onShutdown = nullptr;
    EventCallback onEvent = nullptr;

    bool isRunning = true;

    WindowRender* window;
};