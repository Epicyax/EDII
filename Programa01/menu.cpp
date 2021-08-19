#include "menu.h"

using namespace std;

Menu::Menu(){
    myList.retrieveList();
}

int Menu::displayMenu(){
    int opcion = 0;
    system("cls");
    cout << "- Menu -" << endl;
    cout << "1) Insertar nueva cancion" << endl;
    cout << "2) Eliminar cancion" << endl;
    cout << "3) Buscar cancion" << endl;
    cout << "4) Mostrar todas las canciones" << endl;
    cout << "5) Guardar canciones" << endl;
    cout << "6) Cargar canciones" << endl;
    cout << "7) Salir" << endl;
    do{
        cin >> opcion;
        cin.ignore();
        if(opcion < 1 || opcion > 7)
            cout << "Opcion no valida, ingrese de nuevo" << endl;
    }while(opcion < 1 || opcion > 7);

    optionsMenu(opcion);
    system("pause");
    return opcion;
}

void Menu::optionsMenu(const int& o){
    switch(o){
        case 1:
            insertSong();
            break;
        case 2:
            deleteSong();
            break;
        case 3:
            searchSong();
            break;
        case 4:
            cout << myList.toString();
            break;
        case 5:
            myList.saveList();
            cout << "Canciones guardadas con exito" << endl;
            break;
        case 6:
            myList.deleteAll(); // Esto es para evitar duplicar los datos
            myList.retrieveList();
            cout << "Canciones recuperadas con exito" << endl;
            break;
        case 7:
            cout << "Guardando informacion y saliendo..." << endl;
            myList.saveList();
            break;
        default:
            break;
    }
}

void Menu::insertSong(){
    Song mySong;
    string myStr;

    cout << "Nombre de la cancion: ";
    getline(cin,myStr);
    mySong.setSongName(myStr);
    cout << "Nombre del interprete: ";
    getline(cin,myStr);
    mySong.setPerformer(myStr);
    cout << "Nombre del album: ";
    getline(cin,myStr);
    mySong.setAlbum(myStr);
    myList.insertElement(myList.getLastPosition(), mySong);
}

void Menu::deleteSong(){
    string myStr;

    cout << "Ingrese el nombre de la cancion que desea eliminar" << endl;
    getline(cin,myStr);

    List<Song>::Position pos = findSong(myStr);

    if(pos == nullptr)
        cout << "No se encontro ninguna cancion con esos datos" << endl;
    else{
        myList.deleteElement(pos);
        cout << "Cancion eliminada" << endl;
    }
}

void Menu::searchSong(){
    string myStr;

    cout << "Ingrese el nombre de la cancion que desea buscar" << endl;
    getline(cin,myStr);

    List<Song>::Position pos = findSong(myStr);

    if(pos == nullptr)
        cout << "No se encontro ninguna cancion con esos datos" << endl;
    else
        cout << myList.retrieveElement(pos).toString() << endl;
}

typename List<Song>::Position Menu::findSong(const string &songName){
    Song mySong;
    mySong.setSongName(songName);
    return myList.linearSearch(mySong);
}
