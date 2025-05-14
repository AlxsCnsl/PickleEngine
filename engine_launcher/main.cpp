
#include <window_render/window_render.hpp>
#include <app_loop/app_loop.hpp>

int main (){
    WindowRender window = WindowRender("ExampleWindow", 500, 500);
    AppLoop app = AppLoop(window);

    app.setOnInit({
        //logique d'initalisation de l'app
    });

    app.setOnUpdate({
        //logiqe de mise à jours de l'app
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
