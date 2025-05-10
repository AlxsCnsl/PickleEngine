#include <iostream>
#include <memory>
#include <ModuleManager.hpp>
#include <window_render.hpp>

int main() {
    // Création du gestionnaire de modules
    ModuleManager manager;

    // Inscription des modules
    manager.registerModule(std::make_unique<WindowRenderModule>());


    // Initialisation de tous les modules
    manager.initAll();

    // Boucle principale (simulée)
    bool running = true;
    float deltaTime = 0.016f;  // 60fps simulé

    while (running) {
        manager.updateAll(deltaTime);  // Mise à jour de tous les modules

        // Simule une condition de sortie, par exemple après 5 secondes
        static int frameCount = 0;
        if (++frameCount > 300) {  // ~5 secondes (300 frames à 60fps)
            running = false;
        }
    }

    manager.shutdownAll();

    return 0;
}
