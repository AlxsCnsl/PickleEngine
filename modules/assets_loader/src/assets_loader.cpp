#include <assets_loader.hpp>

std::string getAssetPath(const std::string& filename){
  const char* basepath = SDL_GetBasePath();
  if(!basepath){
    std::string msg = std::string("Failed to get base path: ") + SDL_GetError();
    SDL_Log(msg.c_str());
    return filename;
  }
  std::string fullPath = std::string(basepath) + "/assets/" + filename;
  SDL_free((void*)basepath);
  return fullPath;
}