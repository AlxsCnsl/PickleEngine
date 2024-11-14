//configuration.c===
#include "../../headers/system/configuration.h" 


int str_debuts_str(char* str1, char* str2){ //Vérifie si str1 est dans str2() (pour le cross OS)
    int i;
    for(i = 0; i<strlen(str1); i++)
    {
        if(str1[i] != str2[i])
        {
            return 1;
        }
    }
    return 0;
}

int get_seting_config(char* file_name, char* target_seting, int default_setting){
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier %s\n", file_name);
        return default_setting;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)!= NULL &&//while  le while pour ignorer tout jusqu'a la target
    str_debuts_str(target_seting, buffer)){}//while 
    if(buffer == NULL){ // à modifié
        printf("[%s] NO SEEK in /%s", target_seting, file_name);
        return default_setting;
    }
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
    printf("NEW: [%s] = %d\n", target_seting, atoi(buffer));
    return atoi(buffer);//transforme le char buffer en int 
}


//===