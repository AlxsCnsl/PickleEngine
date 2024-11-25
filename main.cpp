//main.cpp===
#include "main.hpp"

//const pour GAME


int main(int argc, char** argv) {
    PkWindow window("Pickle ENGINE");
    
    SDL_Event event;
    while (window.is_running()) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                window.close();
            }
        }
    }

    return 0;
}
//===