//main.c===
#include "main.hpp"

//const pour GAME


int main(int argc, char** argv) {
    int a(5);
    std::cout<<"le nombre est: "<< a << std::endl;
    get_int_seting_config("system_conf.txt", "~MAX_FPS", 80);
    return 0;
}
//===