#ifndef PROGRAMA01_LIST_H
#define PROGRAMA01_LIST_H

#include <cstdlib>
#include <fstream>
#include <exception>
#include "song.h"

template <class T>
class List{
private:
    class Node{
    private:
        T data;
        Node* next;
    public:
        Node();
        Node(const T&);

        T getData() const;
        Node* getNext() const;

        void setData(const T&);
        void setNext(Node*);
    };

    Node* anchor;

    bool isValidPosition(Node*) const;
    void copyAll(const List&);

public:
    typedef Node* Position;

    List();
    List(const List&);
    ~List();

    class Exception : public std::exception {
    private:
        std::string msg;
    public:
        explicit Exception(const char* message) : msg(message) { }
        explicit Exception(const std::string& message) : msg(message) { }
        virtual ~Exception() throw () { }
        virtual const char* what() const throw () {
            return msg.c_str();
        }
    };

    bool isEmpty() const;

    void insertElement(Node*, const T&);

    void deleteElement(Node*);

    Node* getFirstPosition() const;
    Node* getLastPosition() const;
    Node* getPrevPosition(Node*) const;
    Node* getNextPosition(Node*) const;

    std::string toString() const;

    T retrieveElement(Node*) const;

    void deleteAll();

    Node* linearSearch(const T&) const;

    void retrieveList();
    void saveList();

    List<T>& operator = (const List<T>&);
};

// Implementacion
using namespace std;

// Nodo
template <class T>
List<T>::Node::Node() : next(nullptr) {}

template <class T>
List<T>::Node::Node(const T& e) : data(e), next(nullptr) {}

template <class T>
T List<T>::Node::getData() const{
    return data;
}

template <class T>
typename List<T>::Node* List<T>::Node::getNext() const{
    return next;
}

template <class T>
void List<T>::Node::setData(const T& e){
    data = e;
}

template <class T>
void List<T>::Node::setNext(Node* p){
    next = p;
}


// Lista
template <class T>
void List<T>::copyAll(const List<T>& l){
    Node* aux(l.anchor);
    Node* last(nullptr);
    Node* newNode;

    while(aux != nullptr){
        newNode = new Node(aux->getData());
        if(newNode == nullptr)
            throw Exception("Memoria no disponible (insertElement");

        if(last == nullptr)
            anchor = newNode;
        else
            last->setNext(newNode);

        last = newNode;
        aux = aux->getNext();
    }
}

template <class T>
bool List<T>::isValidPosition(Node* pos) const{
    Node* aux(anchor);

    while(aux != nullptr){
        if(aux == pos)
            return true;
        aux = aux->getNext();
    }
    return false;
}

template <class T>
List<T>::List() : anchor(nullptr){}

template <class T>
List<T>::List(const List<T>& l) : anchor(nullptr){
    copyAll(l);
}

template <class T>
List<T>::~List(){
    deleteAll();
}

template <class T>
bool List<T>::isEmpty() const{
    return anchor == nullptr;
}

template <class T>
void List<T>::insertElement(Node* pos, const T& s){
    if(pos != nullptr && !isValidPosition(pos))
        throw Exception("Posicion invalida (insertElement)");

    Node* aux(new Node(s));

    if(aux == nullptr)
        throw Exception("Memoria no disponible (insertElement");
    if(pos == nullptr){
        aux->setNext(anchor);
        anchor = aux;
    }
    else{
        aux->setNext(pos->getNext());
        pos->setNext(aux);
    }
}

template <class T>
void List<T>::deleteElement(Node* pos){
    if(!isValidPosition(pos))
        throw Exception("Posicion invalida (deleteElement)");
    if(pos == anchor)
        anchor = anchor->getNext();
    else
        getPrevPosition(pos)->setNext(pos->getNext());
    delete pos;
}

template <class T>
typename List<T>::Node* List<T>::getFirstPosition() const{
    return anchor;
}

template <class T>
typename List<T>::Node* List<T>::getLastPosition() const{
    if(isEmpty())
        return nullptr;

    Node* aux(anchor);
    while(aux->getNext() != nullptr){
        aux = aux->getNext();
    }
    return aux;
}

template <class T>
typename List<T>::Node* List<T>::getPrevPosition(Node* pos) const{
    if(pos == anchor)
        return nullptr;

    Node* aux(anchor);
    while(aux != nullptr && aux->getNext() != pos){
        aux = aux->getNext();
    }
    return aux;
}

template <class T>
typename List<T>::Node* List<T>::getNextPosition(Node* pos) const{
    if(!isValidPosition(pos))
        return nullptr;
    return pos->getNext();
}

template <class T>
T List<T>::retrieveElement(Node* pos) const{
    if(!isValidPosition(pos))
        throw Exception("Posicion invalida (retrieveElement)");
    return pos->getData();
}

template <class T>
void List<T>::deleteAll(){
    Node* aux;

    while(anchor != nullptr){
        aux = anchor;
        anchor = anchor->getNext();
        delete aux;
    }
}

template <class T>
string List<T>::toString() const{
    Node* aux(anchor);
    string result;

    result = "Nombre de cancion\t\t| Interprete\t\t\t| Album\n";
    while(aux != nullptr){
        result += aux->getData().toString() + "\n";
        aux = aux->getNext();
    }
    return result;
}

template <class T>
typename List<T>::Node* List<T>::linearSearch(const T& s) const{
    Node* aux(anchor);

    while(aux != nullptr && aux->getData() != s){
        aux = aux->getNext();
    }
    return aux;
}

template <class T>
List<T>& List<T>::operator=(const List<T>& l){
    deleteAll();
    copyAll(l);
    return *this;
}

template <class T>
void List<T>::retrieveList(){
    ifstream file("file01.txt");
    if(file.is_open()){
        string myStr, temp;
        T song;
        getline(file, myStr);

        int found = 0;
        while (myStr.length() > 0) {
            temp.assign(myStr, 0, found = myStr.find('|'));
            song.setSongName(temp);
            myStr = myStr.substr(found+1);

            temp.assign(myStr, 0, found = myStr.find('|'));
            song.setPerformer(temp);
            myStr = myStr.substr(found+1);

            temp.assign(myStr, 0, found = myStr.find('*'));
            song.setAlbum(temp);
            myStr = myStr.substr(found+1);

            insertElement(getLastPosition(), song);
        }
    }
    file.close();
}

template <class T>
void List<T>::saveList(){
    Node* aux(anchor);

    ofstream file("file01.txt");
    if(file.is_open()) {
        while (aux != nullptr) {
            file << aux->getData().getSongName();
            file << "|";
            file << aux->getData().getPerformer();
            file << "|";
            file << aux->getData().getAlbum();
            file << "*";
            aux = aux->getNext();
        }
    }
    file.close();
}

#endif //PROGRAMA01_LIST_H
