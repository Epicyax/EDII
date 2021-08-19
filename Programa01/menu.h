#ifndef PROGRAMA01_MENU_H
#define PROGRAMA01_MENU_H

#include <iostream>
#include <string>
#include "list.h"

class Menu{
private:
    List<Song> myList;
public:
    Menu();
    int displayMenu();
    void optionsMenu(const int&);
    void insertSong();
    void deleteSong();
    void searchSong();
    void sortSongs();
    List<Song>::Position findSong(const string&);
};

#endif //PROGRAMA01_MENU_H
