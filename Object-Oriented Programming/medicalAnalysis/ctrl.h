#ifndef CTRL_H
#define CTRL_H
#include "repo.h"

class ctrl
{
private:
    repo r;
public:
    ctrl() {}
    ctrl( const repo& _r ) : r{ _r } {}

    bool addMA( std::shared_ptr<MA> b) {
        r.addMA(b);
        return true;
    }

    std::vector<std::shared_ptr<MA>> get() { return r.getList(); }
    std::string ill(int m){ return r.ill(m);  }
    void wr(int d1, int d2) { r.writeToFile(d1, d2);}
};

#endif // CTRL_H
