#include "game_manager.hpp"

// Modules
#include <window_render/window_render.hpp>
#include <app_loop/app_loop.hpp>
#include <easy_drawing/easy_drawing.hpp>
#include <rgb_pallet/rgb_pallet.hpp>
#include <keyboard_manager/keyboard_manager.hpp>
#include <ecs_sprite/ecs_sprite.hpp>

#include <iostream>

GameManager::GameManager() {
    // Créer la fenêtre et l'app
    window = std::make_unique<WindowRender>("ExampleWindow", 500, 500);
    app = std::make_unique<AppLoop>(window.get());
    keyboard = std::make_unique<KeyboardInput::KeyboardManager>();
    spriteManager = std::make_unique<SpriteManager>(window.get());

    // Configurer les callbacks
    app->setOnInit([this](float dt){ init(); });
    app->setOnEvent([this](const SDL_Event& e){ handleEvents(e); });
    app->setOnUpdate([this](float dt){ update(dt); });
    app->setOnRender([this](float dt){ render(dt); });
    app->setOnShutdown([this](float dt){ shutdown(dt); });
}

GameManager::~GameManager() = default;

void GameManager::run() {
    app->run();
}

void GameManager::init() {
    window->setClearRGBA(PKRGB::L_GRAY);
    keyboard->initialize();
    std::cout << "Keyboard manager initialized\n";

    // Créer le sprite du joueur
    player = spriteManager->getFactory()->createStaticSprite(
        registry,
        "assets/psyduck.png",
        x, y,
        3
    );

    if (player == entt::null) {
        std::cerr << "Failed to create player sprite!\n";
    } else {
        std::cout << "Player sprite created successfully!\n";
    }
}

void GameManager::handleEvents(const SDL_Event& event) {
    keyboard->handleEvent(event);
}

void GameManager::update(float deltatime) {
    keyboard->update();

    if (keyboard->isKeyDown(SDL_SCANCODE_A)) x -= velocity * deltatime;
    if (keyboard->isKeyDown(SDL_SCANCODE_D)) x += velocity * deltatime;
    if (keyboard->isKeyDown(SDL_SCANCODE_W)) y -= velocity * deltatime;
    if (keyboard->isKeyDown(SDL_SCANCODE_S)) y += velocity * deltatime;

    // Mettre à jour la position du sprite
    if (player != entt::null && registry.valid(player)) {
        auto& pos = registry.get<Position>(player);
        pos.x = x;
        pos.y = y;
    }

    spriteManager->update(registry, deltatime);
    spriteManager->printStats(registry);
}

void GameManager::render(float deltatime) {
    spriteManager->render(registry);
}

void GameManager::shutdown(float deltatime) {
    keyboard->shutdown();
    std::cout << "Shutting down...\n";
}
