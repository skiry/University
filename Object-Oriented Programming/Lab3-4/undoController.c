#include "undoController.h"
#include <stdio.h>

undoCtrl* newUndo() {
	undoCtrl* undo = (undoCtrl*)malloc(sizeof(undoCtrl));
	undo -> capacity = 2;
	undo -> length = 0;
	undo -> repos = (DynamicArray**)malloc(sizeof(DynamicArray) * undo -> capacity);
	undo -> valMax = 0;
	return undo;

}

undoCtrl* resizeCtrl(undoCtrl* unCtrl) {
	printf("\nAm facut resize.\n");
	unCtrl -> capacity *= 2;
	unCtrl -> repos = (DynamicArray**)realloc(unCtrl -> repos, sizeof(DynamicArray) * unCtrl -> capacity);
	return unCtrl;
}

void addRepo(undoCtrl* unCtrl, DynamicArray* unRepo) {
	if (unCtrl -> length == unCtrl -> capacity - 1)
		unCtrl = resizeCtrl(unCtrl);

	unCtrl -> repos[unCtrl -> length++] = copyOfRepo(unRepo);
	if(unCtrl -> length > unCtrl -> valMax) unCtrl -> valMax = unCtrl -> length;
}

void removeUndo(undoCtrl* undo) {
	for (int i = 0; i < undo -> valMax; ++i) {
		wipeArray(undo -> repos[i]);
	}
	free(undo -> repos);
	free(undo);
}

int doUndo(undoCtrl* unCtrl, Controller* ctrl) {
	if (unCtrl -> length - 1== 0) return 0;
	else {
		unCtrl -> length -= 1;
		ctrl -> repo = unCtrl -> repos[unCtrl -> length - 1];
		return 1;
	}
}

int doRedo(undoCtrl* unCtrl, Controller* ctrl) {
	if (unCtrl -> length == unCtrl -> valMax) return 0;
	else {
		ctrl -> repo = unCtrl -> repos[unCtrl -> length++];
		return 1;
	}
}