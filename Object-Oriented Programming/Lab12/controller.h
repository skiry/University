#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "fileplaylist.h"
#include "repository.h"
#include "undooperation.h"

class Controller
{
private:
    Repository ctrl;
    FilePlaylist* playList, *sqlR;
    int length;
    std::vector< std::shared_ptr< undoOperation > > undo;
    int undoCnt = 0;
public:
    Controller(const Repository& r, FilePlaylist* p/*, FilePlaylist* _sqlR*/) : ctrl(r), playList{ p }, /*sqlR{ _sqlR },*/ length(0) {}
    //constructor

    Controller(const Repository& r) : ctrl(r), length(0) {}
    //constructor 2

    int add(const Tutorial& tut, int c = 0);
    //check if tut is existent, if not, add

    int rm(std::string title, int c = 0);
    //if tut is not existent, remove

    int rmW(std::string title, int c = 0);
    //if tut is not existent, remove from watch list

    int upd(std::string title, const Tutorial& tut, int c = 0);
    //if title in in the list of tuts, update it with tut

    Controller& getCtrl()
    {
        return *this;
    }
    //getter for controller

    Tutorial& operator[](int pos)
    {
        return this -> ctrl[pos];
    }
    //to acces elements from the controller

    int len()
    {
        return this -> length;
    }
    //length getter

    std::vector<Tutorial> byPresenter(std::string pr)
    {
        return ctrl.byPresenter(pr);
    }
    //return an iterator to tutorials presented by pr

    std::vector<Tutorial> getWlist()
    {
        return ctrl.getWlist();
    }
    //return an iterator to tutorials in the watch list

    Repository& getRepo()
    {
        return ctrl.getRepo();
    }
    //repo getter

    std::vector<Tutorial> byPresenterWL(std::string pr)
    {
        return ctrl.byPresenterWL(pr);
    }
    //return an iterator to tutorials presented by pr in the watch list

    void like(std::string title)
    {
        ctrl.increaseLike(title);
    }
    //increase the number of likes of tutorial with the name title

    bool addToPL(const Tutorial& tut, int c = 0);
    //add tutorial to the playlist

    void read()
    {
        ctrl.readRepo();
        ctrl.readWlist();
        playList -> set( ctrl.getWlist() );
        //sqlR -> setDB( ctrl.getWlist(), ctrl.byPresenter("") );
    }
    //read from file

    void save()
    {
        ctrl.writeRepo();
        ctrl.writeWList();
        saveToFile();
    }
    //write to file

    void saveToFile()
    {
        playList->saveToFile();
        //  sqlR -> saveToFile();
    }
    //save the WL to either csv or html file

    void displayFile()
    {
        playList->displayWatchList();
    }
    //display the file with the accordingly program

    std::string allTuts()
    {
        std::vector<Tutorial> v = byPresenter("");
        std::string ret;

        for ( const auto& tut : v )
            ret += tut.getTitle() + "," + tut.getPresenter() + "," + std::to_string( tut.getTime().getMinutes() ) + "," +
                   std::to_string( tut.getTime().getSeconds() ) + "," + std::to_string( tut.getLikes() ) + "," + tut.getLink() + "\n";

        return ret;
    }
    //return a string with all the tutorials


    std::string wat()
    {
        return playList->wat();
    }

    bool doUndo();
    //undo operation

    bool doRedo();
    //redo operation

    ~Controller() {}
    //destructor for controller
};

#endif // CONTROLLER_H
