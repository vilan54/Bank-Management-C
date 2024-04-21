#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "types.h"
#include "system.h"
#include "hash.h"
#include "interfaz.h"

int createUser(User);
bool checkUser(tUserDni);
char* checkCredentials(User);
bool logIn(User*);
User getUser(FILE*); 
Transaction* getTransactions(User*);
bool updateMoney(User, tUserMoney);
bool createTransaction(User, Transaction, bool);

#endif