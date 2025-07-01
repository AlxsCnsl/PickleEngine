#pragma once
#include <entt/entt.hpp>
#include <window_render/window_render.hpp>
#include <SDL3_image/SDL_image.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

// ========== COMPOSANTS ==========

struct Position {
    float x, y;
    float rotation = 0.0f;
    
    Position(float x = 0, float y = 0);
};

struct Transform {
    float scaleX = 1.0f, scaleY = 1.0f;
    
    Transform(float sx = 1.0f, float sy = 1.0f);
};

struct SpriteComponent {
    uint32_t textureId;           // ID de la texture dans le TextureManager
    SDL_FRect sourceRect;         // Rectangle source dans la texture (pour sprite sheets)
    bool visible = true;
    int layer = 0;                // Ordre de rendu (z-order)
    
    SpriteComponent(uint32_t id, SDL_FRect src = {0, 0, 0, 0});
};

struct AnimationComponent {
    uint32_t currentFrame = 0;
    uint32_t frameCount;
    float frameTime;              // Temps par frame
    float currentTime = 0.0f;
    bool loop = true;
    bool playing = true;
    
    AnimationComponent(uint32_t frames, float time);
};

// ========== GESTIONNAIRE DE TEXTURES ==========

class TextureManager {
private:
    std::unordered_map<std::string, uint32_t> pathToId;
    std::unordered_map<uint32_t, SDL_Texture*> textures;
    std::unordered_map<uint32_t, SDL_ScaleMode> scaleModes;
    uint32_t nextId = 1;
    WindowRender* renderer;

public:
    explicit TextureManager(WindowRender* win);
    ~TextureManager();
    
    // Charge une texture et retourne son ID
    uint32_t loadTexture(const std::string& path, SDL_ScaleMode scaleMode = SDL_SCALEMODE_LINEAR);
    
    // Récupère une texture par son ID
    SDL_Texture* getTexture(uint32_t id);
    
    // Change le mode de mise à l'échelle d'une texture
    void setScaleMode(uint32_t id, SDL_ScaleMode mode);
    
    // Obtient les dimensions d'une texture
    SDL_FRect getTextureDimensions(uint32_t id);
    
    // Vérifie si une texture existe
    bool hasTexture(uint32_t id) const;
    
    // Décharge une texture (optionnel, pour gestion mémoire avancée)
    void unloadTexture(uint32_t id);
    
    // Obtient le nombre de textures chargées
    size_t getTextureCount() const;
};

// ========== SYSTEME D'ANIMATION ==========

class AnimationSystem {
public:
    void update(entt::registry& registry, float deltaTime);
    
private:
    void updateFrameRect(SpriteComponent& sprite, const AnimationComponent& anim);
};

// ========== SYSTEME DE RENDU ==========

class RenderSystem {
private:
    TextureManager* textureManager;
    
public:
    explicit RenderSystem(TextureManager* tm);
    
    void render(entt::registry& registry, WindowRender* renderer);
    
private:
    void renderBatched(entt::registry& registry, WindowRender* renderer, 
                      const std::vector<entt::entity>& entities);
    
    void renderBatch(WindowRender* renderer, uint32_t textureId,
                    const std::vector<SDL_FRect>& srcRects,
                    const std::vector<SDL_FRect>& destRects);
    
    SDL_FRect calculateDestRect(entt::registry& registry, entt::entity entity,
                               const Position& pos, const SpriteComponent& sprite);
    
    std::vector<entt::entity> collectVisibleEntities(entt::registry& registry);
    
    void sortEntitiesByLayer(entt::registry& registry, std::vector<entt::entity>& entities);
};

// ========== FACTORY POUR CREATION D'ENTITES ==========

class SpriteEntityFactory {
private:
    TextureManager* textureManager;
    
public:
    explicit SpriteEntityFactory(TextureManager* tm);
    
    // Crée un sprite statique simple
    entt::entity createStaticSprite(entt::registry& registry, 
                                   const std::string& texturePath,
                                   float x, float y, int layer = 0);
    
    // Crée un sprite animé
    entt::entity createAnimatedSprite(entt::registry& registry,
                                     const std::string& texturePath,
                                     float x, float y,
                                     uint32_t frameCount, float frameTime,
                                     int layer = 0);
    
    // Crée un sprite avec transformation
    entt::entity createScaledSprite(entt::registry& registry,
                                   const std::string& texturePath,
                                   float x, float y,
                                   float scaleX, float scaleY,
                                   int layer = 0);
    
    // Crée un sprite avec rectangle source personnalisé
    entt::entity createSpriteFromAtlas(entt::registry& registry,
                                      const std::string& texturePath,
                                      float x, float y,
                                      SDL_FRect sourceRect,
                                      int layer = 0);
    
    // Crée une copie d'un sprite existant
    entt::entity cloneSprite(entt::registry& registry, entt::entity original,
                            float newX, float newY);
};

// ========== UTILITAIRES ==========

namespace SpriteUtils {
    // Calcule le centre d'un sprite
    SDL_FPoint getSpriteCenter(entt::registry& registry, entt::entity entity);
    
    // Vérifie si un sprite est visible à l'écran
    bool isSpriteOnScreen(const Position& pos, const SpriteComponent& sprite,
                         float screenWidth, float screenHeight);
    
    // Calcule la distance entre deux sprites
    float getDistanceBetweenSprites(entt::registry& registry, 
                                   entt::entity entity1, entt::entity entity2);
    
    // Change la visibilité d'un sprite
    void setSpriteVisible(entt::registry& registry, entt::entity entity, bool visible);
    
    // Change le layer d'un sprite
    void setSpriteLayer(entt::registry& registry, entt::entity entity, int layer);
}

// ========== GESTIONNAIRE PRINCIPAL ==========

class SpriteManager {
private:
    TextureManager textureManager;
    SpriteEntityFactory factory;
    AnimationSystem animationSystem;
    RenderSystem renderSystem;
    WindowRender* window;
    
public:
    explicit SpriteManager(WindowRender* win);
    
    // Accesseurs
    TextureManager* getTextureManager();
    SpriteEntityFactory* getFactory();
    
    // Mise à jour et rendu
    void update(entt::registry& registry, float deltaTime);
    void render(entt::registry& registry);
    
    // Statistiques de debug
    void printStats(entt::registry& registry);
    size_t getLoadedTextureCount() const;
    
    // Nettoyage
    void cleanup();
};