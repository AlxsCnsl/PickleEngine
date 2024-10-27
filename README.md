DEV_TOOLS;
    #CONST==========
        extern SDL_Window* window ; [window]
        extern char WIN_TITLE[128]; [WIN_TITLE]
        extern WindowParameter* win_parameter; [win_parameter]
        extern SDL_Renderer* renderer; [renderer]
    ==========

    #WINDOW==========
        void window_init();
            → initialize the constant window

        void update_window_size_parameter(WindowParameter* wp);
            → change window size

        void toggle_full_screen(WindowParameter* wp);
            → switch window mod and fullscreen

        void window_parameter_init(WindowParameter* wp);
            → initialize the constant win_parameter
    ===================================================

USER_TOOLS;

    //to initialize the game variables
    → void picklengine_init()
    
    //game event loop
    → void picklengine_loop()