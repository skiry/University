#pragma once
#include <vector>
#include "Song.h"
#include "PlayList.h"
#include "FilePlaylist.h"
#include <fstream>

class CSVPlayList : public FilePlaylist
{
std::ofstream g;
public:
    CSVPlayList(std::string a) {
    fileName = a;
     }
	virtual void writeToFile(){
	std::ofstream g(fileName);
	
	    for( auto& i : songs )
	        g << i;
	}
	virtual void displayPlaylist(){
	    std::string exec = "nano ";
	    exec += fileName;
	    system(&exec[0u]);
	}
};

