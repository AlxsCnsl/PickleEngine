add_library(entt INTERFACE)

# Inclure le dossier "include", qui contient le dossier "entt/"
target_include_directories(entt INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
