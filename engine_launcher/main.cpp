
#include <window_render/window_render.hpp>
#include <app_loop/app_loop.hpp>

int main (){
    WindowRender* window = new WindowRender("ExampleWindow", 500, 5000);
    AppLoop app = AppLoop(window);

    app.setOnInit([&app](float deltatime){
        app.getWindow()->setClearRGB(255, 0, 0);
    });

    app.setOnUpdate([&app](float deltatime){
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
    });

    app.setOnRender({
        //logique de rendue 
    });

    app.setOnShutdown({
        //logique de de fermeture de l'app
    });

    app.run();


    return 0;
}