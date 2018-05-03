#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "repository.h"
#include "fileplaylist.h"

class Controller
{
private:
    Repository ctrl;
    FilePlaylist* playList, *sqlR;
    int length;
public:
    Controller(const Repository& r, FilePlaylist* p, FilePlaylist* _sqlR) : ctrl(r), playList{ p }, sqlR{ _sqlR }, length(0) {}
    //constructor

    int add(const Tutorial& tut);
    //check if tut is existent, if not, add

    int rm(std::string title);
    //if tut is not existent, remove

    int rmW(std::string title);
    //if tut is not existent, remove from watch list

    int upd(std::string title, const Tutorial& tut);
    //if title in in the list of tuts, update it with tut

    Controller& getCtrl() { return *this; }
    //getter for controller

    Tutorial& operator[](int pos) { return this -> ctrl[pos];}
    //to acces elements from the controller

    int len() { return this -> length; }
    //length getter

    std::vector<Tutorial> byPresenter(std::string pr) { return ctrl.byPresenter(pr); }
    //return an iterator to tutorials presented by pr

    std::vector<Tutorial> getWlist() { return ctrl.getWlist(); }
    //return an iterator to tutorials in the watch list

    void like(std::string title) { ctrl.increaseLike(title); }
    //increase the number of likes of tutorial with the name title

    bool addToPL(const Tutorial& tut);
    //add tutorial to the playlist

    void readR() {
        ctrl.readRepo();
        sqlR -> setDB( ctrl.getWlist(), ctrl.byPresenter("") );
    }
    //read tutorials from file

    void readP() {
        ctrl.readWlist();
        playList -> set( ctrl.getWlist() );
        sqlR -> setDB( ctrl.getWlist(), ctrl.byPresenter("") );
    }
    //read the watch list from file

    void saveR() { ctrl.writeRepo(); }
    //write tutorials to file

    void saveP() { ctrl.writeWList(); }
    //write the watch list to file

    void saveToFile() {
        playList->saveToFile();
        sqlR -> saveToFile();
    }
    //save the WL to either csv or html file

    void displayFile() { playList->displayWatchList(); }
    //display the file with the accordingly program

    ~Controller() {}
    //destructor for controller
};

#endif // CONTROLLER_H
