#include "menu.h"

Menu::Menu(){
    tree.retrieveData();
}

void Menu::displayMenu(){
    int opcion = 0;

    do{
        system("cls");
        cout << "* Arbol Binario de Busqueda *" << endl;
        cout << "1) Insertar un nuevo videojuego" << endl;
        cout << "2) Eliminar videojuego" << endl;
        cout << "3) Buscar videojuego" << endl;
        cout << "4) Mostrar todos los videojuegos" << endl;
        cout << "5) Guardar videojuegos" << endl;
        cout << "6) Cargar videojuegos" << endl;
        cout << "7) Salir" << endl;

        cin >> opcion;
        cin.ignore();
        menuOptions(opcion);
        system("pause");
    }while(opcion != 7);
}

void Menu::menuOptions(const int& op){
    switch(op){
        case 1:
            insertVideogame();
            break;
        case 2:
            deleteVideogame();
            break;
        case 3:
            searchVideogame();
            break;
        case 4:
            short int opcion;
            cout << "Con cual recorrido desea mostrar los datos?" << endl;
            cout << "1) PreOrder" << endl << "2) InOrder" << endl << "3) PostOrder" << endl;
            cin >> opcion;
            if(opcion == 1)
                cout << tree.parsePreOrder();
            else if(opcion == 2)
                cout << tree.parseInOrder();
            else if(opcion == 3)
                cout << tree.parsePostOrder();
            else
                cout << "Opcion no valida" << endl;
            break;
        case 5:
            tree.save();
            cout << "Informacion guardada" << endl;
            break;
        case 6:
            tree.deleteAll(tree.getRoot());
            tree.retrieveData();
            cout << "Informacion recuperada" << endl;
            break;
        case 7:
            cout << "Saliendo..." << endl;
            tree.save();
            break;
        default:
            cout << "Opcion no valida, ingrese de nuevo" << endl;
            break;
    }
}

void Menu::insertVideogame(){
    Videogame vg;
    string str;

    cout << "ID del videojuego: ";
    getline(cin, str);
    vg.setID(stol(str));
    cout << "Nombre del videojuego: ";
    getline(cin, str);
    vg.setName(str);
    cout << "Genero del videojuego: ";
    getline(cin, str);
    vg.setGenre(str);

    tree.insertData(vg);
}

void Menu::deleteVideogame(){
    long id;
    
    cout << "Ingrese el ID del videojuego a eliminar" << endl;
    cin >> id;

    BTree<Videogame>::Position pos = findVideogame(id);

    if(pos == nullptr)
        cout << "No se encontro ningun videojuego con ese ID" << endl;
    else{
        tree.deleteData(pos);
        cout << "Videojuego eliminado" << endl;
    }
}

void Menu::searchVideogame(){
    long id;
    
    cout << "Ingrese el ID del videojuego a buscar" << endl;
    cin >> id;

    BTree<Videogame>::Position pos = findVideogame(id);

    if(pos == nullptr)
        cout << "No se encontro ningun videojuego con ese ID" << endl;
    else
        cout << tree.retrieve(pos).toString() << endl;
}

BTree<Videogame>::Position Menu::findVideogame(const long& id){
    Videogame vg;
    vg.setID(id);
    return tree.findData(vg);
}