#include "repository.h"
#include <utility>
#include <algorithm>
#include <iostream>
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
        if(this -> repo[i].getTitle().compare(title) == 0){
            this -> repo - this->repo[i];
            this -> length--;
        }
            //std::swap(this -> repo[i], this -> repo[--(this -> length)]);
}

int Repository::find(std::string title){
    int found = 0;
    for(int i = 0; i < this -> length; ++i)
        if( this -> repo[i].getTitle() == title )
            return 1;

    return 0;
}

int Repository::findW(std::string title){
    int found = 0;
    for(int i = 0; i < this -> wLen; ++i)
        if( this -> wList[i].getTitle() == title )
            return 1;

    return 0;
}

void Repository::updTut(std::string title, const Tutorial& tut){
    for(int i = 0; i < this -> length; ++i)
        if(this -> repo[i].getTitle().compare(title) == 0)
            this -> repo[i] = tut;
}

std::vector<Tutorial> Repository::byPresenter(std::string pr){
    std::vector<Tutorial> v;
    for( int i = 0; i < length; ++i )
        if( repo[i].getPresenter() == pr || pr == "")
            v.push_back(repo[i]);

    return v;
}


std::vector<Tutorial> Repository::getWlist(){
    std::vector<Tutorial> v;
    for( int i = 0; i < wLen; ++i )
            v.push_back(wList[i]);

    return v;
}

void Repository::increaseLike(std::string title){
    for(int i = 0; i < this -> length; ++i)
        if( this -> repo[i].getTitle() == title )
            ++(this -> repo[i]);
}

bool Repository::addToPL(const Tutorial& tut){
    if( findW(tut.getTitle()) ) return false;

    this -> wList.add(tut);
    this -> wLen++;

    return true;
}

void Repository::rmFromPL(std::string title){
    for(int i = 0; i < this -> wLen; ++i)
        if(this -> wList[i].getTitle().compare(title) == 0){
            this -> wList - this->wList[i];
            this -> wLen--;
        }
}

Repository& Repository::getRepo(){
    return *this;
}






