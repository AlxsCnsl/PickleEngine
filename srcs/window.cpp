//window.c===
#include "../headers/window.hpp"


bool running;
bool is_full_screen;
int max_fps;
int width;
int height;
SDL_Event* event;
SDL_Window* window;
std::string title;


PkWindow::PkWindow()
    : running(true), is_full_screen(false), max_fps(60), 
    width(800), height(600), event(nullptr), window(nullptr), title("Pickle ENGINE"){
        window = SDL_CreateWindow(title.c_str(),  
        SDL_WINDOWPOS_CENTERED,         // Position X de la fenêtre
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
        );
}

PkWindow::PkWindow(const std::string& window_title);
PkWindow::~PkWindow();

int PkWindow::get_width()const;
int PkWindow::get_height()const;
int PkWindow::get_midle_width()const;
int PkWindow::get_midle_height()const;
bool PkWindow::is_running()const;

SDL_Event* PkWindow::get_event()const;
SDL_Window* PkWindow::get_window()const;

void PkWindow::toggle_full_screen();//switch window mod and fullscreen


/*
char WIN_TITLE[128] = "Pickle Jumper";
SDL_Window* window = NULL;
WindowParameter* win_parameter = NULL;


void window_init(){// initialize the constant window 
    if (SDL_Init(SDL_INIT_VIDEO) < 0){ //initializ SDL
        printf("Erreur lors de l'initialisation de SDL: %s\n", SDL_GetError());
    }
    // make window in creen
    window = SDL_CreateWindow(WIN_TITLE, //WIN_TITLE is constant
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          get_seting_config("SYS_CONF.txt", "~SIZE_X_SCREEN", 800),
                                          get_seting_config("SYS_CONF.txt", "~SIZE_Y_SCREEN", 600),
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
    }
}

void update_window_size_parameter(){//change window size
    SDL_GetWindowSize(window, &win_parameter->x_size, &win_parameter->y_size);
    win_parameter->x_center = win_parameter->x_size/2;
    win_parameter->y_center = win_parameter->y_size/2;
}

void toggle_full_screen(){//switch window mod and fullscreen
    if (win_parameter->is_full_screen) {
        // Revenir en mode fenêtre
        SDL_SetWindowFullscreen(window, 0); // 0 = window mod
        win_parameter->is_full_screen = 0;
    } else {
        // Passer en plein écran
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        win_parameter->is_full_screen = 1;
    }
    update_window_size_parameter();
}

void window_parameter_init(){//initialize the constant win_parameter
    win_parameter = (WindowParameter*)malloc(sizeof(WindowParameter));
    win_parameter->runing = 1;
    win_parameter->is_full_screen = 0;
    win_parameter->max_fps = 60;
    update_window_size_parameter();
}
*/

//===