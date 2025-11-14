# 🥒 PickleEngine

**PickleEngine** is a modular C++ game engine based on SDL3. Its goal is to provide a simple, extensible, and eventually cross-platform architecture for quickly creating games (2D for now).

[Link to SDL ](https://github.com/libsdl-org/SDL)
[Link to SDL_image](https://github.com/libsdl-org/SDL_image)

---

## ✨ Features

- 🔌 Easy-to-integrate module/plugin system

---

## 📦 Included Modules And Libs

### Libs (statique)

- SDL3
- SDL3_image
- entt

### Modules
- window_render
- app_loop
- easy_drawing
- rgb_pallet
- ecs_sprite (IA)
- keyboard_manager (IA)

## 🔧 Building

### Requirements

- CMake (>= 3.20)
- A C++20-compatible compiler
- ninja : [Installation docs here](https://github.com/ninja-build/ninja)
- python3

### Instructions

```bash
#LINUX / MACOS
git clone https://github.com/your-username/PickleEngine.git
cd PickleEngine
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt


#WINDOWS
git clone https://github.com/your-username/PickleEngine.git
cd PickleEngine
python -m venv .venv
.venv\Scripts\activate
pip install -r requirements.txt
```

## 🎮 Developing Your Game
Use the 'main.cpp' file located in '/engine_launcher' as the root of your game.
Feel free to modify and customize it as needed.

### Build a project 
```
python3 scripts/tools.py compile --dev
```
### Run
```
#linux
./build-linux/bin/engine_launcher
```

## 🧩 Creating a Module

### Generate a basic module skeleton

```bash
python /script/tools.py new_module name_of_new_module
```

### Edit meta.json as needed

```json
{
    "name": "example_module",
    "description": "desc ... ",
    "dependencies": {
        "libs": ["SDL3"],
        "modules": []
    },
    "functions": [] // optional
}

```