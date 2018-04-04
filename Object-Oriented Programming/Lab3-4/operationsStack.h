#pragma once
#include "Material.h"
#include "DataStructures.h"

Operation* createOperation(Material* a, char* b); 
//create an operation for material a with the accordingly request, i.e, b

void push(OperationStack* a, Operation* b);
//add the operation b to the stack a

void deleteOperation(Operation* a);
//delete the operation a

int makeUndo(OperationStack* a, DynamicArray* repo);
//undo operation

int makeRedo(OperationStack* a, DynamicArray* repo);
//undo operation

OperationStack* createStack();
//operations stack initializer

void deleteStack(OperationStack* a);
//delete the operations stack a