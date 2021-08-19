#ifndef PROGRAMA02_VIDEOGAME_H
#define PROGRAMA02_VIDEOGAME_H

#include <string>
using namespace std;

class Videogame{
private:
    long ID;
    string name;
    string genre;

    string setTabulations(const string&);
public:
    Videogame();
    Videogame(const Videogame&);

    long getID() const;
    string getName() const;
    string getGenre() const;

    string toString();
    string toText();

    void setID(const long&);
    void setName(const string&);
    void setGenre(const string&);

    bool operator == (const Videogame&) const;
    bool operator != (const Videogame&) const;
    bool operator < (const Videogame&) const;
    bool operator > (const Videogame&) const;
};

#endif //PROGRAMA02_VIDEOGAME_H
