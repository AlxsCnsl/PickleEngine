#include <iostream>
#include <window_render/window_render.hpp>
#include <app_loop_sdl3/app_loop_sdl3.hpp>

int main() {
    WindowRender window("PickleEngine", 800, 600);
    AppLoopSdl3 loop(window);

    loop.run();

    return 0;
}
