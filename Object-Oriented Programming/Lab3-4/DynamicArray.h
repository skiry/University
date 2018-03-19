#pragma once
#include "Material.h"

typedef Material* myType;
typedef char value;
typedef Material with;

typedef struct {
	int capacity;
	int len;
	void** elems;
} DynamicArray;

DynamicArray* newArray();
//dynamic array with initial size 10 creator

DynamicArray* resize(DynamicArray* arr);
//dynamic array with the initial size twice the capacity of the previous array creator

DynamicArray* copyOfRepo(DynamicArray* arr);
//returns an exact copy of arr

void wipeArray(DynamicArray* arr);
//delete all the materials and free up the memory

int addElem(DynamicArray* arr, void*);
//add an element to the array

void swap(void** a, void** b);
//swap materials between themselves

int removeByValue(DynamicArray* arr, value* val);
//remove an element - val - by its name

void updateByValue(DynamicArray* arr, value* val, void*);
/*
input : array - a dyn array, val - a name, this - a material
ouput : the material to be deleted
update the material with the name 'val' with 'this'
*/

void printDyn(DynamicArray* arr);
//print arr

int inRepo(DynamicArray* arr, value* val);
//check if val in arr

int combination(char*a, char* b);
//return 1 if b is a substring of a, 0 otherwise

int dateGT(Date a);
//check if a is past its exp date
//return 1 if True, 0 if False

int suppMats(DynamicArray *repo, char* sup, DynamicArray** result);
//For a given supplier, see all materials, sorted ascending by name.

int repOpts(DynamicArray* repo, char* string, int nr, DynamicArray** res, int(*function)(int a, int b));
//function for reading a supplier and printing the materials with quantity < nr

int asc(int a, int b);
//ascending function for sorting

int desc(int a, int b);
//descending function for sorting

int thYear(DynamicArray* repo, char* string, DynamicArray** result, int(*choose)(Material*));
//filter the materials that have been produced this year

int goodYear(Material* a);
//return 1 if a has been produced in year 2018

int goodDate(Material* a);
//return 1 if a it's past its expiration date