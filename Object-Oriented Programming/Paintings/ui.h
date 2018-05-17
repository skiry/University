#ifndef UI_H
#define UI_H
#include "ctrl.h"

class ui
{
private:
    ctrl c;
public:
    ui() {}
    ui( const ctrl& _c) : c{ _c } {}
    void run();
    void add();
    void move();
    void show();
    void undo();
};

#endif // UI_H
