#include "controller.h"
#include "tutorialvalidator.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int Controller::add(const Tutorial& tut){
    if( this -> ctrl.find(tut.getTitle()) )
        return 1;
    try{
        this -> ctrl.addTut(tut);
        //*************
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;

        rc = sqlite3_open("Tutorial.db", &db);


        std::string sql;
        sql = "INSERT INTO Repository VALUES('";
        sql += tut.getTitle() + "','" + tut.getPresenter() + "'," +std::to_string(tut.getTime().getMinutes()) +
                ","+std::to_string(tut.getTime().getSeconds()) + "," + std::to_string(tut.getLikes()) + ",'" +tut.getLink()+"');";
        std::cout<<'\n'<<sql<<'\n';

        rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

        sqlite3_close(db);
        //**************

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
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;

        rc = sqlite3_open("Tutorial.db", &db);


        std::string sql;
        sql = "DELETE FROM Repository Title='";
        sql += title +"';";
        std::cout<<'\n'<<sql<<'\n';

        rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

        sqlite3_close(db);
        return 1;
    }
    return 0;
}

int Controller::rmW(std::string title){
    if( this -> ctrl.findW(title) ){
        this -> ctrl.rmFromPL(title);
        this -> playList -> rmFromPL(title);
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;

        rc = sqlite3_open("Tutorial.db", &db);


        std::string sql;
        sql = "DELETE FROM WatchList WHERE Title='";
        sql += title +"';";
        std::cout<<'\n'<<sql<<'\n';

        rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

        sqlite3_close(db);
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



bool Controller::addToPL(const Tutorial& tut) {
    bool doo = ctrl.addToPL(tut);

    if( doo ) {
        this -> playList -> addToPL(tut);
        //*************
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;

        rc = sqlite3_open("Tutorial.db", &db);


        std::string sql;
        sql = "INSERT INTO WatchList VALUES('";
        sql += tut.getTitle() + "','" + tut.getPresenter() + "'," +std::to_string(tut.getTime().getMinutes()) +
                ","+std::to_string(tut.getTime().getSeconds()) + "," + std::to_string(tut.getLikes()) + ",'" +tut.getLink()+"');";
        std::cout<<'\n'<<sql<<'\n';

        rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

        sqlite3_close(db);
        //**************
    }
    return doo;
}
