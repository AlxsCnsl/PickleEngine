
#include <window_render/window_render.hpp>
#include <app_loop/app_loop.hpp>
#include <easy_drawing/easy_drawing.hpp>
#include <rgb_pallet/rgb_pallet.hpp>
#include <sprite_class/sprite_class.hpp>

#include<SDL3_image/SDL_image.h>
#include<SDL3/SDL.h>

#include<entt/entt.hpp>


// mes structe


struct Position {
    float x, y;
};

struct Velocity {
    float dx, dy;
};

int main (){
    WindowRender* window = new WindowRender("ExampleWindow", 500, 500);
    AppLoop* app = new AppLoop(window);
    entt::registry registry;//le registry

    auto entity = registry.create();

    app->setOnInit([&](float deltatime){//----------------INIT_________________

        app->getWindow()->setClearRGBA(PKRGB::L_GRAY);
        //test palyer
        registry.emplace<Position>(entity, 0.0f, 0.0f);
        registry.emplace<Velocity>(entity, 30.0f, 30.0f);
    
    });

    app->setOnUpdate([&](float deltatime){//--------------UPDATE_________________
    });
    
    app->setOnRender([&](float deltatime){//--------------RENDER__________________
        WindowRender* win = app->getWindow();
        Sprite sp1 = Sprite(win, "assets/psyduck.png", SDL_SCALEMODE_PIXELART);
        sp1.draw_sprite(win, {0,0, 100, 100});
    });

    app->setOnShutdown({//_________________________ShutDown
        //logique de de fermeture de l'app
    });

    app->run();


    return 0;
}