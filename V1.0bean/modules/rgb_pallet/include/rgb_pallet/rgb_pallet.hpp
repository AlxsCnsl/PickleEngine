#pragma once
#include <SDL3/SDL.h>

namespace PKRGB{
    constexpr SDL_Color RED     = {255, 0,   0,   255};
    constexpr SDL_Color GREEN   = {0,   255, 0,   255};
    constexpr SDL_Color BLUE    = {0,   0,   255, 255};
    constexpr SDL_Color YELOW   = {255, 255, 0,   255};
    constexpr SDL_Color PURPLE  = {255, 255, 0,   255};
    constexpr SDL_Color PINK    = {255, 128, 255, 255};
    constexpr SDL_Color CYAN    = {0,   255, 255, 255};
    constexpr SDL_Color WHITE   = {255, 255, 255, 255};
    constexpr SDL_Color L_GRAY  = {192, 192, 192, 255};
    constexpr SDL_Color GRAY    = {128, 128, 128, 255};
    constexpr SDL_Color D_GRAY  = {64,  64,  64,  255};
    constexpr SDL_Color BLACK   = {0,   0,   0,   255};
}
