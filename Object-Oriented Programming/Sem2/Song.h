#pragma once
#include <string>

class Song {
public:
	Song(const std::string&, const std::string&, const int&);
	// & - reference, gives the same address
	// const - does not allow the parameter to change its value inside the function
	std::string getTitle() const { return this -> title; }
	~Song();

private:
	std::string title;
	std::string artist;
	int duration;
};