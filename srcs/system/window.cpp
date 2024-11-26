//window.cpp===
#include "../include/allinclude.hpp"


SDL_Window* PkWindow::initWindow(const std::string& windowTitle, int width, int height){
    window = SDL_CreateWindow
    (
        windowTitle.c_str(),  
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
    : running(true), fullScreen(false),
    width(800), height(600), window(nullptr), title("Pickle ENGINE"){
        window = initWindow("Pickle ENGINE", width, height);
}

PkWindow::PkWindow(const std::string& windowTitle)
    : running(true), fullScreen(false),
    width(800), height(600), window(nullptr), title(windowTitle){
        window = initWindow(title, width, height);
}


PkWindow::~PkWindow(){
        if (window) {
            SDL_DestroyWindow(window);
        }
}

bool PkWindow::isRunning()const{
    return running;
}

bool PkWindow::isFullScreen()const{
    return fullScreen;
}

int PkWindow::getWidth()const{
    return width;
}

int PkWindow::getHeight()const{
    return height;
}

int PkWindow::getMidleWidth()const{
    return width/2;
}

int PkWindow::getMidleHeight()const{
    return height/2;
}

std::string PkWindow::getTitle()const{
    return title;
}

SDL_Window* PkWindow::getWindow()const{
    return window;
}

void PkWindow::toggleFullScreen(){
    if (isFullScreen()) {
        // Revenir en mode fenêtre
        SDL_SetWindowFullscreen(window, 0);
        fullScreen = false;
    } else {
        // Passer en plein écran
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        fullScreen = true;
    }
}

void PkWindow::close(){
    running = false;
}
