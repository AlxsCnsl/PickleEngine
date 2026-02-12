# easy_drawing module (for SDL3)

`easy_drawing` is a simple and self-contained module for SDL3 that provides **2D primitive drawing functions**: points, lines, rectangles, circles, etc.  
It is designed to be used with a `WindowRender` instance, in order to encapsulate and simplify graphical rendering in SDL3 applications.

---

## Dependencies

- SDL3 (static library)  
- window_render (module)

---

## Functions

```cpp
// Draws a single pixel at (x, y)
PutPixel(WindowRender* window, int x, int y, SDL_Color color);

// Draws a horizontal line from (x, y) with the given "length"
HLine(WindowRender* window, int x, int y, int length, SDL_Color color);

// Draws a vertical line from (x, y) with the given "length"
VLine(WindowRender* window, int x, int y, int length, SDL_Color color);

// Draws a line from (x1, y1) to (x2, y2)
Line(WindowRender* window, int x1, int y1, int x2, int y2, SDL_Color color);

// Draws a line from (x, y) with a given length and angle (in radians)
LineAngle(WindowRender* window, int x, int y, float length, float angleRadians, SDL_Color color);

// Draws an unfilled rectangle
DrawRect(WindowRender* window, int x, int y, int w, int h, SDL_Color color);

// Draws a filled rectangle
FillRect(WindowRender* window, int x, int y, int w, int h, SDL_Color color);

// Draws an unfilled circle
DrawCircle(WindowRender* window, int centerX, int centerY, int radius, SDL_Color color);

// Draws a filled circle
FillCircle(WindowRender* window, int centerX, int centerY, int radius, SDL_Color color);
```

## EXAMPLE : 
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
        Line(&window, 0, 0, 100, 100, {255, 0, 0, 255}); // Draw a red line
        window.renderPresent(); // Display the result on screen

        SDL_Delay(16); // Small delay to limit to ~60 FPS
    }

    return 0;
}
 ```

 ## Notes

Can be used with the `app_loop` module inside `AppLoop::setOnRender({ })`