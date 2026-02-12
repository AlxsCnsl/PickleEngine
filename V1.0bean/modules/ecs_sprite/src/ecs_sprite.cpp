#include <ecs_sprite/ecs_sprite.hpp>
#include <iostream>
#include <cmath>

// ========== COMPOSANTS ==========

Position::Position(float x, float y) : x(x), y(y) {}

Transform::Transform(float sx, float sy) : scaleX(sx), scaleY(sy) {}

SpriteComponent::SpriteComponent(uint32_t id, SDL_FRect src) 
    : textureId(id), sourceRect(src) {}

AnimationComponent::AnimationComponent(uint32_t frames, float time) 
    : frameCount(frames), frameTime(time) {}

// ========== GESTIONNAIRE DE TEXTURES ==========

TextureManager::TextureManager(WindowRender* win) : renderer(win) {}

TextureManager::~TextureManager() {
    for (auto& [id, texture] : textures) {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
    textures.clear();
    pathToId.clear();
    scaleModes.clear();
}

uint32_t TextureManager::loadTexture(const std::string& path, SDL_ScaleMode scaleMode) {
    // Vérifier si déjà chargée
    auto it = pathToId.find(path);
    if (it != pathToId.end()) {
        return it->second;
    }
    
    // Charger la nouvelle texture
    SDL_Texture* texture = IMG_LoadTexture(renderer->getRenderer(), path.c_str());
    if (!texture) {
        std::cerr << "Erreur chargement texture " << path << ": " << SDL_GetError() << std::endl;
        return 0; // ID invalide
    }
    
    SDL_SetTextureScaleMode(texture, scaleMode);
    
    uint32_t id = nextId++;
    pathToId[path] = id;
    textures[id] = texture;
    scaleModes[id] = scaleMode;
    
    return id;
}

SDL_Texture* TextureManager::getTexture(uint32_t id) {
    auto it = textures.find(id);
    return (it != textures.end()) ? it->second : nullptr;
}

void TextureManager::setScaleMode(uint32_t id, SDL_ScaleMode mode) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        SDL_SetTextureScaleMode(it->second, mode);
        scaleModes[id] = mode;
    }
}

SDL_FRect TextureManager::getTextureDimensions(uint32_t id) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        float w, h;
        SDL_GetTextureSize(it->second, &w, &h);
        return {0, 0, w, h};
    }
    return {0, 0, 0, 0};
}

bool TextureManager::hasTexture(uint32_t id) const {
    return textures.find(id) != textures.end();
}

void TextureManager::unloadTexture(uint32_t id) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        SDL_DestroyTexture(it->second);
        textures.erase(it);
        scaleModes.erase(id);
        
        // Supprimer de pathToId aussi
        for (auto pathIt = pathToId.begin(); pathIt != pathToId.end(); ++pathIt) {
            if (pathIt->second == id) {
                pathToId.erase(pathIt);
                break;
            }
        }
    }
}

size_t TextureManager::getTextureCount() const {
    return textures.size();
}

// ========== SYSTEME D'ANIMATION ==========

void AnimationSystem::update(entt::registry& registry, float deltaTime) {
    auto view = registry.view<SpriteComponent, AnimationComponent>();
    
    for (auto [entity, sprite, anim] : view.each()) {
        if (!anim.playing) continue;
        
        anim.currentTime += deltaTime;
        
        if (anim.currentTime >= anim.frameTime) {
            anim.currentTime = 0.0f;
            anim.currentFrame++;
            
            if (anim.currentFrame >= anim.frameCount) {
                if (anim.loop) {
                    anim.currentFrame = 0;
                } else {
                    anim.currentFrame = anim.frameCount - 1;
                    anim.playing = false;
                }
            }
            
            updateFrameRect(sprite, anim);
        }
    }
}

void AnimationSystem::updateFrameRect(SpriteComponent& sprite, const AnimationComponent& anim) {
    // Assuming horizontal sprite sheet
    float totalWidth = sprite.sourceRect.w * anim.frameCount;
    float frameWidth = totalWidth / anim.frameCount;
    sprite.sourceRect.x = anim.currentFrame * frameWidth;
    sprite.sourceRect.w = frameWidth;
}

// ========== SYSTEME DE RENDU ==========

RenderSystem::RenderSystem(TextureManager* tm) : textureManager(tm) {}

void RenderSystem::render(entt::registry& registry, WindowRender* renderer) {
    std::vector<entt::entity> renderQueue = collectVisibleEntities(registry);
    sortEntitiesByLayer(registry, renderQueue);
    renderBatched(registry, renderer, renderQueue);
}

std::vector<entt::entity> RenderSystem::collectVisibleEntities(entt::registry& registry) {
    std::vector<entt::entity> entities;
    
    auto view = registry.view<Position, SpriteComponent>();
    view.each([&](auto entity, auto& pos, auto& sprite) {
        if (sprite.visible && textureManager->hasTexture(sprite.textureId)) {
            entities.push_back(entity);
        }
    });
    
    return entities;
}

void RenderSystem::sortEntitiesByLayer(entt::registry& registry, std::vector<entt::entity>& entities) {
    std::sort(entities.begin(), entities.end(), 
        [&registry](entt::entity a, entt::entity b) {
            auto& spriteA = registry.get<SpriteComponent>(a);
            auto& spriteB = registry.get<SpriteComponent>(b);
            return spriteA.layer < spriteB.layer;
        });
}

void RenderSystem::renderBatched(entt::registry& registry, WindowRender* renderer, 
                                const std::vector<entt::entity>& entities) {
    
    if (entities.empty()) return;
    
    uint32_t currentTexture = 0;
    std::vector<SDL_FRect> srcRects, destRects;
    
    for (auto entity : entities) {
        auto& pos = registry.get<Position>(entity);
        auto& sprite = registry.get<SpriteComponent>(entity);
        
        // Si changement de texture, rendre le batch précédent
        if (currentTexture != 0 && currentTexture != sprite.textureId) {
            renderBatch(renderer, currentTexture, srcRects, destRects);
            srcRects.clear();
            destRects.clear();
        }
        
        currentTexture = sprite.textureId;
        
        // Calculer les rectangles
        SDL_FRect destRect = calculateDestRect(registry, entity, pos, sprite);
        SDL_FRect srcRect = sprite.sourceRect;
        
        // Si sourceRect est vide, utiliser toute la texture
        if (srcRect.w == 0 || srcRect.h == 0) {
            srcRect = textureManager->getTextureDimensions(sprite.textureId);
        }
        
        srcRects.push_back(srcRect);
        destRects.push_back(destRect);
    }
    
    // Rendre le dernier batch
    if (!srcRects.empty()) {
        renderBatch(renderer, currentTexture, srcRects, destRects);
    }
}

void RenderSystem::renderBatch(WindowRender* renderer, uint32_t textureId,
                              const std::vector<SDL_FRect>& srcRects,
                              const std::vector<SDL_FRect>& destRects) {
    
    SDL_Texture* texture = textureManager->getTexture(textureId);
    if (!texture || srcRects.empty()) return;
    
    // Rendu individuel pour chaque sprite (SDL3 n'a pas encore de batch rendering natif)
    for (size_t i = 0; i < srcRects.size(); ++i) {
        SDL_RenderTexture(renderer->getRenderer(), texture, &srcRects[i], &destRects[i]);
    }
}

SDL_FRect RenderSystem::calculateDestRect(entt::registry& registry, entt::entity entity,
                                         const Position& pos, const SpriteComponent& sprite) {
    
    SDL_FRect rect = {pos.x, pos.y, sprite.sourceRect.w, sprite.sourceRect.h};
    
    // Si sourceRect est vide, utiliser la taille complète de la texture
    if (sprite.sourceRect.w == 0 || sprite.sourceRect.h == 0) {
        SDL_FRect texDim = textureManager->getTextureDimensions(sprite.textureId);
        rect.w = texDim.w;
        rect.h = texDim.h;
    }
    
    // Appliquer la transformation si elle existe
    if (registry.all_of<Transform>(entity)) {
        auto& transform = registry.get<Transform>(entity);
        rect.w *= transform.scaleX;
        rect.h *= transform.scaleY;
    }
    
    return rect;
}

// ========== FACTORY POUR CREATION D'ENTITES ==========

SpriteEntityFactory::SpriteEntityFactory(TextureManager* tm) : textureManager(tm) {}

entt::entity SpriteEntityFactory::createStaticSprite(entt::registry& registry, 
                                                     const std::string& texturePath,
                                                     float x, float y, int layer) {
    auto entity = registry.create();
    
    uint32_t textureId = textureManager->loadTexture(texturePath);
    if (textureId == 0) {
        registry.destroy(entity);
        return entt::null;
    }
    
    SDL_FRect texDim = textureManager->getTextureDimensions(textureId);
    
    registry.emplace<Position>(entity, x, y);
    registry.emplace<SpriteComponent>(entity, textureId, texDim);
    registry.get<SpriteComponent>(entity).layer = layer;
    
    return entity;
}

entt::entity SpriteEntityFactory::createAnimatedSprite(entt::registry& registry,
                                                       const std::string& texturePath,
                                                       float x, float y,
                                                       uint32_t frameCount, float frameTime,
                                                       int layer) {
    auto entity = createStaticSprite(registry, texturePath, x, y, layer);
    if (entity == entt::null) return entt::null;
    
    // Configurer l'animation
    auto& sprite = registry.get<SpriteComponent>(entity);
    float originalWidth = sprite.sourceRect.w;
    sprite.sourceRect.w = originalWidth / frameCount; // Largeur d'une frame
    
    registry.emplace<AnimationComponent>(entity, frameCount, frameTime);
    
    return entity;
}

entt::entity SpriteEntityFactory::createScaledSprite(entt::registry& registry,
                                                     const std::string& texturePath,
                                                     float x, float y,
                                                     float scaleX, float scaleY,
                                                     int layer) {
    auto entity = createStaticSprite(registry, texturePath, x, y, layer);
    if (entity == entt::null) return entt::null;
    
    registry.emplace<Transform>(entity, scaleX, scaleY);
    
    return entity;
}

entt::entity SpriteEntityFactory::createSpriteFromAtlas(entt::registry& registry,
                                                        const std::string& texturePath,
                                                        float x, float y,
                                                        SDL_FRect sourceRect,
                                                        int layer) {
    auto entity = registry.create();
    
    uint32_t textureId = textureManager->loadTexture(texturePath);
    if (textureId == 0) {
        registry.destroy(entity);
        return entt::null;
    }
    
    registry.emplace<Position>(entity, x, y);
    registry.emplace<SpriteComponent>(entity, textureId, sourceRect);
    registry.get<SpriteComponent>(entity).layer = layer;
    
    return entity;
}

entt::entity SpriteEntityFactory::cloneSprite(entt::registry& registry, entt::entity original,
                                              float newX, float newY) {
    if (!registry.valid(original)) return entt::null;
    
    auto newEntity = registry.create();
    
    // Copier Position
    if (registry.all_of<Position>(original)) {
        registry.emplace<Position>(newEntity, newX, newY);
    }
    
    // Copier SpriteComponent
    if (registry.all_of<SpriteComponent>(original)) {
        auto& originalSprite = registry.get<SpriteComponent>(original);
        registry.emplace<SpriteComponent>(newEntity, originalSprite);
    }
    
    // Copier Transform si existant
    if (registry.all_of<Transform>(original)) {
        auto& originalTransform = registry.get<Transform>(original);
        registry.emplace<Transform>(newEntity, originalTransform);
    }
    
    // Copier AnimationComponent si existant
    if (registry.all_of<AnimationComponent>(original)) {
        auto& originalAnim = registry.get<AnimationComponent>(original);
        registry.emplace<AnimationComponent>(newEntity, originalAnim);
    }
    
    return newEntity;
}

// ========== UTILITAIRES ==========

namespace SpriteUtils {
    
    SDL_FPoint getSpriteCenter(entt::registry& registry, entt::entity entity) {
        if (!registry.all_of<Position, SpriteComponent>(entity)) {
            return {0, 0};
        }
        
        auto& pos = registry.get<Position>(entity);
        auto& sprite = registry.get<SpriteComponent>(entity);
        
        float width = sprite.sourceRect.w;
        float height = sprite.sourceRect.h;
        
        if (registry.all_of<Transform>(entity)) {
            auto& transform = registry.get<Transform>(entity);
            width *= transform.scaleX;
            height *= transform.scaleY;
        }
        
        return {pos.x + width / 2.0f, pos.y + height / 2.0f};
    }
    
    bool isSpriteOnScreen(const Position& pos, const SpriteComponent& sprite,
                         float screenWidth, float screenHeight) {
        return !(pos.x + sprite.sourceRect.w < 0 || 
                pos.x > screenWidth ||
                pos.y + sprite.sourceRect.h < 0 || 
                pos.y > screenHeight);
    }
    
    float getDistanceBetweenSprites(entt::registry& registry, 
                                   entt::entity entity1, entt::entity entity2) {
        SDL_FPoint center1 = getSpriteCenter(registry, entity1);
        SDL_FPoint center2 = getSpriteCenter(registry, entity2);
        
        float dx = center1.x - center2.x;
        float dy = center1.y - center2.y;
        
        return std::sqrt(dx * dx + dy * dy);
    }
    
    void setSpriteVisible(entt::registry& registry, entt::entity entity, bool visible) {
        if (registry.all_of<SpriteComponent>(entity)) {
            registry.get<SpriteComponent>(entity).visible = visible;
        }
    }
    
    void setSpriteLayer(entt::registry& registry, entt::entity entity, int layer) {
        if (registry.all_of<SpriteComponent>(entity)) {
            registry.get<SpriteComponent>(entity).layer = layer;
        }
    }
}

// ========== GESTIONNAIRE PRINCIPAL ==========

SpriteManager::SpriteManager(WindowRender* win) 
    : textureManager(win), factory(&textureManager), renderSystem(&textureManager), window(win) {}

TextureManager* SpriteManager::getTextureManager() {
    return &textureManager;
}

SpriteEntityFactory* SpriteManager::getFactory() {
    return &factory;
}

void SpriteManager::update(entt::registry& registry, float deltaTime) {
    animationSystem.update(registry, deltaTime);
}

void SpriteManager::render(entt::registry& registry) {
    renderSystem.render(registry, window);
}

void SpriteManager::printStats(entt::registry& registry) {
    auto spriteView = registry.view<SpriteComponent>();
    auto animView = registry.view<AnimationComponent>();
    
    std::cout << "=== SPRITE STATS ===" << std::endl;
    std::cout << "Textures chargées: " << textureManager.getTextureCount() << std::endl;
    std::cout << "Sprites total: " << spriteView.size() << std::endl;
    std::cout << "Sprites animés: " << animView.size() << std::endl;
    
    // Compter sprites visibles
    size_t visibleCount = 0;
    for (auto entity : spriteView) {
        if (spriteView.get<SpriteComponent>(entity).visible) {
            visibleCount++;
        }
    }
    std::cout << "Sprites visibles: " << visibleCount << std::endl;
}

size_t SpriteManager::getLoadedTextureCount() const {
    return textureManager.getTextureCount();
}

void SpriteManager::cleanup() {
    // Le destructeur de TextureManager s'occupe du nettoyage
}