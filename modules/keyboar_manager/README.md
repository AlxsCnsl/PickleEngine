# keyboard_input module (for SDL3)

This module provides a comprehensive and efficient keyboard input management system for SDL3 applications.
It handles key states, key combinations, sequences, repeats, and provides a clean callback-based API for integration with any game engine or application.

## Dependencies 

SDL3 (static lib)

## Functions

```cpp
// Creates an instance of KeyboardManager
KeyboardManager keyboard;

// Initialize the keyboard manager (must be called after SDL initialization)
keyboard.initialize(); // return bool

// Shutdown and cleanup resources
keyboard.shutdown(); // return void

// Update keyboard states (call once per frame)
keyboard.update(); // return void

// Handle SDL events (call for each SDL keyboard event)
keyboard.handleEvent(const SDL_Event& event); // return void

// === KEY STATE CHECKING ===

// Check if a key was just pressed this frame
keyboard.isKeyPressed(SDL_Scancode key); // return bool

// Check if a key is currently held down
keyboard.isKeyHeld(SDL_Scancode key); // return bool

// Check if a key was just released this frame
keyboard.isKeyReleased(SDL_Scancode key); // return bool

// Check if a key is currently down (pressed or held)
keyboard.isKeyDown(SDL_Scancode key); // return bool

// Check if a key is currently up (not pressed)
keyboard.isKeyUp(SDL_Scancode key); // return bool

// Get the current state of a key
keyboard.getKeyState(SDL_Scancode key); // return KeyState

// Get how long a key has been held (in seconds)
keyboard.getKeyHoldDuration(SDL_Scancode key); // return float

// Get the repeat count for a key
keyboard.getKeyRepeatCount(SDL_Scancode key); // return uint32_t

// === KEY COMBINATIONS ===

// Check if multiple keys are currently down
keyboard.areKeysDown(const std::vector<SDL_Scancode>& keys); // return bool

// Check if multiple keys were just pressed
keyboard.areKeysPressed(const std::vector<SDL_Scancode>& keys); // return bool

// Check modifier keys
keyboard.isShiftPressed(); // return bool
keyboard.isCtrlPressed();  // return bool
keyboard.isAltPressed();   // return bool

// === KEY SEQUENCES ===

// Register a key sequence with a name
keyboard.registerSequence(const std::string& name, const std::vector<SDL_Scancode>& sequence); // return void

// Check if a sequence was triggered this frame
keyboard.isSequenceTriggered(const std::string& name); // return bool

// Clear all registered sequences
keyboard.clearSequences(); // return void

// === CALLBACKS ===

// Callback type for key state changes
using KeyCallback = std::function<void(SDL_Scancode key, KeyState state)>;

// Callback type for key repeats
using KeyRepeatCallback = std::function<void(SDL_Scancode key, uint32_t repeat_count)>;

// Set callback for key state changes
keyboard.setKeyCallback(KeyCallback callback); // return void

// Set callback for key repeats
keyboard.setKeyRepeatCallback(KeyRepeatCallback callback); // return void

// === CONFIGURATION ===

// Set repeat delay (time before first repeat in milliseconds)
keyboard.setRepeatDelay(uint32_t delay_ms); // return void

// Set repeat interval (time between repeats in milliseconds)
keyboard.setRepeatInterval(uint32_t interval_ms); // return void

// Enable or disable key repeat
keyboard.enableKeyRepeat(bool enable); // return void

// Set sequence timeout (maximum time between keys in a sequence)
keyboard.setSequenceTimeout(uint32_t timeout_ms); // return void

// Reset all key states and sequences
keyboard.reset(); // return void

// === UTILITIES ===

// Get all currently pressed keys
keyboard.getPressedKeys(); // return std::vector<SDL_Scancode>

// Get all currently held keys
keyboard.getHeldKeys(); // return std::vector<SDL_Scancode>

// Get the name of a key
keyboard.getKeyName(SDL_Scancode key); // return const char*

// === GLOBAL UTILITIES ===

// Convert keycode to scancode
KeyboardInput::keycodeToScancode(SDL_Keycode keycode); // return SDL_Scancode

// Check if a key is a modifier key
KeyboardInput::isModifierKey(SDL_Scancode key); // return bool
```

## Key States

```cpp
enum class KeyState {
    RELEASED,      // Key is not pressed
    PRESSED,       // Key was just pressed this frame
    HELD,          // Key is being held down
    JUST_RELEASED  // Key was just released this frame
};
```

## EXAMPLE : 

```cpp
#include <keyboard_input/keyboard_input.hpp>
#include <SDL3/SDL.h>
#include <iostream>

int main() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    SDL_Window* window = SDL_CreateWindow("Keyboard Test", 800, 600, SDL_WINDOW_SHOWN);

    // Create and initialize keyboard manager
    KeyboardInput::KeyboardManager keyboard;
    keyboard.initialize();

    // Set up callbacks
    keyboard.setKeyCallback([](SDL_Scancode key, KeyboardInput::KeyState state) {
        if (state == KeyboardInput::KeyState::PRESSED) {
            std::cout << "Key pressed: " << SDL_GetScancodeName(key) << std::endl;
        }
    });

    keyboard.setKeyRepeatCallback([](SDL_Scancode key, uint32_t count) {
        std::cout << "Key " << SDL_GetScancodeName(key) << " repeat #" << count << std::endl;
    });

    // Register a sequence (Konami code)
    keyboard.registerSequence("konami", {
        SDL_SCANCODE_UP, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_DOWN,
        SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT,
        SDL_SCANCODE_B, SDL_SCANCODE_A
    });

    // Configure repeat settings
    keyboard.setRepeatDelay(300);    // 300ms before first repeat
    keyboard.setRepeatInterval(100); // 100ms between repeats

    // Main loop
    bool running = true;
    SDL_Event event;

    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
            keyboard.handleEvent(event);
        }

        // Update keyboard
        keyboard.update();

        // Game logic examples
        
        // Player movement
        float speed = 200.0f; // pixels per second
        if (keyboard.isKeyDown(SDL_SCANCODE_W)) {
            // Move player up
        }
        if (keyboard.isKeyDown(SDL_SCANCODE_S)) {
            // Move player down
        }
        if (keyboard.isKeyDown(SDL_SCANCODE_A)) {
            // Move player left
        }
        if (keyboard.isKeyDown(SDL_SCANCODE_D)) {
            // Move player right
        }

        // Jump (single press)
        if (keyboard.isKeyPressed(SDL_SCANCODE_SPACE)) {
            // Player jumps
        }

        // Charge attack (hold duration)
        if (keyboard.isKeyHeld(SDL_SCANCODE_X)) {
            float charge_time = keyboard.getKeyHoldDuration(SDL_SCANCODE_X);
            if (charge_time > 2.0f) {
                // Fully charged attack
            }
        }

        // Save game (Ctrl+S)
        if (keyboard.areKeysPressed({SDL_SCANCODE_LCTRL, SDL_SCANCODE_S})) {
            // Save game
        }

        // Check for cheat code
        if (keyboard.isSequenceTriggered("konami")) {
            std::cout << "Cheat code activated!" << std::endl;
        }

        // Exit with Escape
        if (keyboard.isKeyPressed(SDL_SCANCODE_ESCAPE)) {
            running = false;
        }

        SDL_Delay(16); // ~60 FPS
    }

    // Cleanup
    keyboard.shutdown();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
```

## Notes

- The keyboard manager must be updated every frame with `update()` to properly track key states.
- SDL events must be passed to `handleEvent()` for the manager to work correctly.
- Key states are frame-based: `PRESSED` and `JUST_RELEASED` are only true for one frame.
- Sequences have a configurable timeout - if too much time passes between keys, the sequence resets.
- Repeat functionality mimics standard OS keyboard repeat behavior with configurable delays.
- All functions are thread-safe when called from the same thread that handles SDL events.
- The module uses `SDL_Scancode` for hardware-independent key identification.