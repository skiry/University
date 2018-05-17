#include <iostream>
#include "ma.h"
#include "repo.h"
#include "ctrl.h"
#include "ui.h"

using namespace std;

int main()
{
    MA* a, *b;
    a = new BP{"05.05.2018", 100, 65};
    b = new BMI{"10.02.2017", 18.4};

    std::cout << a->toString() << " " << b->toString() << '\n';

    repo R = repo();
    ctrl C = ctrl( R );
    ui UI = ui( C );
    UI.run();
    return 0;
}
