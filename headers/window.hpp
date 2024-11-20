#ifndef WINDOW_H
#define WINDOW_H

#include "allinclude.hpp"

class PkWindow{

    private:
        int runing;
        int is_full_screen;
        int max_fps;
        int width;
        int height;
        SDL_Event event;
    public:

        PkWindow();
        PkWindow(std::string window_tilte);
        ~PkWindow();

        int get_width();
        int get_height();
        int get_midle_width();
        int get_midle_height();

        void toggle_full_screen();//switch window mod and fullscreen
}

#endif //WINDOW_H
