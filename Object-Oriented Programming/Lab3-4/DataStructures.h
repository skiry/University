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
	int valMax;
} OperationStack;

typedef struct {
	int capacity;
	int len;
	int valMax;
	void** elems;
} DynamicArray;