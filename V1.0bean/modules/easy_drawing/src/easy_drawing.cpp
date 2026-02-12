#include <easy_drawing/easy_drawing.hpp>

// Utilitaire pour dessiner un pixel (wrapper simple)
// Utility to draw a single pixel (simple wrapper)
void PutPixel(WindowRender* window, int x, int y, SDL_Color color) {
    SDL_Renderer* renderer = window->getRenderer();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(renderer, x, y);
}

// Horizontal line
void HLine(WindowRender* window, int x, int y, int length, SDL_Color color) {
    SDL_Renderer* renderer = window->getRenderer();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(renderer, x, y, x + length - 1, y);
}

// Vertical line
void VLine(WindowRender* window, int x, int y, int length, SDL_Color color) {
    SDL_Renderer* renderer = window->getRenderer();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(renderer, x, y, x, y + length - 1);
}

// General line between two points
void Line(WindowRender* window, int x1, int y1, int x2, int y2, SDL_Color color) {
    SDL_Renderer* renderer = window->getRenderer();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(renderer, x1, y1, x2, y2);
}

// Line from a point, given an angle (in radians) and length
void LineAngle(WindowRender* window, int x, int y, float length, float angleRadians, SDL_Color color) {
    SDL_Renderer* renderer = window->getRenderer();
    int x2 = static_cast<int>(x + std::cos(angleRadians) * length);
    int y2 = static_cast<int>(y + std::sin(angleRadians) * length);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderLine(renderer, x, y, x2, y2);
}

// Empty rectangle
void DrawRect(WindowRender* window, int x, int y, int w, int h, SDL_Color color) {
    SDL_Renderer* renderer = window->getRenderer();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect = { static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h) };
    SDL_RenderRect(renderer, &rect);
}

// Filled rectangle
void FillRect(WindowRender* window, int x, int y, int w, int h, SDL_Color color) {
    SDL_Renderer* renderer = window->getRenderer();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_FRect rect = { static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h) };
    SDL_RenderFillRect(renderer, &rect);
}

// Helper to plot 8 symmetrical points of a circle
void PlotCirclePoints(SDL_Renderer* renderer, int cx, int cy, int x, int y) {
    SDL_RenderPoint(renderer, cx + x, cy + y);
    SDL_RenderPoint(renderer, cx - x, cy + y);
    SDL_RenderPoint(renderer, cx + x, cy - y);
    SDL_RenderPoint(renderer, cx - x, cy - y);
    SDL_RenderPoint(renderer, cx + y, cy + x);
    SDL_RenderPoint(renderer, cx - y, cy + x);
    SDL_RenderPoint(renderer, cx + y, cy - x);
    SDL_RenderPoint(renderer, cx - y, cy - x);
}

// Optimized empty circle (Midpoint Circle Algorithm)
void DrawCircle(WindowRender* window, int centerX, int centerY, int radius, SDL_Color color) {
    SDL_Renderer* renderer = window->getRenderer();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int x = 0;
    int y = radius;
    int d = 1 - radius;
    PlotCirclePoints(renderer, centerX, centerY, x, y);
    while (x < y) {
        ++x;
        if (d < 0) {
            d += 2 * x + 1;
        } else {
            --y;
            d += 2 * (x - y) + 1;
        }
        PlotCirclePoints(renderer, centerX, centerY, x, y);
    }
}

// Draws a horizontal line centered at (cx, cy)
void DrawHorizontalLine(SDL_Renderer* renderer, int cx, int cy, int x) {
    SDL_RenderLine(renderer, cx - x, cy, cx + x, cy);
}

// Filled circle (optimized using scanlines)
void FillCircle(WindowRender* window, int centerX, int centerY, int radius, SDL_Color color) {
    SDL_Renderer* renderer = window->getRenderer();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int x = 0;
    int y = radius;
    int d = 1 - radius;

    DrawHorizontalLine(renderer, centerX, centerY, radius);

    while (x <= y) {
        DrawHorizontalLine(renderer, centerX, centerY + y, x);
        DrawHorizontalLine(renderer, centerX, centerY - y, x);
        DrawHorizontalLine(renderer, centerX, centerY + x, y);
        DrawHorizontalLine(renderer, centerX, centerY - x, y);

        ++x;
        if (d < 0) {
            d += 2 * x + 1;
        } else {
            --y;
            d += 2 * (x - y) + 1;
        }
    }
}
