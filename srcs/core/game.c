//game.c===
#include"../../headers/core/game.h"

void pk_run(){
    window_init();//init la const window
    rederer_init();//init la const render
    initDeltaTime();//init la const dt
    window_parameter_init();//init la const win_parameter
    //START INIT//=============================================================

    Object* pickle = object_init("assets/pickle/eloane_pickle.png", 16, 32);
    replace_object(pickle, 5, 10);
    Object* block = object_init("assets/block/basic.png", 16, 16);
    replace_object(block, 10, 500);
    int grave = 10;

    //END INIT//===============================================================
    while (win_parameter->runing) {
        get_sys_input();
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);//BG
        SDL_RenderClear(renderer);//Clear renderer in window
        //START LOOP //========================================================

        display_object(block);
        display_object(pickle);

        pickle->collide_box->y_speed = grave;
        y_move_object(pickle, pickle->collide_box->y_speed);
        check_collision(pickle->collide_box, block->collide_box);
        
        //END LOOP//===========================================================
        updateDeltaTime();
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}
//===