#ifndef UI_H
#define UI_H
#include "ctrl.h"

class ui
{
private:
    ctrl c;
public:
    ui() {}
    ui( const ctrl& _c ) : c{ _c } {}
    void addMA();
    void print();
    void run();
    void ill();
    void w();
};

#endif // UI_H
