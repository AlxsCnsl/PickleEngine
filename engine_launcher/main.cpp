
#include <window_render/window_render.hpp>
#include <app_loop/app_loop.hpp>
#include <easy_drawing/easy_drawing.hpp>
#include <rgb_pallet/rgb_pallet.hpp>
#include <sprite_class/sprite_class.hpp>

#include<SDL3_image/SDL_image.h>
#include<SDL3/SDL.h>

int main (){
    WindowRender* window = new WindowRender("ExampleWindow", 500, 500);
    AppLoop* app = new AppLoop(window);

    app->setOnInit([app](float deltatime){
        app->getWindow()->setClearRGBA(PKRGB::L_GRAY);
    });

    app->setOnUpdate([app](float deltatime){

    });

    
    app->setOnRender([app](float deltatime){
        WindowRender* win = app->getWindow();

        Sprite* psyduck = new Sprite(win, "assets/psyduck.png", SDL_SCALEMODE_PIXELART);

        psyduck->draw_sprite(win,{0, 0, 100, 100});
        psyduck->draw_sprite(win,{100, 0, 100, 100});
        psyduck->draw_sprite(win,{0, 100, 100, 100});
        psyduck->draw_sprite(win,{100, 100, 100, 100});

    });

    app->setOnShutdown({
        //logique de de fermeture de l'app
    });

    app->run();


    return 0;
}