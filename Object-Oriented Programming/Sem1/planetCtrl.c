#include "planetCtrl.h"
#include <stdlib.h>

Controller* createController(PlanetRepo* r) {

	Controller* ctrl = (Controller*)malloc(sizeof(Controller));
	ctrl -> repo = r;
	return ctrl;
}

void destroyController(Controller* ctrl) {
	destroyRepo(ctrl -> repo);
	free(ctrl);
}

void addPlanetCtrl(Controller* ctrl, Planet* p) {
	addPlanet(ctrl -> repo, p);
}