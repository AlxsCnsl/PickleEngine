# 🥒 PickleEngine

**PickleEngine** is a modular C++ game engine based on SDL3. Its goal is to provide a simple, extensible, and eventually cross-platform architecture for quickly creating games (2D for now).

[Link to SDL ](https://github.com/libsdl-org/SDL)
[Link to SDL_image](https://github.com/libsdl-org/SDL_image)

---

## ✨ Features

- 🔌 Easy-to-integrate module/plugin system

---

## 📦 Included Modules

| Module Name         | Description                               | Documentation              |
|---------------------|-------------------------------------------|----------------------------|
| `window_render`     | Simplified classes for SDL3 windows       |[window_render docs](https://github.com/AlxsCnsl/PickleEngine/blob/main/modules/window_render/README.md)|
| `app_loop`          | Simplified loops for your app             |[app_loop docs](https://github.com/AlxsCnsl/PickleEngine/blob/main/modules/app_loop/README.md)|
---

## 🔧 Building

### Requirements

- CMake (>= 3.20)
- A C++20-compatible compiler
- ninja : Installation docs [here](https://github.com/ninja-build/ninja)

### Instructions

```bash
git clone https://github.com/your-username/PickleEngine.git
cd PickleEngine
chmod +x scripts/chmoderall.sh
./scripts/update_sdl3.sh
```

## 🎮 Developing Your Game
Use the 'main.cpp' file located in 'engine_launcher' as the root of your game.
Feel free to modify and customize it as needed.
A 'conf.json' file is provided for some modules or for your own configuration.

### Build
```
#linux 
./scripts/build_linux.sh 
./scripts/build_linux_release.sh #for_publishing

#macos

#windows
```
### Run
```
./build/bin/engine_launcher
```

## 🧩 Creating a Module

### Generate a basic module skeleton
```bash
./script/new_module.sh
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