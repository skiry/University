#include "undoController.h"
#include <stdio.h>

DynamicArray* newUndo() {

	DynamicArray* undo = (DynamicArray*)malloc(sizeof(DynamicArray));
	undo -> capacity = 10;
	undo -> len = 0;
	undo -> elems = (void**)malloc(sizeof(DynamicArray) * undo -> capacity);
	undo -> valMax = 0;
	return undo;
}

DynamicArray* resizeCtrl(DynamicArray* unCtrl) {
	unCtrl -> capacity *= 2;
	unCtrl -> elems = (void**)realloc(unCtrl -> elems, sizeof(DynamicArray) * unCtrl -> capacity);
	return unCtrl;
}

void addRepo(DynamicArray* unCtrl, DynamicArray* unRepo) {
	if (unCtrl -> len == unCtrl -> capacity - 1)
		unCtrl = resizeCtrl(unCtrl);

	if (unCtrl -> len == 0) {
		unCtrl -> elems[unCtrl -> len++] = copyOfRepo(unRepo);
		unCtrl -> valMax = 1;
	}
	else {
			for (int i = unCtrl -> len; i < unCtrl -> valMax; ++i)
				wipeArray(unCtrl -> elems[i]);
			unCtrl -> elems[unCtrl -> len++] = copyOfRepo(unRepo);
			unCtrl -> valMax = unCtrl -> len;
		}
}

void removeUndo(DynamicArray* undo) {
	for (int i = 0; i < undo -> valMax; ++i) {
		wipeArray(undo -> elems[i]);
	}
	free(undo -> elems);
	free(undo);
}

int doUndo(DynamicArray* unCtrl, Controller* ctrl) {
	if (unCtrl -> len - 1 <= 0) return 0;
	else {
		unCtrl -> len -= 1;
		wipeArray(ctrl -> repo);
		ctrl -> repo = copyOfRepo(unCtrl -> elems[unCtrl -> len - 1]);
		return 1;
	}
}

int doRedo(DynamicArray* unCtrl, Controller* ctrl) {
	if (unCtrl -> len == unCtrl -> valMax) return 0;
	else {
		wipeArray(ctrl -> repo);
		ctrl -> repo = copyOfRepo(unCtrl -> elems[unCtrl -> len++]);
		return 1;
	}
}