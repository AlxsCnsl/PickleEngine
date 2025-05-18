# Window_Maker module (for SDL3)

Simplifies the initialization of windows and rendering.

## Dependencies 

SDL3 (static lib)

## Functions

```cpp
// Create a WindowRender instance----------------------------------------------------
WindowRender window_variable = WindowRender(const std::string& title, int width, int height); //clear color = black

WindowRender window_variable = WindowRender(const std::string& title, int width, int height, int rgb[4]);
/* rgb[0] = red   (0 to 255)
** rgb[1] = green (0 to 255)
** rgb[2] = blue  (0 to 255)
** rgb[3] = alpha (O to 255)
*/

// Initializes the SDL window and renderer with a title, width, and height-----------
window_variable.init(); // return void

// Applies the renderer (displays the current frame on screen)-----------------------
window_variable.render(); // return void

// Properly destroys the window and renderer-----------------------------------------
window_variable.shutdown(); // return void

// Returns a pointer to the created SDL_Window---------------------------------------
window_variable.getWindow(); // return SDL_Window*

// Returns a pointer to the associated SDL_Renderer----------------------------------
window_variable.getRenderer(); // return SDL_Renderer*

// Change the background color when clearing ----------------------------------------
window_variable.setClearRGB(int r, int g, int b); // returns void
window_variable.setClearRGBA(int r, int g, int b, int a); // returns void
/* r = red   (0 to 255)
** g = green (0 to 255)
** b = blue  (0 to 255)
** a = alpha (0 to 255)
*/

// Get the background color ---------------------------------------------------------
window_variable.getClearRGB() //return ClearRGB
/*
**  struct ClearRGB{
**        int red;
**        int green;
**        int blue;
**        int aplpha;
**  }
*/

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
