#include <iostream>
#include "painting.h"
#include "repo.h"
#include "ctrl.h"
#include "ui.h"

using namespace std;


int main()
{
    repo G = repo();
    repo S = repo();
    ctrl C = ctrl( G, S );
    C.addPainting( painting{"William", "Jackson", 1969} );
    C.addPainting( painting{"Will", "Jack", 1999} );
    C.addPainting( painting{"WillIam", "Jackie", 2013} );
    ui UI = ui( C );
    UI.run();

    return 0;
}
