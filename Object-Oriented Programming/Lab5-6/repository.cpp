#include "repository.h"
#include <utility>
#include <algorithm>

Repository::Repository(){
    //this -> repo = DynamicArray<Tutorial>(10);
    this -> length = 0;
}

void Repository::addTut(const Tutorial& tut){
    this -> repo.add(tut);
    this -> length++;
}

void Repository::rmTut(std::string title){
    for(int i = 0; i < this -> length; ++i)
        if(this -> repo[i].getTitle().compare(title) == 0)
            this -> repo - this->repo[i];
            //std::swap(this -> repo[i], this -> repo[--(this -> length)]);
}

int Repository::find(std::string title){
    int found = 0;
    for(int i = 0; i < this -> length; ++i)
        if((this -> repo[i]).getTitle().compare(title) == 0)
            return 1;
    return 0;
}
void Repository::updTut(std::string title, const Tutorial& tut){
    for(int i = 0; i < this -> length; ++i)
        if(this -> repo[i].getTitle().compare(title) == 0)
            this -> repo[i] = tut;
}

Repository& Repository::getRepo(){
    return *this;
}
