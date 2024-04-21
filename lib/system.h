#ifndef SYSTEM_H
#define SYSTEM_H

#define USERS_PATH "/users"
#define MAX_LENGTH 256

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <ncurses.h>
#include "interfaz.h"


void initializeSystem();
void startSystem();
char* getUsersPath();
tUserDni* getUsersDni(tUserDni*);
char* getAllUsersFile();
char* getUserFile(tUserId);
bool checkPassword(User, tUserPassword);


#endif 