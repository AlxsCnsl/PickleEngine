#ifndef WINDOW_H
#define WINDOW_H

#include<stdio.h>
#include<SDL2/SDL.h>
#include<string.h>

typedef struct{
    int runing;
    int is_full_screen;
    int max_fps;
    int x_size;
    int y_size;
    int x_center;
    int y_center;
    SDL_Event event
}WindowParameter;




SDL_Window* window_init(char window_name[]);

void update_window_size_parameter(SDL_Window* window, WindowParameter* wp);

void toggle_full_screen(SDL_Window* window, WindowParameter* wp);

void window_parameter_init(SDL_Window* window, WindowParameter* wp);

#endif //WINDOW_H
