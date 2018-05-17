#ifndef PAINTING_H
#define PAINTING_H
#include "bits/stdc++.h"

class painting
{
private:
    std::string title, artist;
    int year;
public:
    painting() {}
    painting(std::string _title, std::string _artist, int _year) : title{ _title }, artist{ _artist }, year{ _year } {}
    std::string getTitle() { return title; }
    std::string getArtist() { return artist; }
    int getYear() { return year; }
    bool isThis( painting p ){
        if( title == p.getTitle() && artist == p.getArtist() && year == p.getYear() )
            return true;
        return false;
    }
};

#endif // PAINTING_H
