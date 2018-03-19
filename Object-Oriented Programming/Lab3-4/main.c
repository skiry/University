#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Material.h"
#include <string.h>
#include "DynamicArray.h"
#include "UI.h"

int main() {

	DynamicArray* Repository = newArray();
	Controller* controller = createController(Repository);
	UI* Ui = createUI(controller);
	run(Ui);
	deleteAll(Ui);

	return 0;
}
