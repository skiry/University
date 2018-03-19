#include "Song.h"

Song::Song(const std::string& title, const std::string& artist,
 const int& duration) {
 	this -> artist = artist;
 	this -> title = title;
 	this -> duration = duration;
}

Song::~Song() {

}