# rgb_pallet (SDL3)

Simplifies the usage of colors related to SDL3.

## Dependencies

- SDL3 (static library)

## Tools
```cpp
// In source code
namespace PKRGB {
    constexpr SDL_Color RED = {255, 0,   0,   255};
    // ...
}

// Applicable colors
PKRGB::RED
PKRGB::BLUE
PKRGB::YELLOW
PKRGB::PURPLE
PKRGB::PINK
PKRGB::CYAN
PKRGB::WHITE
PKRGB::L_GRAY
PKRGB::GRAY
PKRGB::D_GRAY
PKRGB::BLACK
```

## EXAMPLE:
```cpp
#include <window_render/window_render.hpp>
#include <easy_drawing/easy_drawing.hpp>

int main() {
    WindowRender window = WindowRender("ExampleWindow", 500, 500);
    window.init();

    bool isRunning = true;

    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }

        window.renderClear(); // Clear the screen with the set background color
        Line(&window, 0, 0, 100, 100, PKRGB::BLUE); // Draw a blue line
        window.renderPresent(); // Display the result on screen

        SDL_Delay(16); // Small delay to limit to ~60 FPS
    }

    return 0;
}
```

