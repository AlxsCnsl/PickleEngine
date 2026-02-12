#include <fast_debugging.hpp>


namespace pkbog {

DebugOverlay::DebugOverlay(SDL_Renderer* renderer, const char* fontPath, int fontSize)
    : renderer(renderer)
{

    if (TTF_Init() != 0) {
        SDL_Log("DebugOverlay : TTF_Init() Error: %s", SDL_GetError());
        return;
    }

    m_font = TTF_OpenFont(fontPath, fontSize);
    if (!m_font) {
        SDL_Log("DebugOverlay : Failed to load font: %s", SDL_GetError());
    }
}

DebugOverlay::~DebugOverlay() {
    if (m_font) {
        TTF_CloseFont(m_font);
    }
}

void DebugOverlay::quit(){
    TTF_Quit();
}

void DebugOverlay::addValue(const std::string& label, const std::string& value) {
    m_values.push_back({label, value});
}

void DebugOverlay::addValue(const std::string& label, int value) {
    m_values.push_back({label, std::to_string(value)});
}

void DebugOverlay::addValue(const std::string& label, float value) {
    m_values.push_back({label, std::to_string(value)});
}

void DebugOverlay::clear() {
    m_values.clear();
}

void DebugOverlay::render(int x, int y) {
    int offsetY = 0;
    SDL_Color white = {255, 255, 255, 255};

    for (const auto& entry : m_values) {
        std::string full = entry.label + ": " + entry.value;

        SDL_Surface* surf = TTF_RenderText_Blended(m_font, full.c_str(), 0, white);
        if (!surf) {
            SDL_Log("DebugOverlay : TTF_RenderText_Blended failed: %s", SDL_GetError());
            continue;
        }

        SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
        if (!tex) {
            SDL_Log("DebugOverlay : SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
            SDL_DestroySurface(surf);
            continue;
        }

        SDL_FRect dstrect;
        dstrect.x = static_cast<float>(x);
        dstrect.y = static_cast<float>(y + offsetY);
        dstrect.w = static_cast<float>(surf->w);
        dstrect.h = static_cast<float>(surf->h);

        SDL_RenderTexture(renderer, tex, nullptr, &dstrect);

        SDL_DestroyTexture(tex);
        SDL_DestroySurface(surf);

        offsetY += surf->h + 2; // espacement entre les lignes
    }
    }
}
