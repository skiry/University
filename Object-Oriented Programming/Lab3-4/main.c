#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Material.h"
#include <string.h>
#include "DynamicArray.h"
#include "UI.h"
#include "undoController.h"
#include "operationsStack.h"

int main() {

	DynamicArray* Repository = newArray();
	DynamicArray* undo = newUndo();
	//OperationStack* isUndo = createStack();
	//OperationStack* isRedo = createStack();
	Controller* controller = createController(Repository);//, isUndo, isRedo);
	UI* Ui = createUI(controller, undo);
	run(Ui);
	deleteAll(Ui);

	return 0;
}
