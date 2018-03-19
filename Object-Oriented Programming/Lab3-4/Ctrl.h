#pragma once
#include "DynamicArray.h"


typedef struct {
	DynamicArray* repo;
} Controller;

Controller* createController(DynamicArray* repo);
//create controller

int addMaterial(Controller* ctrl, myType elem);
//add an element to the list of materials

int delMaterial(Controller* ctrl, value* val);
//remove an element - val - by its name

int updateByName(Controller* ctrl, value* val, with* this);
/*
input :val - a name, this - a material
ouput : -
update the material with the name 'val' with 'this'
*/

int validDate(Date a);
//checks if a is a valid Date

int seeMats(Controller *ctrl, char* cuv, DynamicArray** result);
//For a given supplier, see all materials, sorted ascending by name.

void deleteCtrl(Controller* ctrl);
// delete controller

int seeOpts(Controller* ctrl, char* string, int nr, DynamicArray** res, int(*function)(int a, int b));
//function for reading a supplier and printing the materials with quantity < nr

int filterYear(Controller* ctrl, char* string, DynamicArray** result, int(*choose)(Material* a));
//filter materials made this year