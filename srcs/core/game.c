//game.c===

#include"../../headers/core/game.h"

void game_test(){
    window_init();//init la const window
    rederer_init();//init la const render
    initDeltaTime();//init la const dt
    window_parameter_init();//init la const win_parameter
    pk_run();
}

void pk_run(){

    Sprite sprite;
    sprite_init(&sprite, "assets/pickle/green_pickle.png", 100, 100, 16, 32 );

    while (win_parameter->runing) {
        get_sys_input();
        
        //logiqiz de jeux ici vvvvvv
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);// le BG
        SDL_RenderClear(renderer);//ça efface tout le render

        display_sprite(sprite, 100, 100); 

        updateDeltaTime();
        //printf("FPS:%d\n",dt->fps);

        SDL_RenderPresent(renderer);
        //fin de la logique
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}
//===