# ECS Collision Module (for EnTT)
Provides a complete collision detection and response system using Entity-Component-System architecture.

## Dependencies
- EnTT (Entity-Component-System library)
- SDL3 (for collision rectangles)
- ecs_sprite (for Position component)

## Components

### Velocity
```cpp
struct Velocity {
    float vx = 0.0f, vy = 0.0f;
    
    Velocity(float x = 0.0f, float y = 0.0f); // Constructor
};
```

### CollisionBox
```cpp
struct CollisionBox {
    float width, height;
    float offsetX = 0.0f, offsetY = 0.0f;  // Offset from entity position
    bool isTrigger = false;                // True for trigger zones (no physics response)
    
    CollisionBox(float w, float h, float ox = 0.0f, float oy = 0.0f);
};
```

### CollisionTag
```cpp
struct CollisionTag {
    std::string tag;
    
    CollisionTag(const std::string& t);
};
```

### CollisionResponse
```cpp
struct CollisionResponse {
    std::unordered_set<std::string> allowedCollisions;
    
    bool canCollideWith(const std::string& otherTag) const;
};
```

## Collision Event

### CollisionEvent
```cpp
struct CollisionEvent {
    entt::entity entityA;
    entt::entity entityB;
    std::string tagA;
    std::string tagB;
    float penetrationX, penetrationY;
    bool isTrigger;
    
    CollisionEvent(entt::entity a, entt::entity b, const std::string& tA, const std::string& tB,
                   float penX, float penY, bool trigger);
};
```

## Systems

### CollisionSystem

```cpp
// Create a CollisionSystem instance
CollisionSystem collision_system = CollisionSystem();

// Update positions and detect collisions
collision_system.update(entt::registry& registry, float deltaTime); // return void

// Set callback for collision events
collision_system.setOnCollision(std::function<void(const CollisionEvent&)> callback); // return void

// Configure which tags can collide with each other
collision_system.configureCollision(const std::string& tagA, const std::string& tagB); // return void

// Remove collision configuration
collision_system.removeCollisionConfig(const std::string& tagA, const std::string& tagB); // return void

// Check if two tags can collide
collision_system.canTagsCollide(const std::string& tagA, const std::string& tagB); // return bool

// Get collision bounds for an entity
collision_system.getCollisionBounds(entt::registry& registry, entt::entity entity); // return SDL_FRect

// Check AABB collision between two rectangles
collision_system.checkAABBCollision(const SDL_FRect& a, const SDL_FRect& b, float& penX, float& penY); // return bool
```

## Collision Manager

### CollisionManager

```cpp
// Create a CollisionManager instance
CollisionManager collision_manager = CollisionManager();

// Get the collision system
collision_manager.getCollisionSystem(); // return CollisionSystem&

// Update collision system
collision_manager.update(entt::registry& registry, float deltaTime); // return void

// Create a static collision entity
collision_manager.createCollisionEntity(entt::registry& registry, float x, float y,
                                       float width, float height, const std::string& tag); // return entt::entity

// Create a moving collision entity
collision_manager.createMovingEntity(entt::registry& registry, float x, float y,
                                    float width, float height, const std::string& tag,
                                    float vx = 0.0f, float vy = 0.0f); // return entt::entity

// Create a trigger zone (no physics response)
collision_manager.createTriggerZone(entt::registry& registry, float x, float y,
                                   float width, float height, const std::string& tag); // return entt::entity

// Set entity velocity
collision_manager.setEntityVelocity(entt::registry& registry, entt::entity entity, float vx, float vy); // return void

// Add collision response to entity
collision_manager.addCollisionResponse(entt::registry& registry, entt::entity entity, const std::string& allowedTag); // return void
```

## Utilities (CollisionUtils namespace)

```cpp
// Check if a point is inside a collision box
CollisionUtils::isPointInBounds(float x, float y, const SDL_FRect& bounds); // return bool

// Get distance between two entities
CollisionUtils::getDistanceBetween(entt::registry& registry, entt::entity entityA, entt::entity entityB); // return float

// Move entity safely (checks for collisions)
CollisionUtils::moveEntitySafe(entt::registry& registry, entt::entity entity, float deltaX, float deltaY,
                               CollisionSystem& collisionSystem); // return bool

// Get all entities with a specific collision tag
CollisionUtils::getEntitiesWithTag(entt::registry& registry, const std::string& tag); // return std::vector<entt::entity>

// Check if entity has collision components
CollisionUtils::hasCollisionComponents(entt::registry& registry, entt::entity entity); // return bool
```

## EXAMPLE:

```cpp
#include <ecs_collisions/ecs_collisions.hpp>
#include <entt/entt.hpp>

int main() {
    entt::registry registry;
    ECSCollision::CollisionManager collision_manager;
    
    // Configure collision rules
    collision_manager.getCollisionSystem().configureCollision("player", "wall");
    collision_manager.getCollisionSystem().configureCollision("player", "enemy");
    collision_manager.getCollisionSystem().configureCollision("bullet", "enemy");
    
    // Create entities
    auto player = collision_manager.createMovingEntity(registry, 100, 100, 32, 32, "player", 0, 0);
    auto wall = collision_manager.createCollisionEntity(registry, 200, 100, 64, 64, "wall");
    auto trigger = collision_manager.createTriggerZone(registry, 300, 100, 48, 48, "powerup");
    
    // Set collision callback
    collision_manager.getCollisionSystem().setOnCollision([](const ECSCollision::CollisionEvent& event) {
        if (event.tagA == "player" && event.tagB == "powerup") {
            std::cout << "Player collected powerup!" << std::endl;
        }
    });
    
    // Game loop
    bool isRunning = true;
    float deltaTime = 0.016f; // 60 FPS
    
    while (isRunning) {
        // Handle input and set player velocity
        collision_manager.setEntityVelocity(registry, player, 100.0f, 0.0f); // Move right
        
        // Update collision system
        collision_manager.update(registry, deltaTime);
        
        // Other game logic...
        
        SDL_Delay(16);
    }
    
    return 0;
}
```