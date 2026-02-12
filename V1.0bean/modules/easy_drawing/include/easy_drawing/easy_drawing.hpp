#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <cmath>
#include <iostream>
#include <window_render/window_render.hpp>

void PutPixel(WindowRender* window, int x, int y, SDL_Color color);

void HLine(WindowRender* window, int x, int y, int length, SDL_Color color);
void VLine(WindowRender* window, int x, int y, int length, SDL_Color color);
void Line(WindowRender* window, int x1, int y1, int x2, int y2, SDL_Color color);
void LineAngle(WindowRender* window, int x, int y, float length, float angleRadians, SDL_Color color);

void DrawRect(WindowRender* window, int x, int y, int w, int h, SDL_Color color);
void FillRect(WindowRender* window, int x, int y, int w, int h, SDL_Color color);

void DrawCircle(WindowRender* window, int centerX, int centerY, int radius, SDL_Color color);
void FillCircle(WindowRender* window, int centerX, int centerY, int radius, SDL_Color color);