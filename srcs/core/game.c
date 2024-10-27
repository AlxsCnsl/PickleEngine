#include"../../headers/core/game.h"


void game_test(){
    window_init();//init la const window
    rederer_init();//init la const render
    
    DeltaTime dt;
    initDeltaTime(&dt);
    WindowParameter wp;
    window_parameter_init(window, &wp);
    run(&dt, &wp);
}



void run(DeltaTime *dt, WindowParameter *wp){
    Sprite sprite;
    sprite_init(renderer,&sprite, "assets/pickle/green_pickle.png", 100, 100, 16, 32 );
    while (wp->runing) {
        get_sys_input(window, wp);
        
        //logiqiz de jeux ici vvvvvv
        SDL_SetRenderDrawColor(renderer, 90, 80, 254, 255);// le BG
        SDL_RenderClear(renderer);//ça efface tout le render

        display_sprite(renderer, sprite, 100, 100);

        updateDeltaTime(dt,wp->max_fps);
        //printf("FPS:%d\n",dt->fps);

        SDL_RenderPresent(renderer);
        //fin de la logique
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}