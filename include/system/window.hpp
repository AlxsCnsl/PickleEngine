#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../allinclude.hpp"

class PkWindow{

    private:

        //var
        bool running;
        bool fullScreen;
        int width;
        int height;
        SDL_Window* window;
        std::string title;

        //def
        SDL_Window* initWindow(const std::string& windowTitle, int width, int height);

    public:

        PkWindow();
        PkWindow(const std::string& windowTitle);
        ~PkWindow();

        bool isRunning()const;
        bool isFullScreen()const;
        int getWidth()const;
        int getHeight()const;
        int getMidleWidth()const;
        int getMidleHeight()const;
        std::string getTitle()const;
        
        SDL_Window* getWindow()const;
    
        void toggleFullScreen();//switch window mod and fullscreen
        void close();
};

#endif //WINDOW_HPP
