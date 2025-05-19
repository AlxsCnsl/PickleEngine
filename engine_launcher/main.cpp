
#include <window_render/window_render.hpp>
#include <app_loop/app_loop.hpp>
#include<easy_drawing/easy_drawing.hpp>
#include<rgb_pallet/rgb_pallet.hpp>

int main (){
    WindowRender* window = new WindowRender("ExampleWindow", 600, 600);
    AppLoop app = AppLoop(window);

    app.setOnInit([&app](float deltatime){
        app.getWindow()->setClearRGBA(PKRGB::L_GRAY);
    });

    app.setOnUpdate([&app](float deltatime){

    });

    app.setOnRender([&app](float deltatime){
  
       WindowRender* window = app.getWindow();
        PutPixel(window, 320, 240, {255, 0, 0, 255});
        HLine(window, 100, 100, 200, {0, 255, 0, 255});
        VLine(window, 100, 100, 200, {0, 0, 255, 255});
        DrawRect(window, 300, 200, 100, 50, {0, 0, 0, 255});
        FillRect(window, 100, 300, 150, 80, PKRGB::RED);
        DrawCircle(window, 500, 350, 40, PKRGB::BLUE);
        DrawCircle(window, 480, 320, 45, PKRGB::PINK);
    });

    app.setOnShutdown({
        //logique de de fermeture de l'app
    });

    app.run();


    return 0;
}