// deltatime.h (ajout de la fonction FPS)
#ifndef DELTATIME_H
#define DELTATIME_H

#include <SDL2/SDL.h>

typedef struct {
    Uint32 lastTime;   // Temps de la dernière frame
    float deltaTime;   // Temps écoulé entre deux frames
    Uint32 frameCount; // Compteur de frames
    Uint32 lastFPSUpdate; // Temps de la dernière mise à jour des FPS
    int fps;           // Nombre de FPS
} DeltaTime;

// Initialiser DeltaTime
void initDeltaTime(DeltaTime* dt);

// Mettre à jour DeltaTime
void updateDeltaTime(DeltaTime* dt, int max);

// Obtenir les FPS actuels
int getFPS(DeltaTime* dt);

#endif // DELTATIME_H
