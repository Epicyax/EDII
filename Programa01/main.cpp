#include "menu.h"

int main(){
    Menu myMenu;
    int opcion;
    do{
        opcion = myMenu.displayMenu();
    }while(opcion!=7);

    return 0;
}
