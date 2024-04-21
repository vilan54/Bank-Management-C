#include "system.h"

bool checkPassword(User user, tUserPassword password){
    return (strcmp(user.password, password) == 0);
}

char* getUsersPath() {
    char cwd[MAX_LENGTH];
    static char userPath[MAX_LENGTH * 2]; // Definir una matriz estática para contener la ruta

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        strcpy(userPath, cwd); 
        strcat(userPath, "/users/"); 
    } else {
        perror("getcwd() error");
        return NULL;
    }

    return userPath;
}

char* getAllUsersFile(){
    char *path = getUsersPath();

    strcat(path, "usersFile");

    return path;
}

void writeUsersDniHeader() {
    char *usersFilePath = getAllUsersFile();

    FILE *file = fopen(usersFilePath, "a");
    if (!file) {
        perror("Error al abrir usersFile para escritura");
        return;
    }

    fprintf(file, "-----USERS LIST-----\n");

    fclose(file);
}

bool checkUsersPath() {
    char *path = getUsersPath();
    
    DIR *dir = opendir(path);
    
    if (dir) {
        closedir(dir); 
    } else if (ENOENT == errno) { 
        if (mkdir(path, 0777) == -1) {
            perror("mkdir() error");
            return false;
        }
    } else {
        perror("opendir() error");
        return false;
    }

    char usersFilePath[MAX_LENGTH];
    snprintf(usersFilePath, sizeof(usersFilePath), "%s/usersFile", path);

    FILE *file = fopen(usersFilePath, "r");
    if (file) {
        fclose(file); 
    } else {
        file = fopen(usersFilePath, "w");
        if (!file) {
            perror("Error al crear usersFile");
            return false;
        }
        writeUsersDniHeader();
        fclose(file); 
    }

    return true;
}

tUserDni* getUsersDni(tUserDni *users) {
    char *path = getAllUsersFile();

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printw("Error: El archivo no existe en la ruta proporcionada.\n");
        refresh();
        return NULL;
    }

    if (users == NULL) {
        printw("Error: No se pudo reservar memoria.\n");
        refresh();
        napms(1000);
        return NULL; 
    }

    int numUsers = 0;

    char line[LINE_LENGTH_LIMIT];
    while (fgets(line, LINE_LENGTH_LIMIT, file) != NULL) {
        if (strncmp(line, "Dni: ", 5) == 0) {
            sscanf(line, "Dni: %s", users[numUsers]);
            numUsers++;
        }
    }
    
    fclose(file);
    return users;
}

char* getUserFile(tUserId id) {
    char *path = getUsersPath();     
    char idStr[20]; 

    snprintf(idStr, sizeof(idStr), "%lu", id);
    strcat(path, idStr);

    return path; 
}

void initializeSystem() {
    char *path = getUsersPath();

    if(path == NULL || !checkUsersPath()) {
        printw("ERROR INITIALAZING SYSTEM\n");
    }

}

void startSystem(){
    initscr(); 
    initializeSystem();

    printMainMenu();  
    
    endwin();  
}
