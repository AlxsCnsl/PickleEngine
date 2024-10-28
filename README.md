DEV_LIB_TOOLS;

    #CONST==========
        extern SDL_Window* window ; [window]
        /
        extern char WIN_TITLE[128]; [WIN_TITLE]
        /
        extern WindowParameter* win_parameter; [win_parameter]
            → typedef struct{
                int runing;
                int is_full_screen;
                int max_fps;
                int x_size;
                int y_size;
                int x_center;
                int y_center;
                SDL_Event event;
            }WindowParameter;
        /
        extern SDL_Renderer* renderer; [renderer]
        /
    ===================

    #WINDOW.*==========
        void window_init();
            → initialize the constant "window"

        void update_window_size_parameter();
            → update window size in parameter

        void toggle_full_screen();
            → switch window mod and fullscreen

        void window_parameter_init();
            → initialize the constant "win_parameter"


    #RENDERER.*==========
        void rederer_init()
            → initialize the constant "renderer"


    #DELTATIME.*==========
        void initDeltaTime();
            → initialize the constant "dt"

        void updateDeltaTime();
            → update the constant "dt" and other
        
        int getFPS();
            → get actualy FPS


    #GAME.*==========
        void run();
            → run game


    #SYS_INPUT.*==========
        void get_sys_input();
            → get input of engine system interaction


    #SPRITE.*==========
        SDL_Texture* make_texture(char name_img[]);
            → make SDL texture with name_path of image.png

        void sprite_init(Sprite* sprite, char* path_name, int x, int y, int width, int height);
            → init one sprite

        void display_sprite(Sprite sprite, int x_pose, int y_pose);
            → dispaly one sprite

    

USER_TOOLS;

    //to initialize the game variables
    → void picklengine_init()
    
    //game event loop
    → void picklengine_loop()