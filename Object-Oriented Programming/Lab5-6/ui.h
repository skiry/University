#ifndef UI_H
#define UI_H
#include "controller.h"

class UI
{
private:
    Controller ui;
public:
    UI(const Controller& ctrl) : ui(ctrl) {};
    //constructor
    void start();
    //the main function in which to program will run
    ~UI() {};
    //destructor
};

#endif // UI_H
