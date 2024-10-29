//game.c===

#include"../../headers/core/game.h"

void game_test(){

    pk_run();
}

void pk_run(){
    window_init();//init la const window
    rederer_init();//init la const render
    initDeltaTime();//init la const dt
    window_parameter_init();//init la const win_parameter
    //START INIT//=============================================================

    Sprite* sprite = sprite_init("assets/pickle/green_pickle.png", 10, 10, 16, 32 );

    Sprite* palteform = sprite_init("assets/block/basic.png", 10, 42, 16, 16);

    //END INIT//===============================================================
    while (win_parameter->runing) {
        get_sys_input();
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);//BG
        SDL_RenderClear(renderer);//Clear renderer in window
        //START LOOP //========================================================

        display_sprite(sprite);
        sprite->y_pose += 10;
        display_sprite(palteform);

        //END LOOP//===========================================================
        updateDeltaTime();
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}
//===