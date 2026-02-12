#include <app_loop/app_loop.hpp>
#include <iostream>

AppLoop::AppLoop(WindowRender* win)
:window(win) {
    // le WindowRender ne dois pas etre .init avant 
}

AppLoop::~AppLoop() {
    window->shutdown();
}

void AppLoop::run() {

    window->init();
    
    if (onInit) onInit(0.0f);

    auto lastTime = std::chrono::high_resolution_clock::now();

    while (isRunning) {

        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            if (onEvent) {
                onEvent(event);
            }
            
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }
    
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;

        
        if (onUpdate) onUpdate(deltaTime);
        window ->renderClear();
        if (onRender) onRender(deltaTime);
        window->renderPresent();

        SDL_Delay(16);
    }

    if (onShutdown) onShutdown(0.0f);
}