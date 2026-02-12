# app_loop module (for SDL3)

This module simplifies the creation of a main application loop for event-driven SDL3 applications.
It allows you to define initialization, update, rendering, and shutdown callbacks in a clean and modular way.

## Dependencies 

SDL3 (static lib)
window_render (module)

## Functions

```cpp
// Creates an instance of AppLoopSdl3 using a WindowRender object
AppLoop app = AppLoop(WindowRender* win);

// Defines a callback type that takes a float (delta time)
using Callback = std::function<void(float)>;

// Sets the initialization logic (called once at app start)
app.setOnInit(Callback cb); // return void

// Sets the update logic (called every frame, receives delta time)
app.setOnUpdate(Callback cb); // return void

// Sets the rendering logic (called every frame, after update)
app.setOnRender(Callback cb); // return void

// Sets the shutdown logic (called once before the app closes)
app.setOnShutdown(Callback cb); // return void

// Starts the application loop (returns when the app exits)
app.run(); // return void

```

## EXAMPLE : 
 ```cpp

#include <window_render/window_render.hpp>
#include <app_loop/app_loop.hpp>

int main (){
    WindowRender* window = new WindowRender("ExampleWindow", 500, 5000);
    AppLoop app = AppLoop(window);

    app.setOnInit([&app](float deltatime){
        app.getWindow()->setClearRGB(255, 0, 0);
    });

    app.setOnUpdate({
        // Updating logic
    });

    app.setOnRender([&app](float deltatime) {
        WindowRender::ClearRGB rgb = app.getWindow()->getClearRGB();
        int factor = 5;
        for (int i = 0; i < factor; i++) {
            if (rgb.red == 255 && rgb.green < 255 && rgb.blue == 0) {  // Red → Yellow
                rgb.green++;
            } else if (rgb.red > 0 && rgb.green == 255 && rgb.blue == 0) {  // Yellow → Green
                rgb.red--;
            } else if (rgb.red == 0 && rgb.green == 255 && rgb.blue < 255) {  // Green → Cyan
                rgb.blue++;
            } else if (rgb.red == 0 && rgb.green > 0 && rgb.blue == 255) {  // Cyan → Blue
                rgb.green--;
            } else if (rgb.red < 255 && rgb.green == 0 && rgb.blue == 255) {  // Blue → Magenta
                rgb.red++;
            } else if (rgb.red == 255 && rgb.green == 0 && rgb.blue > 0) {  // Magenta → Red
                rgb.blue--;
            }
        }
        app.getWindow()->setClearRGB(rgb.red, rgb.green, rgb.blue);
    });

    app.setOnShutdown({
        // app shutdown logic
    });

    app.run();


    return 0;
}
 ```

## Notes

Callbacks receive a float representing the time (in seconds) since the last frame — useful for time-based updates.

WindowRender must be initialized before being passed to AppLoop().

In the setOnRender callback, you do not need to call WindowRender::render() or SDL_RenderPresent(renderer) manually.
These are automatically called at the end of each frame by the main loop, after your rendering logic is executed.