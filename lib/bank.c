#include "bank.h"

int writeTransactionData(int numTransaction, Transaction transaction, char *path, bool operation) {
    FILE *file = fopen(path, "a");
    if (!file) {
        return 1;
    }

    fprintf(file, "Transaction %d\n", numTransaction);
    if(operation){
        fprintf(file, "    Recipient: %s\n", transaction.recipient);
    } else {
        fprintf(file, "    Transmitter: %s\n", transaction.recipient);
    }
    fprintf(file, "    Amount: %d\n", transaction.amount);
    fprintf(file, "    Date: %s\n\n", transaction.date);

    fclose(file);

    return 0;

}

bool createTransaction(User user, Transaction newTransaction, bool operation) {
    char *path = getUserFile(user.id);
    user.numTransactions++;
    bool notFound = true;

    FILE *file = fopen(path, "r+");
    if (!file) {
        return false;
    }

    char line[MAX_LENGTH];
    long int pos = 0;
    
     while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "NumTransactions:", 16) == 0) {
             notFound = false;
             fseek(file, pos, SEEK_SET);
             fprintf(file, "NumTransactions: %d\n", user.numTransactions);
             break;
        }
        pos = ftell(file);
    }
    fclose(file);

    if(notFound || writeTransactionData(user.numTransactions, newTransaction, path, operation)==1) return false;

    User temp;

    strcpy(temp.dni, newTransaction.recipient);
    generateUserId(&temp);

    printw("Temp: %ld", temp.id);
    refresh();

    char *pathRecipient = getUserFile(temp.id);
    printw("%s\n", pathRecipient);
    refresh();
    napms(2000);

    FILE *fileRecipient = fopen(pathRecipient, "r");

    if (fileRecipient == NULL) {
        printw("\nError\n");
        refresh();
        napms(1000);
        return false;
    }

    User recipient = getUser(fileRecipient);
    fclose(fileRecipient);

    int userMoney = user.money - newTransaction.amount;
    int recipientMoney = recipient.money + newTransaction.amount;
    
    if(updateMoney(user, userMoney) && updateMoney(recipient, recipientMoney)){
        return true;
    } else {
        return false;
    }
    
}

bool checkUser(tUserDni dni) {
    tUserDni *users = (tUserDni *)malloc(100 * sizeof(tUserDni));
    if (users == NULL) {
        printw("Error: No se pudo reservar memoria.\n");
        refresh();
        napms(1000);
        return false;
    }
    
    users = getUsersDni(users);

    for(int i = 0; i < MAX_USERS; i++) {
        if (users[i][0] == '\0') {
            break;
        }
        refresh();
        if(strcmp(users[i], dni) == 0) {
            free(users); 
            return true;
        }
    }

    free(users); 
    return false;
}

void writeDataUser(FILE *file, User user) { 
    fprintf(file, "------USER------\n");
    fprintf(file, "Id: %lu\n", user.id);
    fprintf(file, "Dni: %s\n", user.dni);
    fprintf(file, "Name: %s\n", user.name);
    fprintf(file, "Password: %s\n", user.password);
    fprintf(file, "Birthday: %s\n", user.birthday);
    fprintf(file, "NumTransactions: 0\n");
    fprintf(file, "Money: 0\n\n\n");
    fprintf(file, "------TRANSACTIONS------\n");

}

int createUser(User newUser) {
    hashUserPassword(&newUser);

    char *pathFile = getUserFile(newUser.id);

    FILE *file = fopen(pathFile, "r");
    if(file != NULL) {
        fclose(file);
        return -1;  
    } else {
        file = fopen(pathFile, "w");

        if (file == NULL) {
            return -2; 
        }
        writeDataUser(file, newUser);
        fclose(file);
    }

    char *usersFilePath = getAllUsersFile();

    FILE *fileList = fopen(usersFilePath, "a");
    if (!fileList) {
        perror("Error al abrir usersFile para escritura");
        return -2;
    }

    fprintf(fileList, "Dni: %s\n", newUser.dni);

    fclose(fileList);
    return 0;

}

bool logIn(User *user) {
    generateUserId(user);

    char *path = getUserFile(user->id);

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        return false;
    } else {
        User userExist = getUser(file);
        fclose(file); 
        hashUserPassword(user); 
        if (strcmp(user->password, userExist.password) == 0) {
            return true;
        }
        return false;
    }
}

void copyArray(Transaction source[], Transaction destination[], int size) {
    for (int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}

User getUser(FILE* file) {
    User user;
    char line[MAX_LENGTH];
    int i=0;
    Transaction transactions[MAX_TRANSACTIONS];

    user.numTransactions = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Id:", 3) == 0) {
            sscanf(line, "Id: %lu", &user.id);
            
        } else if (strncmp(line, "Dni:", 4) == 0) {
            sscanf(line, "Dni: %s", user.dni);
        
        } else if (strncmp(line, "Name:", 5) == 0) {
            sscanf(line, "Name: %s", user.name);
         
        } else if (strncmp(line, "Password:", 6) == 0) {
            sscanf(line, "Password: %s", user.password);
            
        } else if (strncmp(line, "Money:", 6) == 0) {
            sscanf(line, "Money: %d", &user.money);
            
        } else if (strncmp(line, "Birthday:", 6) == 0) {
            sscanf(line, "Birthday: %s", user.birthday);
            
        } else if (strncmp(line, "NumTransactions:", 16) == 0) {
            sscanf(line, "NumTransactions: %d", &user.numTransactions);
            
        } else if (strstr(line, "Transaction") != NULL) {
            fgets(line, LINE_LENGTH_LIMIT, file);
            sscanf(line, "    Recipient: %s", transactions[i].recipient);
            
            fgets(line, LINE_LENGTH_LIMIT, file);
            sscanf(line, "    Amount: %d", &transactions[i].amount);
            
            fgets(line, LINE_LENGTH_LIMIT, file);
            sscanf(line, "    Date: %s", transactions[i].date);
            
            fgets(line, LINE_LENGTH_LIMIT, file);  // Leer "Money:"
            i++;
        }
    }
    copyArray(transactions, user.transactions, i);

    return user;
}

bool updateMoney(User user, tUserMoney amount) {
    char *path = getUserFile(user.id);
    bool notFound = true;

    FILE *fp = fopen(path, "r");
    if (!fp) {
        return false;
    }

    FILE *fpTemp = fopen("tempfile", "w");
    if (!fpTemp) {
        fclose(fp);
        return false;
    }

    char line[MAX_LENGTH];
    while(fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "Money: ", 6) == 0) {
            notFound = false;
            char newLine[MAX_LENGTH];
            sprintf(newLine, "Money: %d", amount);
            fprintf(fpTemp, "%s\n", newLine);
        } else {
            fputs(line, fpTemp);
        }
    }

    fclose(fp);
    fclose(fpTemp);


    if(notFound) return false;

    remove(path);
    rename("tempfile", path);

    Transaction transaction;
    strcpy(transaction.recipient, "yourself");
    transaction.amount = amount;
    time_t now = time(NULL); 
    struct tm *tm_now = localtime(&now);

    strftime(transaction.date, LINE_LENGTH_LIMIT, "%d-%m-%Y", tm_now);

    return true;



}
