#include <assets_loader.hpp>
#include <filesystem>

std::string getAssetPath(const std::string& filename, const char* argv0) {
    std::filesystem::path binPath = std::filesystem::absolute(argv0).parent_path();
    return (binPath / "assets" / filename).string();
}