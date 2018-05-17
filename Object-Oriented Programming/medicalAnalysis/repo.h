#ifndef REPO_H
#define REPO_H
#include "ma.h"
#include <fstream>
class repo
{
private:
    std::vector<std::shared_ptr<MA>> list;
public:
    repo() {}
    //~repo() { for( auto& i : list )
        //    delete i;
//            }
    void addMA( std::shared_ptr<MA> b ) { list.push_back(b); }

    std::vector<std::shared_ptr<MA>> getList() { return list; }

    std::string ill(int m){
        bool ok = false;
        for( auto &i : list )
            if( i->getMonth() == m && i->isResultOK() )
                ok = true;
        if( ok ) return "You are not ill this time";
            else return "You are ill.";
    }


    void writeToFile(int d1, int d2) {
        std::ofstream g("analysis.txt");
        for( auto &i : list )
            if( i->getMonth() >= d1 && i->getMonth() <= d2 )
                g << i->toString();
    }

};

#endif // REPO_H
