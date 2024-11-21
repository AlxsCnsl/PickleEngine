#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "allinclude.hpp"

class PkWindow{

    private:
        bool running;
        bool full_screen;
        int width;
        int height;
        SDL_Window* window;
        //PkRenderer renderer;
        std::string title;

        SDLWindow* window_init();
    public:

        Pk_Window();
        PkWindow(const std::string& window_title);
        ~PkWindow();


        bool is_running()const;
        bool is_full_screen()const;
        int get_width()const;
        int get_height()const;
        int get_midle_width()const;
        int get_midle_height()const;
        stt::string get_title()const;

        SDL_Window* get_window()const;
        SDL_Renderer* get_renderer()const;
    
        void toggle_full_screen();//switch window mod and fullscreen
};

#endif //WINDOW_HPP
