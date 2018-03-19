#include "Ctrl.h"
#include <string.h>
#include <stdlib.h>
#include "UI.h"
#include <stdio.h>

Controller* createController(DynamicArray* repo) {
	Controller* ctrl = (Controller*)malloc(sizeof(Controller));
	ctrl -> repo = repo;

	return ctrl;
}

int addMaterial(Controller* ctrl, myType elem) {
	int ok = 1;
	if (strcmp(elem -> name, "") == 0 || strcmp(elem -> supplier, "") == 0 )
		ok = 2;
	if (elem -> quantity == 0)
		ok = 3;
	if (validDate(elem -> expDate) == 0)
		ok = 4;
	if (inRepo(ctrl -> repo, getName(elem)))
		ok = 5;
	int sec;
	if (ok == 1) sec = addElem(ctrl -> repo, elem);
	else throwMaterial(elem);

	if (sec == 1) throwMaterial(elem);
	return ok;
}

int validDate(Date a) {
	int ok = 0;
	if (a.year >= 1980 && a.year <= 2100) ok++;
	if (a.month >= 1 && a.month <= 12) ok++;
	if (a.month == 2 && a.day >= 1 && a.day <= 28) ok++;
	else if (a.day >= 1 && a.day <= 31) ok++;

	if (ok == 3) return 1;
	return 0;
}

int delMaterial(Controller* ctrl, value* val) {
	return removeByValue(ctrl -> repo, val);
}

int updateByName(Controller* ctrl, value* val, with* this) {
	int ok = 1;
	if (strcmp(this -> name, "") == 0 || strcmp(this -> supplier, "") == 0)
		ok = 2;
	if (this -> quantity == 0)
		ok = 3;
	if (validDate(this -> expDate) == 0)
		ok = 4;
	if (ok == 1) {
		if (inRepo(ctrl -> repo, val)) {
			if (inRepo(ctrl -> repo, getName(this)) == 0) {
				updateByValue(ctrl -> repo, val, this);
			}
			else ok = 6;
		}
		else ok = 5;
	}
	else throwMaterial(this);

	return ok;
}

int seeMats(Controller *ctrl, char* cuv, DynamicArray** result) {
	return suppMats(ctrl -> repo, cuv, result);
}

void deleteCtrl(Controller* ctrl) {
	wipeArray(ctrl -> repo);
	free(ctrl);
}

int seeOpts(Controller* ctrl, char* string, int nr, DynamicArray** res, int(*function)(int a, int b)) {
	return repOpts(ctrl -> repo, string, nr, res, function);
}

int filterYear(Controller* ctrl, char* string, DynamicArray** result, int(*choose)(Material* a)) {
	return thYear(ctrl -> repo, string, result, choose);
}