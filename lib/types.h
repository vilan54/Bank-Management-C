#ifndef BANK_MANAGEMENT_TYPES_H
#define BANK_MANAGEMENT_TYPES_H

#define LINE_LENGTH_LIMIT 50
#define MAX_USERS 100
#define MAX_TRANSACTIONS 200

typedef unsigned long tUserId;

typedef char tUserDni[LINE_LENGTH_LIMIT];

typedef char tUserName[LINE_LENGTH_LIMIT];

typedef char tUserPassword[LINE_LENGTH_LIMIT];

typedef int tUserMoney;

typedef int tUserNumTransactions;

typedef char tDate[LINE_LENGTH_LIMIT];

typedef struct {
    tUserDni recipient;
    tUserMoney amount;
    tDate date;
} Transaction;

typedef struct {
    tUserId id;
    tUserDni dni;
    tUserName name;
    tUserPassword password;
    tUserMoney money;
    tDate birthday;
    tUserNumTransactions numTransactions;
    Transaction transactions[MAX_TRANSACTIONS];
} User;

#endif