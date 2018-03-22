#pragma once
#include "Material.h"

typedef struct {
	Material* obj;
	char* op;
} Operation;

typedef struct {
	Operation** elems;
	int len;
	int cap;
} OperationStack;

Operation* createOperation(Material* a, char* b); 
//create an operation for material a with the accordingly request, i.e, b

void push(OperationStack* a, Operation* b);
//add the operation b to the stack a

void deleteOperation(Operation* a);
//delete the operation a

OperationStack* createStack();
//operations stack initializer

void deleteStack(OperationStack* a);
//delete the operations stack a