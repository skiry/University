#ifndef UI_H
#define UI_H
#include "controller.h"

class UI
{
private:
    Controller ui;
    std::string file, fileType;
public:
    UI(const Controller& ctrl) : ui(ctrl) {};
    //constructor

    void start();
    //the main function in which to program will run

    ~UI() {};
    //destructor

    void update();
    //update a tutorial in administrator mode

    void addA();
    //add a tutorial in administrator mode

    void deleteA();
    //delete a tutorial in administrator mode

    void printMenu();
    //print the menu

    void printWmenu();
    //print the watch list's menu

    void printRepo();
    //print the repo

    void showTuts();
    //print the tutorials

    void delTut();
    //delete a tutorial

    void printWlist();
    //print the watch list's tutorials

    void saveTuts();
    //save the watch list to file
};

#endif // UI_H
