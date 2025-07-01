#include <window_render/window_render.hpp>
#include <app_loop/app_loop.hpp>
#include <easy_drawing/easy_drawing.hpp>
#include <rgb_pallet/rgb_pallet.hpp>
#include <keyboar_manager/keyboar_manager.hpp>
#include <ecs_sprite/ecs_sprite.hpp>

#include<SDL3_image/SDL_image.h>
#include<SDL3/SDL.h>
#include<entt/entt.hpp>
#include<iostream>
#include<memory>

int main (){
    // Utiliser des pointeurs intelligents
    auto window = std::make_unique<WindowRender>("ExampleWindow", 500, 500);
    auto app = std::make_unique<AppLoop>(window.get()); // Passer le pointeur brut à AppLoop

    float x = 250; // Centrer initialement
    float y = 250;
    float velocity = 100;
    KeyboardInput::KeyboardManager keyboard;
    SpriteManager spriteManager(window.get());
    entt::registry registry;
    
    entt::entity player = entt::null; // Initialiser à null

    app->setOnInit([&](float deltatime){
        app->getWindow()->setClearRGBA(PKRGB::L_GRAY);
        keyboard.initialize();
        
        std::cout << "Keyboard manager initialized" << std::endl;
        std::cout << "Renderer ready, loading sprite..." << std::endl;
        
        // Créer le sprite ici, une fois que le renderer est prêt
        player = spriteManager.getFactory()->createStaticSprite(
            registry,
            "assets/psyduck.png",
            x, y,
            0
        );
        
        if (player == entt::null) {
            std::cerr << "Failed to create player sprite!" << std::endl;
        } else {
            std::cout << "Player sprite created successfully!" << std::endl;
        }
    });

    app->setOnEvent([&](const SDL_Event& event){
        keyboard.handleEvent(event);
        
    });

    app->setOnUpdate([&](float deltatime){
        keyboard.update();
    
        // Logique de mouvement (corrigée pour AZERTY)
        if (keyboard.isKeyDown(SDL_SCANCODE_A)) {  // A pour aller à gauche
            x -= velocity * deltatime;
            std::cout << "A pressed - x: " << x << std::endl;   
        }
        if (keyboard.isKeyDown(SDL_SCANCODE_D)) {  // D pour aller à droite
            x += velocity * deltatime;
            std::cout << "D pressed - x: " << x << std::endl;
        }
        if (keyboard.isKeyDown(SDL_SCANCODE_W)) {  // W pour aller en haut 
            y -= velocity * deltatime;
            std::cout << "W pressed - y: " << y << std::endl;
        }
        if (keyboard.isKeyDown(SDL_SCANCODE_S)) {  // S pour aller en bas
            y += velocity * deltatime;
            std::cout << "S pressed - y: " << y << std::endl;
        }
        
        // IMPORTANT: Mettre à jour la position du sprite
        if (player != entt::null && registry.valid(player)) {
            auto& pos = registry.get<Position>(player);
            pos.x = x;
            pos.y = y;
        }
        
        // Mettre à jour les animations
        spriteManager.update(registry, deltatime);
    });
    
    app->setOnRender([&](float deltatime){
        // IMPORTANT: Effectuer le rendu des sprites
        spriteManager.render(registry);
    });

    app->setOnShutdown([&](float deltatime){
        keyboard.shutdown();
        std::cout << "Shutting down..." << std::endl;
    });

    app->run();
    
    // Plus besoin de delete ! Les pointeurs intelligents s'en chargent automatiquement
    std::cout << "Program ended cleanly" << std::endl;
    
    return 0;
}