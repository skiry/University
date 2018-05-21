#ifndef REPOSITORY_H
#define REPOSITORY_H
//#include "dynamicarray.h"
#include "tutorial.h"
#include <vector>

class Repository
{
protected:
    /*DynamicArray<Tutorial>*/ std::vector<Tutorial> repo;
    /*DynamicArray<Tutorial>*/ std::vector<Tutorial> wList;
    int length;
    int wLen;
public:
    Repository();
    void addTut(const Tutorial& tut);
    //add a tutorial to repo

    void rmTut(std::string title);
    //remove a tutorial from repo

    void updTut(std::string title, const Tutorial& tut);
    //update tutorial in repo

    int find(std::string title);
    // find a tutorial in repo

    int findW(std::string title);
    // find a tutorial in watch list

    Repository& getRepo();
    //repo getter

    int len() { return this -> length; }
    //length getter

    Tutorial& operator[](int pos) { if(pos < this -> length) return this -> repo[pos]; return this->repo[0]; }
    std::vector<Tutorial> byPresenter(std::string pr);
    //return an iterator to tutorials presented by pr

    std::vector<Tutorial> getWlist();
    //return an iterator to tutorials in the watch list

    void increaseLike(std::string title);
    //increase the number of likes of tutorial with the name title

    bool addToPL(const Tutorial &tut);
    //add tutorial to the playlist

    void rmFromPL(std::string title);
    //add tutorial to the playlist

    void readRepo();
    //read tutorials from file

    void writeRepo();
    //write tutorials to file

    void readWlist();
    //read the watch list from file

    void writeWList();
    //write the watch list to file

    ~Repository() {};
};

#endif // REPOSITORY_H
