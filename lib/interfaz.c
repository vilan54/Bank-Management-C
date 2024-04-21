#include "interfaz.h"

void print_separator() {
  printw("\n**********************************\n");
}

void showUserInformation(User user) {
  clear();
  print_separator();
  printw("          USER INFORMATION");
  print_separator();
  refresh();
  napms(750);

  printw("\nUser ID: %lu\n", user.id);
  printw("\nDNI: %s\n", user.dni);
  printw("\nName: %s\n", user.name);
  printw("\nMoney: %d\n", user.money);
  printw("\nBirthday: %s\n", user.birthday);
  printw("\nNumber of Transactions: %d\n", user.numTransactions);
  napms(850);
  
  printw("\n\n\nPress any key to go back");
  refresh();
  int option;
  scanw("%d\n", &option);
    
}

void showTransactionsInformation(User user) {
  clear();
  print_separator();
  printw("     TRANSACTION INFORMATION");
  print_separator();
  refresh();
  napms(750);

  if(user.numTransactions == 0) {
    printw("\nThere are not transactions yet\n");
  } else {
    for(int i=0; i<user.numTransactions; i++) {
      printw("\n#%d Transaction %s\n", i+1, user.transactions[i].date);
      printw("        Recipient: %s\n", user.transactions[i].recipient);
      printw("        Amount: %d\n", user.transactions[i].amount);
    } 
  }
  refresh();
  napms(1000);

  printw("\n\nPress any key to go back");
  refresh();
  int option;
  scanw("%d\n", &option);
}

void printMoneyMenu(User user, char *action) {
  char title[50]; 
  int i;

  for (i = 0; action[i] != ' ' && action[i] != '\0'; i++) {
      title[i] = toupper(action[i]);
  }
  title[i] = '\0'; 

  bool withdraw = true;
  if(strcmp(title, "ADD") == 0) {
    withdraw = false; 
  }

  clear();
  print_separator();
  printw("            %s MONEY", title);
  print_separator();
  refresh();
  napms(1000);

  printw("How much money do you want to %s your account?\n", action);
  
  int amount, validate, attempts = 3;
  do {
    printw("\nENTER AMOUNT..");
    refresh();
    validate = scanw("%d\n", &amount);

    if(validate != 1) {
      attempts--;
      printw("\nERROR, ARGUMENT NOT VALID\n");
      printw("%d attempts left\n", attempts);
      refresh();
      napms(2000);
    }

    if(amount<1) {
      attempts--;
      validate = 0;
      printw("\nERROR, AMOUNT NOT VALID\n");
      refresh();
      napms(1000);
      printw("%d attempts left\n", attempts);
      refresh();
      napms(2000);
    }

    if(withdraw) {
      if(amount > user.money) {
        printw("\nError: There is not enough money to make this transaction\n");
        refresh();
        napms(1000);
        printw("\nGoing back to user menu..\n");
        refresh();
        napms(1000);
        return;
      }
    } 


  } while(validate != 1 && attempts != 0);
  
  napms(500);
  
  int totalAmount;
  
  if(withdraw) {
    totalAmount = user.money - amount;
  } else {
    totalAmount = user.money + amount;
  }


  if(!updateMoney(user, totalAmount)) {
    clear();
    
    printw("An error has occurred\n");
    refresh();
    napms(2000);
    
    printUserMenu(user.id);
  
  } else {
    printw("\nUpdating your information..\n");
    refresh();
    napms(1000);
    
    printw("\nDone!! Going back to user menu..\n");
    refresh();
    napms(1000);
    
  }

}

void printManageMenu(User user) {
  
  clear();
  print_separator();
  printw("   MANAGE YOU MONEY");
  print_separator();

  printw("\n1... DEPOSIT MONEY TO YOUR ACCOUNT\n");
  printw("\n2... WITHDRAW MONEY FROM YOUR ACCOUNT\n");  
  printw("\n3... BACK\n");
  
  printw("\n\nENTER YOUR CHOICE..");
  refresh();

  int option;    
  scanw("%d\n", &option);

  switch ((option))
  {
  case 1:
    clear();
    printMoneyMenu(user, "deposit to");
    printUserMenu(user.id);
    break;

  case 2:
    clear();
    printMoneyMenu(user, "withdraw from");
    printUserMenu(user.id);
    break;
  
  case 3:
    printUserMenu(user.id);
    break;

  default:
    clear();
    printw("Not an option dumbass\n");
    refresh();
    napms(2000);
    printManageMenu(user);
    break;
  }
}

void makeTransaction(User user) {
  Transaction transaction;
  int amountIsValid, attemps;
  bool userExists;

  clear();
  print_separator();
  printw("          MAKE A TRANSACTION");
  print_separator();
  refresh();
  napms(750);

  printw("You can cancel this operation at any time by entering (e) or (0)\n\n");
  refresh();
  napms(1000);

  attemps = 3;
  do {
    printw("Recipient's Dni: ");
    refresh();
    getstr(transaction.recipient);

    if(strcmp(transaction.recipient, "e") == 0) {
      printw("Canceling operation..\n");
      refresh();
      napms(1000);
      return;
    }

    if(strcmp(transaction.recipient, user.dni) == 0) {
      attemps--;
      printw("\nYou can not make a transaction on yourself.\n%d attemps left..\n\n", attemps);
      refresh();
      napms(1500);
      continue;
    }

    userExists = checkUser(transaction.recipient);
    
    if (!userExists) {
      attemps--;
      printw("\nThe recipient does not exist\n%d attemps left..\n\n", attemps);
      refresh();
      napms(1500); 
    }

  } while (!userExists && attemps > 0);

  if(attemps == 0) {
    printw("Error: maximum number of attempts reached\n\nGoing back to user menu\n");
    refresh();
    napms(1500);
    return;
  }

  attemps = 3;
  do {
    printw("Amount: ");
    refresh();
    scanw("%d", &transaction.amount);
    
    if(transaction.amount == 0) {
      printw("Canceling operation..\n");
      refresh();
      napms(1000);
      return;
    }

    amountIsValid = transaction.amount <= user.money && transaction.amount >= 1;

    if (!amountIsValid) {
        attemps--;
        printw("\nThe amount is not valid\n%d attemps left\n\n", attemps);
        refresh();
        napms(1000); 
    }
  } while (!amountIsValid && attemps > 0);

  if(attemps == 0) {
    printw("Error: maximum number of attempts reached\n\nGoing back to user menu\n");
    refresh();
    napms(1500);
    return;
  }

  time_t now = time(NULL); 
  struct tm *tm_now = localtime(&now);

  strftime(transaction.date, LINE_LENGTH_LIMIT, "%d-%m-%Y", tm_now);
  
  createTransaction(user, transaction, true);
  
}

void printUserMenu(tUserId id) {
  char* pathUser = getUserFile(id);

  clear();

  FILE *file = fopen(pathUser, "r");
  if (!file) {
      printw("\nError at opening user file\n");
      refresh();
      napms(1000);
      printw("\nReturning to main menu . . .\n");
      refresh();
      napms(1000);
      printMainMenu();
  }

  User user = getUser(file);
  fclose(file);

  clear();

  print_separator();
  printw("          USER MENU");
  print_separator();

  printw("\n¡¡Welcome %s!!\n", user.name);

  printw("\n1... SEE YOUR INFORMATION\n");
  printw("\n2... SEE YOUR TRANSACTIONS\n");
  printw("\n3... MANAGE YOUR MONEY\n");
  printw("\n4... MAKE A TRANSACTION\n");  
  printw("\n5... EXIT\n");
  
  printw("\n\nENTER YOUR CHOICE..");
  refresh();

  int option;
    
  scanw("%d\n", &option);

  switch (option){
    case 1:
      showUserInformation(user);
      printUserMenu(id);
      break;

    case 2:
      showTransactionsInformation(user);
      printUserMenu(id);
      break;

    case 3: 
      printManageMenu(user);
      break;
    
    case 4:
      clear();
      makeTransaction(user);
      printUserMenu(id);

    case 5:
      printMainMenu();
      break;
    
    default:
      clear();
      printw("That's not an option dumbass\n");
      refresh();
      napms(2000);
      printUserMenu(id);
      break;
  }

}

bool createAccount(User *user) {
  clear();
  print_separator();
  printw("  CREATE A BANK ACCOUNT");
  print_separator();
  refresh();
  napms(1000);

  printw("We are going to need some data to create your bank account\n\n");
  refresh();
  napms(1000);

  printw("Dni: ");
  refresh();
  getstr(user->dni);
  if(checkUser(user->dni)){
    printw("\nError, user already exists\n");
    refresh();
    napms(1000);
    printw("\nGoing back...\n");
    refresh();
    napms(2500);
    return false;
  }

  printw("Name: ");
  refresh();
  getstr(user->name);

  printw("Password:");
  noecho();
  getstr(user->password);
  echo();
  napms(1000);

  do {
    printw("Birthday (xx/yy/zzzz): ");
    refresh();
    getstr(user->birthday);

    if (validateDateFormat(user->birthday) != 1) {
        printw("\nDate is not in the required format.\n");
        refresh();
        napms(750);
        printw("Try again");
        refresh();
        napms(750);
    }
  } while (validateDateFormat(user->birthday) != 1);

  printw("\n\n¡Perfect, we have all the data necessary!\n");
  refresh();
  napms(1500);
  printw("\nCreating user...\n");
  refresh();
  napms(1000);

  generateUserId(user);
  int cu = createUser(*user);
  switch(cu) {
    case 0:
        printw("User created\n");
        break;
    case -1:
        printw("User already exists\n");
        break;
    case -2:
        printw("Error creating file\n");
        break;
    default:
        printw("Unknown error\n");
  }
  refresh();
  napms(1000);

  return true;
}

bool signIn(User *user) {
  int tries = 3;
  bool attemptLogin = false; 

  clear();
  print_separator();
  printw("            LOG IN");
  print_separator();
  refresh();
  napms(500);

  printw("Dni:");
  refresh();
  getstr(user->dni);
  napms(1000);
  if(!checkUser(user->dni)) {
    printw("\nError, user does not exist\n");
    refresh();
    napms(750);
    printw("\nGoing back ...\n");
    refresh();
    napms(750);
    return false;
  }

  do {
    printw("Password:");
    refresh();
    noecho();
    getstr(user->password); // Asume que user es una variable accesible previamente definida
    echo();
    napms(1000); // Pequeña pausa por motivos de UX

    attemptLogin = logIn(user); // Intenta iniciar sesión una vez y guarda el resultado


    if (!attemptLogin) {
        tries--;
        if (tries > 0) { // Solo muestra el mensaje si aún quedan intentos
            printw("\nIncorrect password, %d tries remaining\n", tries);
            refresh();
            napms(1500);
        }
    } else {
        return true; // Contraseña correcta, retorna true para indicar éxito
    }
  } while (!attemptLogin && tries > 0);

  if (!attemptLogin) { // Si se sale del bucle porque se agotaron los intentos, muestra un mensaje final.
    printw("\nNo more tries left. Access denied.\n");
    refresh();
    napms(1500);
  }
  return false;

}

void printMainMenu() {
  User user;

  clear();
  print_separator();
  printw("  WELCOME TO BANK ACCOUNT SYSTEM");
  print_separator();

  printw("DEVELOPER-Pablo Vilan\n");

  printw("\n1... CREATE A BANK ACCOUNT\n");
  printw("\n2... ALREADY A USER? SIGN IN\n");  
  printw("\n3... EXIT\n");
  
  printw("\n\nENTER YOUR CHOICE..");
  refresh();

  int option;
    
  scanw("%d\n", &option);

  switch (option)
  {
    case 1:
      if(createAccount(&user)) {
        printUserMenu(user.id);
      } else {
        printMainMenu();
      }
      break;

    case 2:
      if(signIn(&user)) {
        printUserMenu(user.id);
      } else {
        printMainMenu();
      }
      break;

    case 3:
      return;
    
    default:
      clear();
      printw("That's not an option dumbass\n");
      refresh();
      napms(2000);
      printMainMenu();
      break;
  }
  
}
