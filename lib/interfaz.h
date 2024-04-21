#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
#include "bank.h"
#include "hash.h"

void printMainMenu();
void printManageMenu(User);
void printUserMenu(tUserId);

#endif
