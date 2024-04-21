#ifndef HASH_H
#define HASH_H

#include "types.h"
#include <stdio.h>
#include <ncurses.h>
#include <math.h>
#include <pcre.h>
#include <string.h>

void generateUserId(User*);
void hashUserPassword(User*);
int validateDateFormat(char*);

#endif