#pragma once

#include <vector>
#include <memory>
#include "ModuleInterface.hpp"  // Correction : inclure la bonne interface

class ModuleManager {
    std::vector<std::unique_ptr<ModuleInterface>> modules;  // Liste des modules

public:
    // Inscrire un module
    void registerModule(std::unique_ptr<ModuleInterface> module) {
        modules.push_back(std::move(module));  // Ajoute un module à la liste
    }

    // Initialiser tous les modules
    void initAll() {
        for (auto& module : modules) {
            if (!module->onInit()) {
                // Si un module échoue à s'initialiser, tu peux afficher un message d'erreur
                std::cerr << "Erreur lors de l'initialisation de " << module->getName() << std::endl;
            }
        }
    }

    // Mettre à jour tous les modules
    void updateAll(float deltaTime) {
        for (auto& module : modules) {
            module->onUpdate(deltaTime);  // Appel de la mise à jour de chaque module
        }
    }

    // Fermer tous les modules
    void shutdownAll() {
        for (auto& module : modules) {
            module->onShutdown();  // Appel de la fermeture de chaque module
        }
    }
};
