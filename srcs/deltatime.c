//deltatime.c===
#include"../headers/deltatime.h"

DeltaTime* dt = NULL;

void initDeltaTime() {
    dt = (DeltaTime*)malloc(sizeof(DeltaTime));
    dt->lastTime = SDL_GetTicks();
    dt->lastFPSUpdate = dt->lastTime;
    dt->deltaTime = 0.0f;
    dt->frameCount = 0;
    dt->fps = 0;
}

void updateDeltaTime() {
    Uint32 currentTime = SDL_GetTicks();
    int frameTime = SDL_GetTicks() - currentTime;
    dt->deltaTime = (currentTime - dt->lastTime) / 1000.0f; // Temps écoulé en secondes
    dt->lastTime = currentTime;

    //limite le nombre de FPS
    if (dt->deltaTime > 0.1f) {
    dt->deltaTime = 0.1f;
    }

    if (frameTime < 1000 / win_parameter->max_fps) {
    SDL_Delay((1000 / win_parameter->max_fps) - frameTime);
    }
    
    // Mettre à jour le compteur de frames
    dt->frameCount++;
    
    // Calculer les FPS toutes les secondes
    if (currentTime - dt->lastFPSUpdate >= 1000) { // Toutes les secondes
        dt->fps = dt->frameCount;
        dt->frameCount = 0;
        dt->lastFPSUpdate = currentTime;
    }
}

int getFPS() {
    return dt->fps;
}
//===