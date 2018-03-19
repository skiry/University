#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Material.h"
#include <string.h>
#include "DynamicArray.h"
#include "UI.h"
#include "undoController.h"

int main() {

	DynamicArray* Repository = newArray();
	undoCtrl* undo = newUndo();
	Controller* controller = createController(Repository);
	UI* Ui = createUI(controller, undo);
	run(Ui);
	deleteAll(Ui);

	return 0;
}
