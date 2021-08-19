#ifndef PROGRAMA02_MENU_H
#define PROGRAMA02_MENU_H

#include "btree.h"

class Menu{
private:
    BTree<Videogame> tree;
public:
    Menu();
    void displayMenu();
    void menuOptions(const int&);

    void insertVideogame();
    void deleteVideogame();
    void searchVideogame();
    BTree<Videogame>::Position findVideogame(const long&);
};

#endif //PROGRAMA02_MENU_H
