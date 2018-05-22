#include "tutorialvalidator.h"
#include "controller.h"

int Controller::add(const Tutorial& tut){
    if( this -> ctrl.find(tut.getTitle()) )
        return 1;
    try{
        this -> ctrl.addTut(tut);
        this -> sqlR -> addTut(tut);
       // this -> sqlR -> saveToFile();
    }
    catch(...){
        throw;
    }
    this -> length++;
    return 0;
}

int Controller::rm(std::string title){
    if( this -> ctrl.find(title) ){
        this -> length--;
        this -> ctrl.rmTut(title);
        //this -> sqlR -> rmTut(title);
        //this -> sqlR -> saveToFile();
        return 1;
    }
    return 0;
}

int Controller::rmW(std::string title){
    if( this -> ctrl.findW(title) ){
        this -> ctrl.rmFromPL(title);
        this -> playList -> rmFromPL(title);
        //this -> sqlR -> rmFromPL(title);
        return 1;
    }
    return 0;
}

int Controller::upd(std::string title, const Tutorial& tut){
    if( this -> ctrl.find(title) && this -> ctrl.find(tut.getTitle()) ==0 ){
        try{
            this -> ctrl.updTut(title, tut);
           // this -> sqlR -> updTut(title, tut);
            //this -> sqlR -> saveToFile();
        }
        catch(...){
            throw;
        }
        return 1;
    }
    return 0;
}



bool Controller::addToPL(const Tutorial& tut) {
    bool doo = ctrl.addToPL(tut);

    if( doo ) {
        this -> playList -> addToPL(tut);
       // this -> sqlR -> addToPL(tut);
    }
    return doo;
}
