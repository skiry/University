#pragma once
#include <vector>
#include "Song.h"
#include "PlayList.h"

class FilePlaylist : public PlayList
{
protected:
	std::string fileName;
public:
	virtual void writeToFile() = 0;
	virtual void displayPlaylist() = 0;
};

