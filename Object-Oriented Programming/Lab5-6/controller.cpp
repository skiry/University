#include "controller.h"

int Controller::add(const Tutorial& tut){
    if( this -> ctrl.find(tut.getTitle()) )
        return 1;
    this -> ctrl.addTut(tut);
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
int Controller::upd(std::string title, const Tutorial& tut){
    if( this -> ctrl.find(title) && this -> ctrl.find(tut.getTitle()) ==0 ){
        this -> ctrl.updTut(title, tut);
        return 1;
    }
    return 0;
}
