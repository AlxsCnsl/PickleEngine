# Engine Launcher (jeu de test)
add_executable(engine_launcher
    main.cpp
)

# Include directories
target_include_directories(engine_launcher PRIVATE
    ${PROJECT_SOURCE_DIR}/engine_launcher/include
    ${PROJECT_SOURCE_DIR}/core/include
    ${ENTT_INCLUDE_DIR}
)

# Copie automatique du dossier assets dans le dossier final de build
add_custom_command(TARGET engine_launcher POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:engine_launcher>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:engine_launcher>/assets
    COMMENT "📁 Copie des assets dans le dossier de build..."
)

# Lien vers les libs SDL
target_link_libraries(engine_launcher PRIVATE
    SDL3
    SDL3_image
    entt
)


target_link_libraries(engine_launcher PRIVATE PickleEngine)

target_include_directories(engine_launcher PRIVATE ${CMAKE_SOURCE_DIR}/core)
