#include "controller.h"
#include "tutorialvalidator.h"

int Controller::add(const Tutorial& tut){
    if( this -> ctrl.find(tut.getTitle()) )
        return 1;
    try{
        this -> ctrl.addTut(tut);
    }
    catch(TutorialException& ){
        throw;
    }
    this -> length++;
    return 0;
}

int Controller::rm(std::string title){
    if( this -> ctrl.find(title) ){
        this -> length--;
        this -> ctrl.rmTut(title);
        return 1;
    }
    return 0;
}

int Controller::rmW(std::string title){
    if( this -> ctrl.findW(title) ){
        this -> ctrl.rmFromPL(title);
        return 1;
    }
    return 0;
}

int Controller::upd(std::string title, const Tutorial& tut){
    if( this -> ctrl.find(title) && this -> ctrl.find(tut.getTitle()) ==0 ){
        try{
            this -> ctrl.updTut(title, tut);
        }
        catch(...){
            throw;
        }
        return 1;
    }
    return 0;
}
