#ifndef FILEPLAYLIST_H
#define FILEPLAYLIST_H
#include <string>
#include "repository.h"
#include <vector>

class FilePlaylist : public Repository
{
protected:
    std::string fileName;
public:
    virtual void saveToFile() = 0;
    virtual void displayWatchList() = 0;
    virtual std::string wat() = 0;
    void set(std::vector<Tutorial> V)
    {
        this -> wList = V;
    }
    void setDB(std::vector<Tutorial> V, std::vector<Tutorial> P)
    {
        this -> wList = V;
        this -> repo = P;
    }
};

#endif // FILEPLAYLIST_H
