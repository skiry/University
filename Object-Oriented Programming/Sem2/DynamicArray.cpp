#include "DynamicArray.h"

DynamicArray::DynamicArray(int cap) {
	this -> capacity = cap;
	this -> size = 0;
	this -> elems = new TElement[this -> capacity];
}

DynamicArray::DynamicArray(const DynamicArray& arr) {
	this -> capacity = arr.capacity;
	this -> size = arr.size;
	this -> elems = new TElement[this -> capacity];
	for (int i = 0; i < arr.capacity; ++i) {
		this -> elems[i] = arr.elems[i];
	}
}

DynamicArray& DynamicArray::operator=(const DynamicArray& arr) {
	if (this == &arr) return *this;

	delete[] this -> elems;
	this -> capacity = arr.capacity;
	this -> size = arr.size;
	this -> elems = new TElement[arr.capacity];
	for (int i = 0; i < arr.size; ++i)
		this -> elems[i] = arr.elems[i];

	return *this;
}

DynamicArray::~DynamicArray() {
	delete[] this -> elems;
}