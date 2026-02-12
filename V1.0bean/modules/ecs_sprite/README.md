# ecs_sprite module (for SDL3)

This module provides a comprehensive Entity Component System (ECS) based sprite management system for SDL3 applications. It handles texture loading, sprite rendering, animations, and provides efficient batch rendering with layer management.

## Dependencies

- SDL3 (static lib)
- SDL3_image
- EnTT (Entity Component System library)
- window_render module

## Components

### Position
```cpp
struct Position {
    float x, y;
    float rotation = 0.0f;
    
    Position(float x = 0, float y = 0);
};
```

### Transform
```cpp
struct Transform {
    float scaleX = 1.0f, scaleY = 1.0f;
    
    Transform(float sx = 1.0f, float sy = 1.0f);
};
```

### SpriteComponent
```cpp
struct SpriteComponent {
    uint32_t textureId;           // ID of texture in TextureManager
    SDL_FRect sourceRect;         // Source rectangle in texture (for sprite sheets)
    bool visible = true;
    int layer = 0;                // Render order (z-order)
    
    SpriteComponent(uint32_t id, SDL_FRect src = {0, 0, 0, 0});
};
```

### AnimationComponent
```cpp
struct AnimationComponent {
    uint32_t currentFrame = 0;
    uint32_t frameCount;
    float frameTime;              // Time per frame
    float currentTime = 0.0f;
    bool loop = true;
    bool playing = true;
    
    AnimationComponent(uint32_t frames, float time);
};
```

## Core Classes

### TextureManager

Manages texture loading, caching, and provides texture information.

```cpp
class TextureManager {
public:
    explicit TextureManager(WindowRender* win);
    ~TextureManager();
    
    // Load a texture and return its ID
    uint32_t loadTexture(const std::string& path, SDL_ScaleMode scaleMode = SDL_SCALEMODE_LINEAR);
    
    // Get texture by ID
    SDL_Texture* getTexture(uint32_t id);
    
    // Change texture scale mode
    void setScaleMode(uint32_t id, SDL_ScaleMode mode);
    
    // Get texture dimensions
    SDL_FRect getTextureDimensions(uint32_t id);
    
    // Check if texture exists
    bool hasTexture(uint32_t id) const;
    
    // Unload texture (for advanced memory management)
    void unloadTexture(uint32_t id);
    
    // Get number of loaded textures
    size_t getTextureCount() const;
};
```

### SpriteEntityFactory

Factory class for creating different types of sprite entities.

```cpp
class SpriteEntityFactory {
public:
    explicit SpriteEntityFactory(TextureManager* tm);
    
    // Create a simple static sprite
    entt::entity createStaticSprite(entt::registry& registry, 
                                   const std::string& texturePath,
                                   float x, float y, int layer = 0);
    
    // Create an animated sprite
    entt::entity createAnimatedSprite(entt::registry& registry,
                                     const std::string& texturePath,
                                     float x, float y,
                                     uint32_t frameCount, float frameTime,
                                     int layer = 0);
    
    // Create a sprite with scaling
    entt::entity createScaledSprite(entt::registry& registry,
                                   const std::string& texturePath,
                                   float x, float y,
                                   float scaleX, float scaleY,
                                   int layer = 0);
    
    // Create sprite from texture atlas
    entt::entity createSpriteFromAtlas(entt::registry& registry,
                                      const std::string& texturePath,
                                      float x, float y,
                                      SDL_FRect sourceRect,
                                      int layer = 0);
    
    // Clone an existing sprite
    entt::entity cloneSprite(entt::registry& registry, entt::entity original,
                            float newX, float newY);
};
```

### AnimationSystem

Handles sprite animation updates.

```cpp
class AnimationSystem {
public:
    void update(entt::registry& registry, float deltaTime);
};
```

### RenderSystem

Manages efficient batch rendering of sprites with layer sorting.

```cpp
class RenderSystem {
public:
    explicit RenderSystem(TextureManager* tm);
    
    void render(entt::registry& registry, WindowRender* renderer);
};
```

### SpriteManager

Main manager class that coordinates all sprite-related systems.

```cpp
class SpriteManager {
public:
    explicit SpriteManager(WindowRender* win);
    
    // Accessors
    TextureManager* getTextureManager();
    SpriteEntityFactory* getFactory();
    
    // Update and render
    void update(entt::registry& registry, float deltaTime);
    void render(entt::registry& registry);
    
    // Debug statistics
    void printStats(entt::registry& registry);
    size_t getLoadedTextureCount() const;
    
    // Cleanup
    void cleanup();
};
```

## Utility Functions

### SpriteUtils Namespace

```cpp
namespace SpriteUtils {
    // Calculate sprite center
    SDL_FPoint getSpriteCenter(entt::registry& registry, entt::entity entity);
    
    // Check if sprite is visible on screen
    bool isSpriteOnScreen(const Position& pos, const SpriteComponent& sprite,
                         float screenWidth, float screenHeight);
    
    // Calculate distance between two sprites
    float getDistanceBetweenSprites(entt::registry& registry, 
                                   entt::entity entity1, entt::entity entity2);
    
    // Change sprite visibility
    void setSpriteVisible(entt::registry& registry, entt::entity entity, bool visible);
    
    // Change sprite layer
    void setSpriteLayer(entt::registry& registry, entt::entity entity, int layer);
}
```

## Example Usage

```cpp
#include <ecs_sprite/ecs_sprite.hpp>
#include <window_render/window_render.hpp>
#include <entt/entt.hpp>
#include <SDL3/SDL.h>
#include <iostream>

int main() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    
    // Create window and renderer
    WindowRender window("Sprite Demo", 1024, 768);
    if (!window.initialize()) {
        std::cerr << "Failed to initialize window" << std::endl;
        return -1;
    }
    
    // Create ECS registry and sprite manager
    entt::registry registry;
    SpriteManager spriteManager(&window);
    
    // Get factory for creating sprites
    SpriteEntityFactory* factory = spriteManager.getFactory();
    
    // === CREATING DIFFERENT TYPES OF SPRITES ===
    
    // 1. Static sprite (background)
    entt::entity background = factory->createStaticSprite(
        registry, 
        "assets/background.png", 
        0, 0,           // position
        -1              // layer (background)
    );
    
    // 2. Animated sprite (character walking)
    entt::entity player = factory->createAnimatedSprite(
        registry,
        "assets/player_walk.png",  // sprite sheet with 8 frames
        400, 300,                  // position
        8,                         // frame count
        0.1f,                      // 0.1 seconds per frame
        1                          // layer (foreground)
    );
    
    // 3. Scaled sprite (large enemy)
    entt::entity boss = factory->createScaledSprite(
        registry,
        "assets/enemy.png",
        600, 200,       // position
        2.0f, 2.0f,     // 2x scale
        1               // layer
    );
    
    // 4. Sprite from texture atlas
    SDL_FRect coinRect = {0, 0, 32, 32}; // 32x32 coin in atlas
    entt::entity coin = factory->createSpriteFromAtlas(
        registry,
        "assets/items_atlas.png",
        300, 400,       // position
        coinRect,       // source rectangle
        0               // layer
    );
    
    // 5. Clone sprites (multiple coins)
    std::vector<entt::entity> coins;
    for (int i = 0; i < 5; i++) {
        entt::entity clonedCoin = factory->cloneSprite(
            registry, 
            coin, 
            300 + i * 40, 400
        );
        coins.push_back(clonedCoin);
    }
    
    // === SPRITE MANIPULATION ===
    
    // Change sprite properties
    SpriteUtils::setSpriteLayer(registry, boss, 2); // Move boss to top layer
    SpriteUtils::setSpriteVisible(registry, coin, false); // Hide original coin
    
    // Modify position directly
    auto& playerPos = registry.get<Position>(player);
    playerPos.x = 100;
    playerPos.y = 200;
    
    // Modify animation
    auto& playerAnim = registry.get<AnimationComponent>(player);
    playerAnim.frameTime = 0.05f; // Faster animation
    
    // === MAIN GAME LOOP ===
    
    bool running = true;
    SDL_Event event;
    Uint64 lastTime = SDL_GetPerformanceCounter();
    
    while (running) {
        // Calculate delta time
        Uint64 currentTime = SDL_GetPerformanceCounter();
        float deltaTime = (float)(currentTime - lastTime) / SDL_GetPerformanceFrequency();
        lastTime = currentTime;
        
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            
            // Move player with arrow keys
            if (event.type == SDL_EVENT_KEY_DOWN) {
                auto& pos = registry.get<Position>(player);
                switch (event.key.scancode) {
                    case SDL_SCANCODE_LEFT:
                        pos.x -= 10;
                        break;
                    case SDL_SCANCODE_RIGHT:
                        pos.x += 10;
                        break;
                    case SDL_SCANCODE_UP:
                        pos.y -= 10;
                        break;
                    case SDL_SCANCODE_DOWN:
                        pos.y += 10;
                        break;
                }
            }
        }
        
        // === GAME LOGIC ===
        
        // Animate boss scaling
        auto& bossTransform = registry.get<Transform>(boss);
        bossTransform.scaleX = 2.0f + sin(SDL_GetTicks() * 0.001f) * 0.5f;
        bossTransform.scaleY = 2.0f + cos(SDL_GetTicks() * 0.001f) * 0.5f;
        
        // Rotate coins
        for (auto coinEntity : coins) {
            auto& coinPos = registry.get<Position>(coinEntity);
            coinPos.rotation += deltaTime * 90.0f; // 90 degrees per second
        }
        
        // Check collision between player and coins
        for (auto it = coins.begin(); it != coins.end();) {
            float distance = SpriteUtils::getDistanceBetweenSprites(registry, player, *it);
            if (distance < 30.0f) {
                registry.destroy(*it);
                it = coins.erase(it);
                std::cout << "Coin collected!" << std::endl;
            } else {
                ++it;
            }
        }
        
        // === UPDATE AND RENDER ===
        
        // Update sprite systems
        spriteManager.update(registry, deltaTime);
        
        // Clear screen
        window.clear(0, 0, 50, 255); // Dark blue background
        
        // Render all sprites
        spriteManager.render(registry);
        
        // Present to screen
        window.present();
        
        // Print stats every 3 seconds
        static Uint32 lastStatsTime = 0;
        if (SDL_GetTicks() - lastStatsTime > 3000) {
            spriteManager.printStats(registry);
            lastStatsTime = SDL_GetTicks();
        }
        
        SDL_Delay(16); // ~60 FPS
    }
    
    // === CLEANUP ===
    
    spriteManager.cleanup();
    window.shutdown();
    SDL_Quit();
    
    return 0;
}
```

## Advanced Usage Examples

### Custom Animation Control

```cpp
// Pause/resume animation
auto& anim = registry.get<AnimationComponent>(entity);
anim.playing = false; // Pause
anim.playing = true;  // Resume

// Change animation speed
anim.frameTime = 0.05f; // Faster
anim.frameTime = 0.2f;  // Slower

// Non-looping animation
anim.loop = false;

// Check if animation finished
if (!anim.playing && !anim.loop) {
    std::cout << "Animation finished!" << std::endl;
}
```

### Performance Optimization

```cpp
// Cull off-screen sprites
auto view = registry.view<Position, SpriteComponent>();
for (auto [entity, pos, sprite] : view.each()) {
    if (!SpriteUtils::isSpriteOnScreen(pos, sprite, 1024, 768)) {
        SpriteUtils::setSpriteVisible(registry, entity, false);
    }
}

// Batch similar operations
std::vector<entt::entity> enemies;
// ... populate enemies vector

// Move all enemies at once
for (auto enemy : enemies) {
    auto& pos = registry.get<Position>(enemy);
    pos.y += enemySpeed * deltaTime;
}
```

### Layer Management

```cpp
// Define layer constants
const int LAYER_BACKGROUND = -2;
const int LAYER_TERRAIN = -1;
const int LAYER_OBJECTS = 0;
const int LAYER_CHARACTERS = 1;
const int LAYER_EFFECTS = 2;
const int LAYER_UI = 3;

// Organize sprites by layers
SpriteUtils::setSpriteLayer(registry, background, LAYER_BACKGROUND);
SpriteUtils::setSpriteLayer(registry, player, LAYER_CHARACTERS);
SpriteUtils::setSpriteLayer(registry, explosion, LAYER_EFFECTS);
```

## Notes

- The sprite manager must be updated every frame with `update()` for animations to work.
- Sprites are automatically batched by texture for efficient rendering.
- Layer sorting is performed automatically - lower layer numbers render first.
- Texture loading is cached - loading the same file multiple times returns the same ID.
- All sprite operations are thread-safe when called from the main thread.
- The system uses `SDL_FRect` for sub-pixel positioning and precise rendering.
- Memory management is automatic - textures are cleaned up when the TextureManager is destroyed.
- For best performance, group sprites by texture and minimize texture switches.