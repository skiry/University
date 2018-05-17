#ifndef REPO_H
#define REPO_H
#include <bits/stdc++.h>
#include "painting.h"

class repo
{
protected:
    std::vector<painting> list;
public:
    repo(){}
    void addPainting( painting p ) { list.push_back(p); }
    void removePainting( painting p ) {
        for(auto i : list)
            std::cout<<i.getArtist()<<'\n';
        for( int i = 0; i < list.size(); ++i )
            if( list[i].isThis(p) ){
                std::swap(list[i], list[list.size() - 1]);
                i = list.size() + 2;
            }
        list.erase(list.end());
    }
    std::vector<painting> get() { return list; }
};

#endif // REPO_H
