#ifndef SQLREPO_H
#define SQLREPO_H
#include "fileplaylist.h"
#include <fstream>
#include <stdlib.h>
#include <sqlite3.h>

class SQLRepo : public FilePlaylist
{
public:
    static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
       int i;
       for(i = 0; i<argc; i++) {
          printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
       }
       printf("\n");
       return 0;
    }

    SQLRepo( std::string title ) {}
    void saveToFile() override{
        //*******************************
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;

        rc = sqlite3_open("Tutorial.db", &db);

        std::string sql;
        sql = "DELETE from Repository WHERE 1=1;";
        rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
        if( rc != SQLITE_OK ) std::cout<<zErrMsg;

        sql = "DELETE from WatchList WHERE 1=1;";
        rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
        if( rc != SQLITE_OK ) std::cout<<zErrMsg;

        for(auto tut : repo){
            sql = "INSERT INTO Repository VALUES('";
            sql += tut.getTitle() + "','" + tut.getPresenter() + "'," +std::to_string(tut.getTime().getMinutes()) +
                    ","+std::to_string(tut.getTime().getSeconds()) + "," + std::to_string(tut.getLikes()) + ",'" +tut.getLink()+"');";

            rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
        }

        for(auto tut : wList){
            sql = "INSERT INTO WatchList VALUES('";
            sql += tut.getTitle() + "','" + tut.getPresenter() + "'," +std::to_string(tut.getTime().getMinutes()) +
                    ","+std::to_string(tut.getTime().getSeconds()) + "," + std::to_string(tut.getLikes()) + ",'" +tut.getLink()+"');";

            rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
        }

        sqlite3_close(db);
        //**************

    }

    void displayWatchList() override{}
};

#endif // SQLREPO_H
