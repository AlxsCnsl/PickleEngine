#pragma once

#include <entt/entt.hpp>
#include <SDL3/SDL.h>
#include<ecs_sprite/ecs_sprite.hpp>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <functional>

// ================================ COMPONENTS ================================

struct AABBComponent{
    uint32_t width, height;

    AABBComponent(u_int32_t w, u_int32_t h);
};

struct TagComponent {
    std::unordered_set<uint32_t> tags_id;
};

// ================================ COLLISION SYSTEM ================================

class CollisionSystem{
    public:

    private:
};

// ================================ COLLIDER ENTITY FACTORY ================================

class ColliderEntityFactory{
    public:

    private:
};

// ================================ TAG TOOLS ================================

class TagTools{

};

// ================================ COLLISION MANAGER ================================

class CollisionManager{
    public:
        TagTools tagtools;
        ColliderEntityFactory factory;

    private: 
};