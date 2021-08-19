#ifndef PROGRAMA01_SONG_H
#define PROGRAMA01_SONG_H

#include <string>

class Song{
private:
    std::string songName;
    std::string performer;
    std::string album;

    std::string setTabulations(const std::string&);
public:
    Song();
    Song(const Song&);

    std::string getSongName() const;
    std::string getPerformer() const;
    std::string getAlbum() const;

    std::string toString();

    void setSongName(const std::string&);
    void setPerformer(const std::string&);
    void setAlbum(const std::string&);

    bool operator == (const Song&) const;
    bool operator != (const Song&) const;
};

#endif //PROGRAMA01_SONG_H
