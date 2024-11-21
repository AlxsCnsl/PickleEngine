#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "allinclude.hpp"

class PkWindow{

    private:
        bool running;
        bool is_full_screen;
        int max_fps;
        int width;
        int height;
        SDL_Event* event;
        SDL_Window* window;
        std::string title;

    public:

        PkWindow();
        PkWindow(const std::string& window_title);
        ~PkWindow();

        int get_width()const;
        int get_height()const;
        int get_midle_width()const;
        int get_midle_height()const;
        bool is_running()const;

        SDL_Event* get_event()const;
        SDL_Window* get_window()const;
    
        void toggle_full_screen();//switch window mod and fullscreen
};

#endif //WINDOW_HPP
