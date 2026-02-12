#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <window_render/window_render.hpp>
#include <vector>

namespace pkbog {

struct DebugValue {
  std::string label;
  std::string value;
};

class DebugOverlay {
public:
  DebugOverlay(SDL_Renderer* sdl_renderer,  const char* fontPath, int fontSize);
  ~DebugOverlay();

  void addValue(const std::string& label, const std::string& value);
  void addValue(const std::string& label, int value);
  void addValue(const std::string& label, float value);

  void clear();
  void render(int x = 10, int y = 10);

  void quit();


private:

  SDL_Renderer* renderer = nullptr;
  TTF_Font* m_font = nullptr;
  std::vector<DebugValue> m_values;
};
}