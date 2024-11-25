//window.cpp===
#include "../include/allinclude.hpp"


SDL_Window* PkWindow::window_init(const std::string& window_title, int width, int height){
    window = SDL_CreateWindow
    (
        window_title.c_str(),  
        SDL_WINDOWPOS_CENTERED,         // Position X de la fenêtre
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "Erreur de création de la fenêtre : " << SDL_GetError() << std::endl;
        SDL_Quit(); // Nettoyage de SDL
        return nullptr;
    }
    return window;
}

PkWindow::PkWindow()
    : running(true), full_screen(false),
    width(800), height(600), window(nullptr), title("Pickle ENGINE"){
        window = window_init("Pickle ENGINE", width, height);
}

PkWindow::PkWindow(const std::string& window_title)
    : running(true), full_screen(false),
    width(800), height(600), window(nullptr), title(window_title){
        window = window_init(title, width, height);
}


PkWindow::~PkWindow(){
        if (window) {
            SDL_DestroyWindow(window);
        }
}

bool PkWindow::is_running()const{
    return running;
}

bool PkWindow::is_full_screen()const{
    return full_screen;
}

int PkWindow::get_width()const{
    return width;
}

int PkWindow::get_height()const{
    return height;
}

int PkWindow::get_midle_width()const{
    return width/2;
}

int PkWindow::get_midle_height()const{
    return height/2;
}

std::string PkWindow::get_title()const{
    return title;
}

SDL_Window* PkWindow::get_window()const{
    return window;
}

void PkWindow::toggle_full_screen(){
    if (is_full_screen()) {
        // Revenir en mode fenêtre
        SDL_SetWindowFullscreen(window, 0);
        full_screen = false;
    } else {
        // Passer en plein écran
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        full_screen = true;
    }
}

void PkWindow::close(){
    running = false;
}
