#include <window_render/window_render.hpp>
#include <app_loop/app_loop.hpp>
#include <easy_drawing/easy_drawing.hpp>
#include <rgb_pallet/rgb_pallet.hpp>
#include <sprite_class/sprite_class.hpp>
#include <keyboar_manager/keyboar_manager.hpp>

#include<SDL3_image/SDL_image.h>
#include<SDL3/SDL.h>
#include<entt/entt.hpp>
#include<iostream>

int main (){
    WindowRender* window = new WindowRender("ExampleWindow", 500, 500);
    AppLoop* app = new AppLoop(window);

    float x = 0;
    float y = 0;
    float velocity = 100;
    KeyboardInput::KeyboardManager keyboard; 

    Sprite* sp1 = nullptr;

    app->setOnInit([&](float deltatime){
        app->getWindow()->setClearRGBA(PKRGB::L_GRAY);
        keyboard.initialize();
        
        sp1 = new Sprite(window, "assets/psyduck.png", SDL_SCALEMODE_PIXELART);
        
        std::cout << "Keyboard manager initialized" << std::endl;
    });

    app->setOnEvent([&](const SDL_Event& event){
        keyboard.handleEvent(event);
    });

    app->setOnUpdate([&](float deltatime){

        keyboard.update();
        
    
        if (keyboard.isKeyDown(SDL_SCANCODE_A)) {  // Q pour aller à gauche
            x -= velocity * deltatime;
            std::cout << "Q pressed - x: " << x << std::endl;   
        }
        if (keyboard.isKeyDown(SDL_SCANCODE_D)) {  // D pour aller à droite
            x += velocity * deltatime;
            std::cout << "D pressed - x: " << x << std::endl;
        }
        if (keyboard.isKeyDown(SDL_SCANCODE_W)) {  // Z pour aller en haut
            y -= velocity * deltatime;
            std::cout << "Z pressed - y: " << y << std::endl;
        }
        if (keyboard.isKeyDown(SDL_SCANCODE_S)) {  // S pour aller en bas
            y += velocity * deltatime;
            std::cout << "S pressed - y: " << y << std::endl;
        }

    });
    
    app->setOnRender([&](float deltatime){
        if (sp1) { 
            sp1->draw_sprite(window, {x, y, 100, 100});
        }
    });

    app->setOnShutdown([&](float deltatime){
        keyboard.shutdown();
        std::cout << "Shutting down..." << std::endl;
    });

    app->run();
    
    // Nettoyer après la fin de la boucle
    delete sp1;
    delete app;
    delete window;
    
    return 0;
}