#ifndef FILEPLAYLIST_H
#define FILEPLAYLIST_H
#include <string>
#include "repository.h"

class FilePlaylist : public Repository
{
protected:
    std::string fileName;
public:
    virtual void saveToFile() = 0;
    virtual void displayWatchList() = 0;
};

#endif // FILEPLAYLIST_H
