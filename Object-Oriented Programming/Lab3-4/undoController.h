#pragma once
#include "DynamicArray.h"
#include <stdlib.h>
#include "Ctrl.h"

typedef struct {
	DynamicArray** repos;
	int length;
	int capacity;
	int valMax;
} undoCtrl;

undoCtrl* newUndo();
//creates a new undo-redo list

undoCtrl* resizeCtrl(undoCtrl* unCtrl);
//double the capacity of unCtrl

void addRepo(undoCtrl* unCtrl, DynamicArray* unRepo);
//add unRepo to unCtrl

void removeUndo(undoCtrl* undo);
//deletes the undo-redo list

int doUndo(undoCtrl* unCtrl, Controller* ctrl);
//step 1 time back

int doRedo(undoCtrl* unCtrl, Controller* ctrl);
//step 1 time forward