#include "videogame.h"

Videogame::Videogame(){}

Videogame::Videogame(const Videogame& v){
    ID = v.ID;
    name = v.name;
    genre = v.genre;
}

long Videogame::getID() const{
    return ID;
}

string Videogame::getName() const{
    return name;
}

string Videogame::getGenre() const{
    return genre;
}

string Videogame::setTabulations(const string& aString){
    string tabs;
    int stringSize = aString.length();

    if(stringSize < 7)
        tabs+="\t\t\t";
    else if(stringSize < 15)
        tabs+="\t\t";
    else 
        tabs+="\t";
    return tabs;
}

string Videogame::toString(){
    string videogameInfo;
    videogameInfo = to_string(ID);
    videogameInfo += "\t|";
    videogameInfo += name;
    videogameInfo += setTabulations(name) + "|";
    videogameInfo += genre;
    videogameInfo += "\n";
    return videogameInfo;
}

string Videogame::toText(){
    string text;
    text = to_string(ID);
    text += "|" + name + "|" + genre + "*";
    return text;
}

void Videogame::setID(const long& id){
    ID = id;
}

void Videogame::setName(const string& n){
    name = n;
}

void Videogame::setGenre(const string& g){
    genre = g;
}


bool Videogame::operator == (const Videogame& v) const{
    return ID == v.ID;
}

bool Videogame::operator != (const Videogame& v) const{
    return ID != v.ID;
}

bool Videogame::operator < (const Videogame& v) const{
    return ID < v.ID;
}

bool Videogame::operator > (const Videogame& v) const{
    return ID > v.ID;
}