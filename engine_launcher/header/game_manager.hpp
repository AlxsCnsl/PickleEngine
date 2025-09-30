#pragma once
#include <memory>

#include <SDL3/SDL.h>
#include <entt/entt.hpp>

class WindowRender;
class AppLoop;
class SpriteManager;
namespace KeyboardInput { class KeyboardManager; }

class GameManager {
public:
    GameManager();
    ~GameManager();

    void run();

private:
    void init();
    void handleEvents(const SDL_Event& event);
    void update(float deltatime);
    void render(float deltatime);
    void shutdown(float deltatime);

    // Pointeurs intelligents pour la gestion automatique
    std::unique_ptr<WindowRender> window;
    std::unique_ptr<AppLoop> app;
    std::unique_ptr<KeyboardInput::KeyboardManager> keyboard;
    std::unique_ptr<SpriteManager> spriteManager;

    entt::registry registry;
    entt::entity player = entt::null;

    // Position et vitesse du joueur
    float x = 0;
    float y = 0;
    float velocity = 100.0f;
};
