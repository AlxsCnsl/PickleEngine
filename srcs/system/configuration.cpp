//configuration.c===
#include "../../include/system/configuration.hpp" 


int isNumber(std::string str){
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

int strToInt(std::string str){
    std::istringstream iss(str);
    int num;
    iss >> num;
    return num;
}


int getIntSetingConfig(std::string fileName, std::string targetSeting, int defaultSetting){
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier : "<< fileName <<"\n";
        return 1;
    }
    std::string line;
    while (std::getline(file, line))
    {
        if(line == targetSeting){
            std::getline(file, line);
            if(isNumber(line)){
                int intString = strToInt(line);
                std::cout << "[" << targetSeting << "]" << "deviens " << intString << std::endl;
                return intString;
            }
        }
    }
    file.close();
    return defaultSetting;
}


//===