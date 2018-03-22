#include "operationsStack.h"
#include <string.h>
#include <stdlib.h>
#include "Material.h"
#include "DynamicArray.h"

Operation* createOperation(Material* a, char* b) {
	Operation* new = (Operation*)malloc(sizeof(Operation));
	new -> op = (char*)malloc(sizeof(char) * strlen(b) + 1);
	new -> obj = newMaterial(getName(a), getSupplier(a), getQuantity(a), getDate(a));
	return new;
}

void push(OperationStack* a, Operation* b) {
	a -> elems[a -> len++] = b;
	a -> valMax ++;
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
	for (int i = 0; i < a -> len; ++i)
		deleteOperation(a -> elems[i]);
	free(a -> elems);
	free(a);
}

int makeUndo(OperationStack* a, DynamicArray* repo) {
	if (a -> len == 0) return 0;
	else {
		a -> len--;
		Operation* op = a -> elems[a -> len];
		if(strcmp(op -> op, "Add") == 0) {
			addElem(repo, newMaterial(getName(op -> obj), getSupplier(op -> obj), 
				getQuantity(op -> obj), getDate(op -> obj)));
		}
		else if(strcmp(op -> op, "Delete") == 0) {
			removeByValue(repo,getName(op -> obj),a,a,0);
		}
		else if(strcmp(op -> op, "Update") == 0) {
			removeByValue(repo,getName(op -> obj),a,a,0);
			addElem(repo, newMaterial(getName(op -> obj), getSupplier(op -> obj), 
				getQuantity(op -> obj), getDate(op -> obj)));
		}
	}
	return 1;
}

int makeRedo(OperationStack* a, DynamicArray* repo) {
	if (a -> len == a -> valMax) return 0;
	else {
		a -> len--;
		Operation* op = a -> elems[a -> len];
		if(strcmp(op -> op, "Add") == 0) {
			addElem(repo, newMaterial(getName(op -> obj), getSupplier(op -> obj), 
				getQuantity(op -> obj), getDate(op -> obj)));
		}
		else if(strcmp(op -> op, "Delete") == 0) {
			removeByValue(repo,getName(op -> obj),a,a,0);
		}
		else if(strcmp(op -> op, "Update") == 0) {
			removeByValue(repo,getName(op -> obj),a,a,0);
			addElem(repo, newMaterial(getName(op -> obj), getSupplier(op -> obj), 
				getQuantity(op -> obj), getDate(op -> obj)));
		}
	}
	return 1;
}

