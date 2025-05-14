# Window_Maker module (for SDL3)

Simplifies the initialization of windows and rendering.

## Dependencies 

SDL3 (static lib)

## Functions

```cpp
// Create a WindowRender instance
WindowRender window_variable = WindowRender();

// Initializes the SDL window and renderer with a title, width, and height
window_variable.init(const std::string& title, int width, int height); // return void

// Applies the renderer (displays the current frame on screen)
window_variable.render(); // return void

// Properly destroys the window and renderer
window_variable.shutdown(); // return void

// Returns a pointer to the created SDL_Window
window_variable.getWindow(); // return SDL_Window*

// Returns a pointer to the associated SDL_Renderer
window_variable.getRenderer(); // return SDL_Renderer*

```

## EXAMPLE : 
 ```cpp

 #include <window_render/window_render.hpp>

 int main (){
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

        window.render();

        SDL_Delay(16);
    }
    return 0;
}

 ```
