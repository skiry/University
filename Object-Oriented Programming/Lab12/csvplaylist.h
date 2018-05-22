#ifndef CSVPLAYLIST_H
#define CSVPLAYLIST_H
#include "fileplaylist.h"
#include <fstream>

class CSVPlaylist : public FilePlaylist
{
public:
    CSVPlaylist( std::string title )
    {
        fileName = title;
    }
    void saveToFile() override
    {
        std::ofstream g( fileName );
        std::cout << wList.size() << " ";

        for ( auto it : wList) {
            g << it;
        }

    }

    void displayWatchList() override
    {
        std::string exec = "nano ";
        exec += fileName;
        system( &exec[0u] );
    }

    std::string wat()
    {
        return "CSV";
    }
};
#endif // CSVPLAYLIST_H
