#include <iostream>
#include <window_render/window_render.hpp>

int main() {
    WindowRender window("PickleEngine", 800, 600);
    if (!window.init()) return -1;

    bool running = true;
    float deltaTime = 0.016f;
    int frameCount = 0;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }
    
        window.render();
        SDL_Delay(16);
    }
    

    return 0;
}
