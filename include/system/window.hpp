#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../allinclude.hpp"

class PkWindow{

    private:

        //var
        bool running;
        bool full_screen;
        int width;
        int height;
        SDL_Window* window;
        std::string title;

        //def
        SDL_Window* window_init(const std::string& window_title, int width, int height);

    public:

        PkWindow();
        PkWindow(const std::string& window_title);
        ~PkWindow();

        bool is_running()const;
        bool is_full_screen()const;
        int get_width()const;
        int get_height()const;
        int get_midle_width()const;
        int get_midle_height()const;
        std::string get_title()const;
        
        SDL_Window* get_window()const;
    
        void toggle_full_screen();//switch window mod and fullscreen
        void close();
};

#endif //WINDOW_HPP
