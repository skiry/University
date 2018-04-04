#pragma once
#include "Song.h"

typedef int TElement;
//typedef Song TElement;

class DynamicArray {
private:
	int capacity;
	int size;
	TElement* elems;

public:
	DynamicArray(int k = 10);
	//constructor

	DynamicArray(const DynamicArray& arr);
	//& does not make a copy for arr and points to the same address as the called one
	
	DynamicArray& operator=(const DynamicArray& arr);
	//assignment operator

	~DynamicArray();
	//destructor
};