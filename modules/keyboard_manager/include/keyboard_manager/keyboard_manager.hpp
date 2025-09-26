#pragma once

#include <SDL3/SDL.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <functional>
#include <chrono>
#include <string>

namespace KeyboardInput {

    // États possibles d'une touche
    enum class KeyState {
        RELEASED,    // Touche relâchée
        PRESSED,     // Touche vient d'être appuyée (frame actuelle)
        HELD,        // Touche maintenue enfoncée
        JUST_RELEASED // Touche vient d'être relâchée (frame actuelle)
    };

    // Informations sur une touche
    struct KeyInfo {
        KeyState state = KeyState::RELEASED;
        std::chrono::steady_clock::time_point press_time;
        std::chrono::steady_clock::time_point last_repeat_time;
        uint32_t repeat_count = 0;
        bool is_repeating = false;
    };

    // Callback pour les événements clavier
    using KeyCallback = std::function<void(SDL_Scancode key, KeyState state)>;
    using KeyRepeatCallback = std::function<void(SDL_Scancode key, uint32_t repeat_count)>;

    class KeyboardManager {
    public:
        KeyboardManager();
        ~KeyboardManager() = default;

        // Initialisation et nettoyage
        bool initialize();
        void shutdown();

        // Mise à jour à appeler chaque frame
        void update();

        // Traitement des événements SDL
        void handleEvent(const SDL_Event& event);

        // === MÉTHODES DE VÉRIFICATION D'ÉTAT ===
        
        // Vérifications simples
        bool isKeyPressed(SDL_Scancode key) const;      // Vient d'être appuyée
        bool isKeyHeld(SDL_Scancode key) const;         // Maintenue enfoncée
        bool isKeyReleased(SDL_Scancode key) const;     // Vient d'être relâchée
        bool isKeyDown(SDL_Scancode key) const;         // Appuyée (PRESSED ou HELD)
        bool isKeyUp(SDL_Scancode key) const;           // Pas appuyée

        // Informations avancées
        KeyState getKeyState(SDL_Scancode key) const;
        float getKeyHoldDuration(SDL_Scancode key) const; // En secondes
        uint32_t getKeyRepeatCount(SDL_Scancode key) const;

        // === GESTION DES COMBINAISONS ===
        
        // Vérifier si plusieurs touches sont appuyées simultanément
        bool areKeysDown(const std::vector<SDL_Scancode>& keys) const;
        bool areKeysPressed(const std::vector<SDL_Scancode>& keys) const;

        // Vérifier les touches de modification
        bool isShiftPressed() const;
        bool isCtrlPressed() const;
        bool isAltPressed() const;

        // === GESTION DES SÉQUENCES ===
        
        // Enregistrer une séquence de touches
        void registerSequence(const std::string& name, const std::vector<SDL_Scancode>& sequence);
        bool isSequenceTriggered(const std::string& name) const;
        void clearSequences();

        // === CALLBACKS ===
        
        // Enregistrer des callbacks pour les événements
        void setKeyCallback(KeyCallback callback);
        void setKeyRepeatCallback(KeyRepeatCallback callback);

        // === CONFIGURATION ===
        
        // Configuration de la répétition
        void setRepeatDelay(uint32_t delay_ms);     // Délai avant première répétition
        void setRepeatInterval(uint32_t interval_ms); // Intervalle entre répétitions
        void enableKeyRepeat(bool enable);

        // Configuration générale
        void setSequenceTimeout(uint32_t timeout_ms); // Timeout pour les séquences
        void reset(); // Remet à zéro tous les états

        // === UTILITAIRES ===
        
        // Obtenir toutes les touches actuellement appuyées
        std::vector<SDL_Scancode> getPressedKeys() const;
        std::vector<SDL_Scancode> getHeldKeys() const;

        // Convertir scancode vers nom
        const char* getKeyName(SDL_Scancode key) const;

    private:
        // État interne
        std::unordered_map<SDL_Scancode, KeyInfo> key_states_;
        std::unordered_set<SDL_Scancode> previous_frame_keys_;
        
        // Callbacks
        KeyCallback key_callback_;
        KeyRepeatCallback repeat_callback_;

        // Configuration répétition
        uint32_t repeat_delay_ms_ = 500;    // 500ms avant première répétition
        uint32_t repeat_interval_ms_ = 50;  // 50ms entre répétitionsq
        bool repeat_enabled_ = true;

        // Gestion des séquences
        struct SequenceInfo {
            std::vector<SDL_Scancode> keys;
            std::chrono::steady_clock::time_point last_key_time;
            size_t current_index = 0;
        };
        std::unordered_map<std::string, SequenceInfo> sequences_;
        std::unordered_map<std::string, bool> triggered_sequences_;
        uint32_t sequence_timeout_ms_ = 1000; // 1 seconde

        // Méthodes internes
        void updateKeyStates();
        void updateKeyRepeats();
        void updateSequences();
        void triggerCallback(SDL_Scancode key, KeyState state);
        void triggerRepeatCallback(SDL_Scancode key, uint32_t count);
    };

    // === FONCTIONS UTILITAIRES GLOBALES ===
    
    // Convertir SDL_Keycode vers SDL_Scancode
    SDL_Scancode keycodeToScancode(SDL_Keycode keycode);
    
    // Vérifier si une touche est une touche de modification
    bool isModifierKey(SDL_Scancode key);
    
} // namespace KeyboardInput