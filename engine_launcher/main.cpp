
#include <window_render/window_render.hpp>
#include <app_loop/app_loop.hpp>
#include<easy_drawing/easy_drawing.hpp>
#include<rgb_pallet/rgb_pallet.hpp>
#include<SDL3_image/SDL_image.h>
#include<SDL3/SDL.h>

int main (){
    WindowRender* window = new WindowRender("ExampleWindow", 500, 500);
    AppLoop app = AppLoop(window);

    app.setOnInit([&app](float deltatime){
        app.getWindow()->setClearRGBA(PKRGB::L_GRAY);
    });

    app.setOnUpdate([&app](float deltatime){

    });

    app.setOnRender([&app](float deltatime){

        const char* basePath = SDL_GetBasePath();
        std::string assetPath = std::string(basePath) + "assets/pickle.png";

        WindowRender* window = app.getWindow();
        SDL_Texture* texture = IMG_LoadTexture(window->getRenderer(), assetPath.c_str());
        if(!texture){std::cout << "Erreur SDL_image : " << SDL_GetError() << std::endl;}
        SDL_SetTextureScaleMode(texture, SDL_ScaleMode::SDL_SCALEMODE_PIXELART);
        SDL_FRect rect;
        rect.x = 0;rect.y = 0;rect.h = 100.0; rect.w = 100.0;
        SDL_RenderTexture(window->getRenderer(), texture, nullptr, &rect);
        
    });

    app.setOnShutdown({
        //logique de de fermeture de l'app
    });

    app.run();


    return 0;
}