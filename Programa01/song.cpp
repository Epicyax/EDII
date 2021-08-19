#include "song.h"

using namespace std;

Song::Song(){}

Song::Song(const Song& s){
    album = s.album;
    performer = s.performer;
    songName = s.songName;
}

string Song::getAlbum() const{
    return album;
}

string Song::getPerformer() const{
    return performer;
}

string Song::getSongName() const{
    return songName;
}


string Song::setTabulations(const string& aString){
    string tabs;
    int stringSize = aString.length();

    if(stringSize < 7)
        tabs+="\t\t\t\t";
    else if(stringSize <15)
        tabs+="\t\t\t";
    else
        tabs+="\t\t";
    return tabs;
}

string Song::toString(){
    string songInfo;
    songInfo = songName;
    songInfo += setTabulations(songName) + "|";
    songInfo += performer;
    songInfo += setTabulations(performer) + "|";
    songInfo += album;
    return songInfo;
}

void Song::setAlbum(const std::string& a){
    album = a;
}

void Song::setPerformer(const std::string& p){
    performer = p;
}

void Song::setSongName(const std::string& sn){
    songName = sn;
}


bool Song::operator == (const Song& s) const{
    return songName == s.songName;
}

bool Song::operator != (const Song& s) const{
    return songName != s.songName;
}