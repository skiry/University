#pragma once
#include <vector>
#include "Song.h"
#include "PlayList.h"
#include "FilePlaylist.h"
#include <fstream>

class JSONPlayList : public FilePlaylist
{
std::ofstream g;
public:
JSONPlayList(std::string a) { 
fileName = a;
}
	virtual void writeToFile(){
	std::ofstream g(fileName);
	for( auto& i : songs )
	        g << i.toJson();
	}
	virtual void displayPlaylist(){
	    std::string exec = "nano ";
	    exec += fileName;
	    system(&exec[0u]);
	}
	
	
};

