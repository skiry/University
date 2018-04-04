#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "dynamicarray.h"
#include "tutorial.h"

class Repository
{
private:
    DynamicArray<Tutorial> repo;
    int length;
public:
    Repository();
    void addTut(const Tutorial& tut);
    void rmTut(std::string title);
    void updTut(std::string title, const Tutorial& tut);
    int find(std::string title);
    Repository& getRepo();
    int len() { return this -> length; };
    Tutorial& operator[](int pos) { if(pos < this -> length) return this -> repo[pos]; return this->repo[0]; };
    ~Repository() {};
};

#endif // REPOSITORY_H
