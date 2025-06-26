#include <keyboar_manager/keyboar_manager.hpp>
#include <algorithm>

namespace KeyboardInput {

    KeyboardManager::KeyboardManager() {
        // Constructeur vide - l'initialisation se fait dans initialize()
    }

    bool KeyboardManager::initialize() {
        // Vérifier que SDL est initialisé
        if (!SDL_WasInit(SDL_INIT_EVENTS)) {
            return false;
        }
        
        // Réinitialiser l'état
        reset();
        return true;
    }

    void KeyboardManager::shutdown() {
        reset();
        key_callback_ = nullptr;
        repeat_callback_ = nullptr;
    }

    void KeyboardManager::update() {
        updateKeyStates();
        if (repeat_enabled_) {
            updateKeyRepeats();
        }
        updateSequences();
        
        // Nettoyer les séquences déclenchées de la frame précédente
        triggered_sequences_.clear();
    }

    void KeyboardManager::handleEvent(const SDL_Event& event) {
        if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
            SDL_Scancode scancode = event.key.scancode;
            auto now = std::chrono::steady_clock::now();
            
            if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat) {
                // Nouvelle pression de touche
                auto& key_info = key_states_[scancode];
                if (key_info.state == KeyState::RELEASED) {
                    key_info.state = KeyState::PRESSED;
                    key_info.press_time = now;
                    key_info.last_repeat_time = now;
                    key_info.repeat_count = 0;
                    key_info.is_repeating = false;
                    
                    triggerCallback(scancode, KeyState::PRESSED);
                }
            }
            else if (event.type == SDL_EVENT_KEY_UP) {
                // Relâchement de touche
                auto it = key_states_.find(scancode);
                if (it != key_states_.end() && it->second.state != KeyState::RELEASED) {
                    it->second.state = KeyState::JUST_RELEASED;
                    triggerCallback(scancode, KeyState::JUST_RELEASED);
                }
            }
            
            // Mettre à jour les séquences
            if (event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat) {
                for (auto& [name, seq_info] : sequences_) {
                    if (seq_info.current_index < seq_info.keys.size() && 
                        seq_info.keys[seq_info.current_index] == scancode) {
                        
                        auto time_since_last = std::chrono::duration_cast<std::chrono::milliseconds>(
                            now - seq_info.last_key_time).count();
                            
                        if (seq_info.current_index == 0 || time_since_last <= sequence_timeout_ms_) {
                            seq_info.current_index++;
                            seq_info.last_key_time = now;
                            
                            if (seq_info.current_index >= seq_info.keys.size()) {
                                triggered_sequences_[name] = true;
                                seq_info.current_index = 0; // Reset pour permettre répétition
                            }
                        } else {
                            // Timeout dépassé, recommencer la séquence
                            seq_info.current_index = (seq_info.keys[0] == scancode) ? 1 : 0;
                            seq_info.last_key_time = now;
                        }
                    } else {
                        // Mauvaise touche, vérifier si c'est le début d'une nouvelle séquence
                        if (seq_info.keys[0] == scancode) {
                            seq_info.current_index = 1;
                            seq_info.last_key_time = now;
                        } else {
                            seq_info.current_index = 0;
                        }
                    }
                }
            }
        }
    }

    // === MÉTHODES DE VÉRIFICATION D'ÉTAT ===

    bool KeyboardManager::isKeyPressed(SDL_Scancode key) const {
        auto it = key_states_.find(key);
        return it != key_states_.end() && it->second.state == KeyState::PRESSED;
    }

    bool KeyboardManager::isKeyHeld(SDL_Scancode key) const {
        auto it = key_states_.find(key);
        return it != key_states_.end() && it->second.state == KeyState::HELD;
    }

    bool KeyboardManager::isKeyReleased(SDL_Scancode key) const {
        auto it = key_states_.find(key);
        return it != key_states_.end() && it->second.state == KeyState::JUST_RELEASED;
    }

    bool KeyboardManager::isKeyDown(SDL_Scancode key) const {
        auto it = key_states_.find(key);
        return it != key_states_.end() && 
               (it->second.state == KeyState::PRESSED || it->second.state == KeyState::HELD);
    }

    bool KeyboardManager::isKeyUp(SDL_Scancode key) const {
        return !isKeyDown(key);
    }

    KeyState KeyboardManager::getKeyState(SDL_Scancode key) const {
        auto it = key_states_.find(key);
        return it != key_states_.end() ? it->second.state : KeyState::RELEASED;
    }

    float KeyboardManager::getKeyHoldDuration(SDL_Scancode key) const {
        auto it = key_states_.find(key);
        if (it == key_states_.end() || 
            (it->second.state != KeyState::PRESSED && it->second.state != KeyState::HELD)) {
            return 0.0f;
        }
        
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - it->second.press_time).count();
        return duration / 1000.0f;
    }

    uint32_t KeyboardManager::getKeyRepeatCount(SDL_Scancode key) const {
        auto it = key_states_.find(key);
        return it != key_states_.end() ? it->second.repeat_count : 0;
    }

    // === GESTION DES COMBINAISONS ===

    bool KeyboardManager::areKeysDown(const std::vector<SDL_Scancode>& keys) const {
        return std::all_of(keys.begin(), keys.end(), 
            [this](SDL_Scancode key) { return isKeyDown(key); });
    }

    bool KeyboardManager::areKeysPressed(const std::vector<SDL_Scancode>& keys) const {
        return std::all_of(keys.begin(), keys.end(), 
            [this](SDL_Scancode key) { return isKeyPressed(key); });
    }

    bool KeyboardManager::isShiftPressed() const {
        return isKeyDown(SDL_SCANCODE_LSHIFT) || isKeyDown(SDL_SCANCODE_RSHIFT);
    }

    bool KeyboardManager::isCtrlPressed() const {
        return isKeyDown(SDL_SCANCODE_LCTRL) || isKeyDown(SDL_SCANCODE_RCTRL);
    }

    bool KeyboardManager::isAltPressed() const {
        return isKeyDown(SDL_SCANCODE_LALT) || isKeyDown(SDL_SCANCODE_RALT);
    }

    // === GESTION DES SÉQUENCES ===

    void KeyboardManager::registerSequence(const std::string& name, 
                                          const std::vector<SDL_Scancode>& sequence) {
        if (!sequence.empty()) {
            sequences_[name] = {sequence, std::chrono::steady_clock::now(), 0};
        }
    }

    bool KeyboardManager::isSequenceTriggered(const std::string& name) const {
        auto it = triggered_sequences_.find(name);
        return it != triggered_sequences_.end() && it->second;
    }

    void KeyboardManager::clearSequences() {
        sequences_.clear();
        triggered_sequences_.clear();
    }

    // === CALLBACKS ===

    void KeyboardManager::setKeyCallback(KeyCallback callback) {
        key_callback_ = callback;
    }

    void KeyboardManager::setKeyRepeatCallback(KeyRepeatCallback callback) {
        repeat_callback_ = callback;
    }

    // === CONFIGURATION ===

    void KeyboardManager::setRepeatDelay(uint32_t delay_ms) {
        repeat_delay_ms_ = delay_ms;
    }

    void KeyboardManager::setRepeatInterval(uint32_t interval_ms) {
        repeat_interval_ms_ = interval_ms;
    }

    void KeyboardManager::enableKeyRepeat(bool enable) {
        repeat_enabled_ = enable;
    }

    void KeyboardManager::setSequenceTimeout(uint32_t timeout_ms) {
        sequence_timeout_ms_ = timeout_ms;
    }

    void KeyboardManager::reset() {
        key_states_.clear();
        previous_frame_keys_.clear();
        sequences_.clear();
        triggered_sequences_.clear();
    }

    // === UTILITAIRES ===

    std::vector<SDL_Scancode> KeyboardManager::getPressedKeys() const {
        std::vector<SDL_Scancode> keys;
        for (const auto& [scancode, info] : key_states_) {
            if (info.state == KeyState::PRESSED) {
                keys.push_back(scancode);
            }
        }
        return keys;
    }

    std::vector<SDL_Scancode> KeyboardManager::getHeldKeys() const {
        std::vector<SDL_Scancode> keys;
        for (const auto& [scancode, info] : key_states_) {
            if (info.state == KeyState::HELD || info.state == KeyState::PRESSED) {
                keys.push_back(scancode);
            }
        }
        return keys;
    }

    const char* KeyboardManager::getKeyName(SDL_Scancode key) const {
        return SDL_GetScancodeName(key);
    }

    // === MÉTHODES PRIVÉES ===

    void KeyboardManager::updateKeyStates() {
        // Mettre à jour les états des touches
        for (auto& [scancode, info] : key_states_) {
            switch (info.state) {
                case KeyState::PRESSED:
                    info.state = KeyState::HELD;
                    triggerCallback(scancode, KeyState::HELD);
                    break;
                case KeyState::JUST_RELEASED:
                    info.state = KeyState::RELEASED;
                    break;
                default:
                    break;
            }
        }
        
        // Nettoyer les touches relâchées
        auto it = key_states_.begin();
        while (it != key_states_.end()) {
            if (it->second.state == KeyState::RELEASED) {
                it = key_states_.erase(it);
            } else {
                ++it;
            }
        }
    }

    void KeyboardManager::updateKeyRepeats() {
        auto now = std::chrono::steady_clock::now();
        
        for (auto& [scancode, info] : key_states_) {
            if (info.state == KeyState::HELD) {
                auto time_since_press = std::chrono::duration_cast<std::chrono::milliseconds>(
                    now - info.press_time).count();
                auto time_since_repeat = std::chrono::duration_cast<std::chrono::milliseconds>(
                    now - info.last_repeat_time).count();
                
                if (!info.is_repeating && time_since_press >= repeat_delay_ms_) {
                    // Première répétition
                    info.is_repeating = true;
                    info.repeat_count = 1;
                    info.last_repeat_time = now;
                    triggerRepeatCallback(scancode, info.repeat_count);
                }
                else if (info.is_repeating && time_since_repeat >= repeat_interval_ms_) {
                    // Répétitions suivantes
                    info.repeat_count++;
                    info.last_repeat_time = now;
                    triggerRepeatCallback(scancode, info.repeat_count);
                }
            }
        }
    }

    void KeyboardManager::updateSequences() {
        auto now = std::chrono::steady_clock::now();
        
        // Vérifier les timeouts des séquences
        for (auto& [name, seq_info] : sequences_) {
            if (seq_info.current_index > 0) {
                auto time_since_last = std::chrono::duration_cast<std::chrono::milliseconds>(
                    now - seq_info.last_key_time).count();
                    
                if (time_since_last > sequence_timeout_ms_) {
                    seq_info.current_index = 0;
                }
            }
        }
    }

    void KeyboardManager::triggerCallback(SDL_Scancode key, KeyState state) {
        if (key_callback_) {
            key_callback_(key, state);
        }
    }

    void KeyboardManager::triggerRepeatCallback(SDL_Scancode key, uint32_t count) {
        if (repeat_callback_) {
            repeat_callback_(key, count);
        }
    }

    // === FONCTIONS UTILITAIRES GLOBALES ===

    SDL_Scancode keycodeToScancode(SDL_Keycode keycode) {
        return SDL_GetScancodeFromKey(keycode, nullptr);
    }

    bool isModifierKey(SDL_Scancode key) {
        return key == SDL_SCANCODE_LSHIFT || key == SDL_SCANCODE_RSHIFT ||
               key == SDL_SCANCODE_LCTRL || key == SDL_SCANCODE_RCTRL ||
               key == SDL_SCANCODE_LALT || key == SDL_SCANCODE_RALT ||
               key == SDL_SCANCODE_LGUI || key == SDL_SCANCODE_RGUI;
    }

} // namespace KeyboardInput