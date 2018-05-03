#include "repository.h"
#include "tutorialvalidator.h"
#include <utility>
#include <algorithm>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <sqlite3.h>

Repository::Repository(){
    //this -> repo = DynamicArray<Tutorial>(10);
    this -> length = 0;
}

void Repository::addTut(const Tutorial& tut){
    TutorialValidator::validate(tut);
    this -> repo.push_back(tut);
    this -> length++;
}

void Repository::rmTut(std::string title){
    for(int i = 0; i < this -> repo.size() ; ++i)
        if(this -> repo[i].getTitle().compare(title) == 0){
            //this -> repo - this->repo[i];
            this -> repo.erase(repo.begin() + i);
            //this -> length--;
        }
            //std::swap(this -> repo[i], this -> repo[--(this -> length)]);
}

int Repository::find(std::string title){
    for(int i = 0; i < this -> repo.size() ; ++i)
        if( this -> repo[i].getTitle() == title )
            return 1;

    return 0;
}

int Repository::findW(std::string title){
    for(int i = 0; i < this -> wList.size() ; ++i)
        if( this -> wList[i].getTitle() == title )
            return 1;

    return 0;
}

void Repository::updTut(std::string title, const Tutorial& tut){
    for(int i = 0; i < this -> repo.size() ; ++i)
        if(this -> repo[i].getTitle().compare(title) == 0){
            TutorialValidator::validate(tut);
            this -> repo[i] = tut;
        }
}

std::vector<Tutorial> Repository::byPresenter(std::string pr){
    std::vector<Tutorial> v;
    for( int i = 0; i < repo.size() ; ++i )
        if( repo[i].getPresenter() == pr || pr == "")
            v.push_back(repo[i]);

    return v;
}


std::vector<Tutorial> Repository::getWlist(){
    std::vector<Tutorial> v;
    for( int i = 0; i < wList.size() ; ++i )
            v.push_back(wList[i]);

    return v;
}

void Repository::increaseLike(std::string title){
    for(int i = 0; i < this -> repo.size() ; ++i)
        if( this -> repo[i].getTitle() == title )
            ++(this -> repo[i]);
}

bool Repository::addToPL(const Tutorial& tut){
    if( findW(tut.getTitle()) ) return false;

    this -> wList.push_back(tut);
    //this -> wLen++;

    return true;
}

void Repository::rmFromPL(std::string title){
    for(int i = 0; i < this -> wList.size() ; ++i)
        if(this -> wList[i].getTitle().compare(title) == 0){
            this -> wList.erase(wList.begin() + i);
            //this -> wLen--;
        }
}

void Repository::readRepo(){
    std::ifstream f( "Tutorials.CSV" );
    Tutorial t{};
    if( f.is_open() ){
        while( f>>t )
            this -> addTut(t);
    }
}

void Repository::readWlist(){
    std::ifstream f( "WatchList.CSV" );
    Tutorial t{};
    if( f.is_open() ){
        while( f>>t )
            this -> addToPL(t);
    }
}

void Repository::writeRepo(){
    std::ofstream g( "Tutorials.CSV" );
    if( g.is_open() ){
        for( auto it : repo )
            g << it;
    }
}

void Repository::writeWList(){
    std::ofstream g( "WatchList.CSV" );
    if( g.is_open() ){
        for( auto it : wList )
            g << it;
    }
}

Repository& Repository::getRepo(){
    return *this;
}





