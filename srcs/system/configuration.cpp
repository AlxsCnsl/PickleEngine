//configuration.c===
#include "../../headers/system/configuration.hpp" 


int is_int(std::string str){
    std::istringstream test(str);
    int num;
    test >> num;
    if (test.fail()) {
        std::cerr << "Conversion échouée.\n";
    } else {
        return 1;
    }
    return 0;
}

int str_to_int(std::string str){
    std::istringstream iss(str);
    int num;
    iss >> num;
    return num;
}


int get_int_seting_config(std::string file_name, std::string target_seting, int default_setting){
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier : "<< file_name <<"\n";
        return 1;
    }
    std::string line;
    while (std::getline(file, line))
    {
        if(line == target_seting){
            std::getline(file, line);
            if(is_int(line)){
                int int_string = str_to_int(line);
                std::cout << "[" << target_seting << "]" << "deviens " << int_string << std::endl;
                return int_string;
            }
        }
    }
    file.close();
    return default_setting;
}


//===