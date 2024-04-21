#include "system.h"

int main(){
    initscr(); 
    initializeSystem();

    printMainMenu();  // Imprimir el menú
    
    endwin();  // Finalizar ncurses
    return 0;
}