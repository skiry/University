#pragma once
#include "Ctrl.h"

typedef struct{
	Controller* ctrl;
}UI;

UI* createUI(Controller* ctrl);
//create UI

void deleteAll(UI* ui);
//delete UI

void run();
//main function in UI

void readAdd(Controller* ctrl);
//read components for adding an element

void readUpdate(Controller* ctrl);
//read components for updating an element

void readDelete(Controller* ctrl);
//read components for deleting an element

Date readDate();
//function for reading a date - day, month, year

void printAll(Controller* ctrl);
//print all Materials

void readSupp(Controller *ctrl);
//function for reading a supplier and printing the materials sorted asc by name

void readSee(Controller* ctrl);
//read string for searching all elements that contain the read string

void readOpt(Controller* ctrl);
//function for reading a supplier and printing the materials with quantity < nr

void thisYear(Controller* ctrl, int(*choose)(Material* a));
//filter materials made this year