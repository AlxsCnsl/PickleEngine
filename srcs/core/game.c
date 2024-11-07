//game.c===
#include"../../headers/core/game.h"

void pk_run(){
    window_init();//init la const window
    rederer_init();//init la const render
    initDeltaTime();//init la const dt
    window_parameter_init();//init la const win_parameter
    if(get_seting_config("SYS_CONF.txt", "~OPEN_IN_FULL_SCREEN",0)==1){
    toggle_full_screen();
    }
    //START INIT//=============================================================

    Object* pickle = object_init("assets/pickle/test_green_pickle.png", 32, 64);
    replace_object(pickle, 12, 10);

    Object* pickle2 = object_init("assets/pickle/test_yelow_pickle.png", 32, 64);
    replace_object(pickle2, 120, 10);

    Object* block = object_init("assets/block/basic.png", 1024,64 );
    replace_object(block, -150, 450);
    int grave = 10;

    //END INIT//===============================================================
    while (win_parameter->runing) {
        get_sys_input();
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);//BG
        SDL_RenderClear(renderer);//Clear renderer in window
        //START LOOP //========================================================

        display_object(block);
        display_object(pickle);
        display_object(pickle2);

        pickle->collide_box->y_speed = grave;
        pickle2->collide_box->y_speed = grave;

        y_move_object(pickle, pickle->collide_box->y_speed);
        y_move_object(pickle2, pickle2->collide_box->y_speed);

        check_collision(pickle->collide_box, block->collide_box);
        check_collision(pickle2->collide_box, block->collide_box);
        
        //END LOOP//===========================================================
        updateDeltaTime();
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}
//===