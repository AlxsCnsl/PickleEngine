# app_loop module (for SDL3)

This module simplifies the creation of a main application loop for event-driven SDL3 applications.
It allows you to define initialization, update, rendering, and shutdown callbacks in a clean and modular way.

## Dependencies 

SDL3 (static lib)
window_render (module)

## Functions

```cpp
// Creates an instance of AppLoopSdl3 using a WindowRender object
AppLoop app = AppLoop(WindowRender win);

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

int main() {
    WindowRender window = WindowRender("ExampleWindow", 500, 500);
    AppLoop app(window);

    app.setOnInit([](float) {
        // Initialization logic
    });

    app.setOnUpdate([](float deltaTime) {
        // Update logic using deltaTime
    });

    app.setOnRender([](float) {
        // Rendering logic
    });

    app.setOnShutdown([](float) {
        // Cleanup logic
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