#include "operationsStack.h"
#include <string.h>
#include <stdlib.h>

Operation* createOperation(Material* a, char* b) {
	Operation* new = (Operation*)malloc(sizeof(Operation));
	new -> op = (char*)malloc(sizeof(char) * strlen(b) + 1);
	new -> obj = newMaterial(getName(a), getSupplier(a), getQuantity(a), getDate(a));
	return new;
}

void push(OperationStack* a, Operation* b) {
	a -> elems[a -> len++] = b;
}

void deleteOperation(Operation* a) {
	free(a -> op);
	throwMaterial(a -> obj);
	free(a);
}

OperationStack* createStack() {
	OperationStack* new = (OperationStack*)malloc(sizeof(OperationStack));
	new -> elems = (Operation**)malloc(sizeof(Operation*) * 200);
	new -> cap = 200;
	new -> len = 0;
	return new;
}

void deleteStack(OperationStack* a) {
	for(int i = 0; i < a -> len; ++i)
		deleteOperation(a -> elems[i]);
	free(a -> elems);
	free(a);
}