#ifndef HTMLPLAYLIST_H
#define HTMLPLAYLIST_H
#include "fileplaylist.h"
#include <fstream>

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
                std::cout<<it.getTitle()<<" ";
                g << "<tr>";
                g << "<td>" << it.getTitle() << "</td>";
                g << "<td>" << it.getPresenter() << "</td>";
                g << "<td>" << it.getTime().getMinutes() << ":"
                  << it.getTime().getSeconds() << "</td>";
                g << "<td>" << it.getLikes() << "</td>";
                g << "<td>" << it.getLink() << "</td>";
                g << "</tr>";
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
