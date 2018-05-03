#ifndef HTMLPLAYLIST_H
#define HTMLPLAYLIST_H
#include "fileplaylist.h"
#include <fstream>
#include "tutorial.h"

class HTMLPlaylist : public FilePlaylist
{
public:
    HTMLPlaylist( std::string title ){
        fileName = title;
    }
    void saveToFile() override{
        std::ofstream g( fileName );
        if( g.is_open() ){
            g << "<!DOCTYPE HTML><html><head><title>Tutorials Watch List</title></head>";
            g << "<body><table border=\"1\"><tr><td>Title</td><td>Presenter</td>";
            g << "<td>Duration</td><td>Likes</td><td>Youtube link</td></tr>";
            for( auto it : wList ){
                g << it.toStr();
            }
            g << "</table></body></html>";
        }
    }

    void displayWatchList() override{
        std::string exec = "cp /home/skiry/Qt/Lab5-6/WatchList.html /home/skiry/Desktop/index.html"
                           " && firefox file:///home/skiry/Desktop/index.html";
        system( &exec[0u] );
    }
};
#endif // HTMLPLAYLIST_H
