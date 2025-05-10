#pragma once

#include <string>

// Interface de base pour tous les modules du moteur
class ModuleInterface {
public:
    virtual ~ModuleInterface() = default;

    // Appelé à l'initialisation du module
    virtual bool onInit() = 0;

    // Appelé à chaque boucle du moteur (si applicable)
    virtual void onUpdate(float deltaTime) {}

    // Appelé à la fermeture du moteur
    virtual void onShutdown() {}

    // Retourne le nom du module
    virtual std::string getName() const = 0;
};
