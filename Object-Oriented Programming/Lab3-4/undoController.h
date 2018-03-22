#pragma once
#include "Ctrl.h"
#include <stdlib.h>
#include "DynamicArray.h"

DynamicArray* newUndo();
//creates a new undo-redo list

DynamicArray* resizeCtrl(DynamicArray* unCtrl);
//double the capacity of unCtrl

void addRepo(DynamicArray* unCtrl, DynamicArray* unRepo);
//add unRepo to unCtrl

void removeUndo(DynamicArray* undo);
//deletes the undo-redo list

int doUndo(DynamicArray* unCtrl, Controller* ctrl);
//step 1 time back

int doRedo(DynamicArray* unCtrl, Controller* ctrl);
//step 1 time forward