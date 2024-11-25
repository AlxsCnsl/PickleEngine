// deltatime.h (ajout de la fonction FPS)
#ifndef DELTATIME_H
#define DELTATIME_H

#include <SDL2/SDL.h>
#include "window.h"

typedef struct {
    Uint32 lastTime;   // Temps de la dernière frame
    float deltaTime;   // Temps écoulé entre deux frames
    Uint32 frameCount; // Compteur de frames
    Uint32 lastFPSUpdate; // Temps de la dernière mise à jour des FPS
    int fps;           // Nombre de FPS
} DeltaTime;

extern DeltaTime* dt;

// Initialiser DeltaTime
void initDeltaTime();

// Mettre à jour DeltaTime
void updateDeltaTime();

// Obtenir les FPS actuels
int getFPS();

#endif // DELTATIME_H
