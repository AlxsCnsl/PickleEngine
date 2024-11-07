#ifndef WINDOW_H
#define WINDOW_H

#include<stdio.h>
#include<SDL2/SDL.h>
#include<string.h>

#include "system/configuration.h"

typedef struct{
    int runing;
    int is_full_screen;
    int max_fps;
    int x_size;
    int y_size;
    int x_center;
    int y_center;
    SDL_Event event;
}WindowParameter;

extern SDL_Window* window ;
extern char WIN_TITLE[128];
extern WindowParameter* win_parameter;

void window_init();// initialize the constant window 

void update_window_size_parameter();//change window size

void toggle_full_screen();//switch window mod and fullscreen

void window_parameter_init();//initialize the constant win_parameter

#endif //WINDOW_H
