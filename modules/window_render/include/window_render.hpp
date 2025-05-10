#pragma once

#include <SDL3/SDL.h>
#include <ModuleInterface.hpp>

class WindowRenderModule : public ModuleInterface {
public:
    WindowRenderModule();
    ~WindowRenderModule();

    bool onInit() override;
    void onUpdate(float deltaTime) override;
    void onShutdown() override;
    std::string getName() const override {
        return "WindowRenderModule";
    }

    SDL_Window* getWindow() const { return window; }
    SDL_Renderer* getRenderer() const { return renderer; }

private:
    bool done = false;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
