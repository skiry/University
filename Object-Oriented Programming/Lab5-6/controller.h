#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "repository.h"

class Controller
{
private:
    Repository ctrl;
    int length;
public:
    Controller(const Repository& r) : ctrl(r), length(0) {};
    //constructor
    int add(const Tutorial& tut);
    //check if tut is existent, if not, add
    int rm(std::string title);
    //if tut is not existent, remove
    int upd(std::string title, const Tutorial& tut);
    //if title in in the list of tuts, update it with tut
    Controller& getCtrl() { return *this; };
    //getter for controller
    Tutorial& operator[](int pos) { return this -> ctrl[pos];};
    //to acces elements from the controller
    int len() { return this -> length; };
    //length getter
    ~Controller() {};
    //destructor for controller
};

#endif // CONTROLLER_H
