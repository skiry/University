#ifndef HTMLPLAYLIST_H
#define HTMLPLAYLIST_H
#include "fileplaylist.h"

class HTMLPlaylist : public FilePlaylist
{
public:
    HTMLPlaylist( std::string title ){
        fileName = title;
    }
    void saveToFile() override{
        std::ofstream g( fileName );
        if( g.is_open() ){
            for( auto it : getWlist() )
                g << it;
        }
    }

    void displayWatchList() override{
        std::string exec = "nano ";
        exec += fileName;
        system( &exec[0u] );
    }
};
#endif // HTMLPLAYLIST_H
