
#include <window_render/window_render.hpp>
#include <app_loop/app_loop.hpp>
#include<easy_drawing/easy_drawing.hpp>

int main (){
    WindowRender* window = new WindowRender("ExampleWindow", 600, 600);
    AppLoop app = AppLoop(window);

    app.setOnInit([&app](float deltatime){
        app.getWindow()->setClearRGB(255, 0, 0);
    });

    app.setOnUpdate([&app](float deltatime){

    });

    app.setOnRender([&app](float deltatime){
        WindowRender::ClearRGB rgb = app.getWindow()->getClearRGB();
        int factor = 5;
        for(int i = 0; i< factor; i++){
            if (rgb.red == 255 && rgb.green < 255 && rgb.blue == 0) {  // Rouge → Jaune
                    rgb.green++;
                } else if (rgb.red > 0 && rgb.green == 255 && rgb.blue == 0) {  // Jaune → Vert
                    rgb.red--;
                } else if (rgb.red == 0 && rgb.green == 255 && rgb.blue < 255) {  // Vert → Cyan
                    rgb.blue++;
                } else if (rgb.red == 0 && rgb.green > 0 && rgb.blue == 255) {  // Cyan → Bleu
                    rgb.green--;
                } else if (rgb.red < 255 && rgb.green == 0 && rgb.blue == 255) {  // Bleu → Magenta
                    rgb.red++;
                } else if (rgb.red == 255 && rgb.green == 0 && rgb.blue > 0) {  // Magenta → Rouge
                    rgb.blue--;
                }
        }
        app.getWindow()->setClearRGB(rgb.red, rgb.green, rgb.blue);
        
        WindowRender* window = app.getWindow();
        PutPixel(window, 320, 240, {255, 0, 0, 255});
        HLine(window, 100, 100, 200, {0, 255, 0, 255});
        VLine(window, 100, 100, 200, {0, 0, 255, 255});
        DrawRect(window, 300, 200, 100, 50, {0, 0, 0, 255});
        FillRect(window, 100, 300, 150, 80, {255, 0, 255, 255});
        DrawCircle(window, 500, 350, 40, {0, 128, 128, 255});
    });

    app.setOnShutdown({
        //logique de de fermeture de l'app
    });

    app.run();


    return 0;
}