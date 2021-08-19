#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include <exception>
#include <iostream>
#include <fstream>
#include "videogame.h"

template <class T>
class BTree{
    private:
        class Node{
            private:
                T* dataPtr;
                Node* left;
                Node* right;
            public:
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

                Node();
                Node(const T&);
                ~Node();

                T* getDataPtr() const;
                T getData() const;
                Node*& getLeft();
                Node*& getRight();

                void setDataPtr(T*);
                void setData(const T&);
                void setLeft(Node*&);
                void setRight(Node*&);
        };
    public:
        typedef Node* Position;

    private:
        Position root;

        void insertData(Position&, const T&);

        Position& findData(Position&, const T&);
        Position& getLowest(Position&);
        Position& getHighest(Position&);

        std::string parsePreOrder(Position&);
        std::string parseInOrder(Position&);
        std::string parsePostOrder(Position&);

        void save(Position&, std::ofstream&);

    public:
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

        BTree();
        ~BTree();

        bool isEmpty() const;

        void insertData(const T&);

        void deleteData(Position&);

        T retrieve(Position&) const;

        int getHeight(Position&);

        Position& findData(const T&);

        Position& getLowest();
        Position& getHighest();
        Position& getRoot();

        bool isLeaf(Position&) const;

        int getHeight();

        std::string parsePreOrder();
        std::string parseInOrder();
        std::string parsePostOrder();

        void save();
        void retrieveData();

        void deleteAll(Position&);
};


template <class T>
BTree<T>::Node::Node() : dataPtr(nullptr), left(nullptr), right(nullptr){}

template <class T>
BTree<T>::Node::Node(const T& e) : dataPtr(new T(e)), left(nullptr), right(nullptr){
    if(dataPtr == nullptr){
        throw Exception("Memoria insuficiente, creando nodo");
    }
}

template <class T>
BTree<T>::Node::~Node(){
    delete dataPtr;
}

template <class T>
T* BTree<T>::Node::getDataPtr() const{
    return dataPtr;
}

template <class T>
T BTree<T>::Node::getData() const{
    if(dataPtr == nullptr){
        throw Exception("Dato inexistente, getData");
    }
    return *dataPtr;
}

template <class T>
typename BTree<T>::Node*& BTree<T>::Node::getLeft(){
    return left;
}

template <class T>
typename BTree<T>::Node*& BTree<T>::Node::getRight(){
    return right;
}

template <class T>
void BTree<T>::Node::setDataPtr(T* p){
    dataPtr = p;
}

template <class T>
void BTree<T>::Node::setData(const T& e){
    if(dataPtr == nullptr){
        if((dataPtr = new T(e)) == nullptr){
            throw Exception("Memoria no disponible, setData");
        }
    }
    else{
        *dataPtr = e;
    }
}

template <class T>
void BTree<T>::Node::setLeft(Node*& p){
    left = p;
}

template <class T>
void BTree<T>::Node::setRight(Node*& p){
    right = p;
}


// BTree


template <class T>
BTree<T>::BTree() : root(nullptr){}

template <class T>
BTree<T>::~BTree(){
    save();
    deleteAll(root);
}

template <class T>
bool BTree<T>::isEmpty() const{
    return root == nullptr;
}

template <class T>
void BTree<T>::insertData(const T& e){
    insertData(root, e);
}

template <class T>
void BTree<T>::insertData(Position& r, const T& e){
    if(r == nullptr){
        try{
            if((r = new Node(e)) == nullptr){
                throw Exception("Memoria no disponible, insertData");
            }
        }
        catch(typename Node::Exception ex){
            throw Exception(ex.what());
        }
    }
    else{
        if(e < r->getData()){
            insertData(r->getLeft(), e);
        }
        else{
            insertData(r->getRight(), e);
        }
    }
}

template <class T>
void BTree<T>::deleteData(Position& p){
    Position pos_reemplazo;
    if(root == nullptr or p == nullptr)
        throw Exception("Dato inexistente, deleteData");
    if(isLeaf(p)){
        delete p;
        p = nullptr;
    }
    else{
        if(p->getLeft() != nullptr){
            pos_reemplazo = getHighest(p->getLeft());
            p->setData(pos_reemplazo->getData());
            deleteData(getHighest(p->getLeft()));
        }
        else{
            pos_reemplazo = getLowest(p->getRight());
            p->setData(pos_reemplazo->getData());
            deleteData(getLowest(p->getRight()));
        }
    }
}

template <class T>
T BTree<T>::retrieve(Position& r) const{
    return r->getData();
}

template <class T>
typename BTree<T>::Position& BTree<T>::findData(const T& e){
    return findData(root, e);
}

template <class T>
typename BTree<T>::Position& BTree<T>::findData(Position& r, const T& e){
    if(r == nullptr or r->getData() == e){
        return r;
    }
    if(e < r->getData()){
        return findData(r->getLeft(), e);
    }
    return findData(r->getRight(), e);
}

template <class T>
typename BTree<T>::Position& BTree<T>::getLowest(){
    return getLowest(root);
}

template <class T>
typename BTree<T>::Position& BTree<T>::getLowest(Position& r){
    if(r == nullptr or r->getLeft() == nullptr){
        return r;
    }
    return getLowest(r->getLeft());
}

template <class T>
typename BTree<T>::Position& BTree<T>::getHighest(){
    return getHighest(root);
}

template <class T>
typename BTree<T>::Position& BTree<T>::getHighest(Position& r){
    if(r == nullptr or r->getRight() == nullptr){
        return r;
    }
    return getHighest(r->getRight());
}

template <class T>
typename BTree<T>::Position& BTree<T>::getRoot(){
    return root;
}

template <class T>
bool BTree<T>::isLeaf(Position& r) const{
    return r != nullptr and r->getLeft() == r->getRight();
}

template <class T>
int BTree<T>::getHeight(){
    return getHeight(root);
}

template <class T>
int BTree<T>::getHeight(Position& r){
    if(r == nullptr){
        return 0;
    }
    int lH(getHeight(r->getLeft()));
    int rH(getHeight(r->getRight()));

    return (lH > rH ? lH : rH) + 1;
}

template <class T>
std::string BTree<T>::parsePreOrder(){
    return parsePreOrder(root);
}

template <class T>
std::string BTree<T>::parsePreOrder(Position& r){
    if(r == nullptr){
        return "";
    }
    std::string po = r->getData().toString();
    po += parsePreOrder(r->getLeft());
    po += parsePreOrder(r->getRight());
    return po;
}

template <class T>
std::string BTree<T>::parseInOrder(){
    return parseInOrder(root);
}

template <class T>
std::string BTree<T>::parseInOrder(Position& r){
    if(r == nullptr){
        return "";
    }
    std::string po = "";
    po += parseInOrder(r->getLeft());
    po += r->getData().toString();
    po += parseInOrder(r->getRight());
    return po;
}

template <class T>
std::string BTree<T>::parsePostOrder(){
    return parsePostOrder(root);
}

template <class T>
std::string BTree<T>::parsePostOrder(Position& r){
    if(r == nullptr){
        return "";
    }
    std::string po = "";
    po += parsePostOrder(r->getLeft());
    po += parsePostOrder(r->getRight());
    po += r->getData().toString();
    return po;
}

template <class T>
void BTree<T>::deleteAll(Position& node){
    if(node) {
        deleteAll(node->getLeft());
        deleteAll(node->getRight());
        delete node;
        node = nullptr;
    }
}

template <class T>
void BTree<T>::save(){
    std::ofstream file("file01.txt", std::ios::out);
    if(file.is_open()){
        save(root, file);
        file.close();
    }
}

template <class T>
void BTree<T>::save(Position& r, std::ofstream& file){
    if(r == nullptr){
        return;
    }
    file << r->getData().toText();
    save(r->getLeft(), file);
    save(r->getRight(), file);
}

template <class T>
void BTree<T>::retrieveData(){
    std::ifstream file("file01.txt");
    if(file.is_open()){
        std::string myStr, temp;
        T vg;
        int found = 0;
        getline(file, myStr);
        while (myStr.length() > 0) {
            temp.assign(myStr, 0, found = myStr.find('|'));
            vg.setID(stol(temp));
            myStr = myStr.substr(found+1);
            
            temp.assign(myStr, 0, found = myStr.find('|'));
            vg.setName(temp);
            myStr = myStr.substr(found+1);

            temp.assign(myStr, 0, found = myStr.find('*'));
            vg.setGenre(temp);
            myStr = myStr.substr(found+1);

            insertData(vg);
        }
    }
    file.close();
}

#endif // BTREE_H_INCLUDED