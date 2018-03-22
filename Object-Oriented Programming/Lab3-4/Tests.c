#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Material.h"
#include <string.h>
#include "DynamicArray.h"
#include <assert.h>
#include "Ctrl.h"

int main() {

	//declare some dates
	Date d1, d2, d3;
	d1.day = 8;
	d1.month = 3;
	d1.year = 2018;
	d2 = d3 = d1;
	d2.day += 10;
	d3.day += 5;
	d3.month += 2;
	//declare 3 objects
	Material* a, *b, *c;
	a = newMaterial("Water", "Dorna", 100, d1);
	b = newMaterial("Bread", "Velpitar", 20, d1);
	c = newMaterial("Juice", "Coca-Cola", 45, d3);

	//tester function for Material modules
	assert(strcmp(getName(a), "Water") == 0);
	assert(strcmp(getSupplier(b), "Velpitar") == 0);
	assert(strcmp(getSupplier(c), "Fanta") < 0);

	assert(getQuantity(a) == 100);
	assert(getQuantity(b) == 20);
	assert(getQuantity(c) == 45);

	setName(c, "Suc");
	assert(strcmp(getName(c), "Suc") == 0);

	//Test addElement function
	DynamicArray* arr = newArray();
	assert(addElem(arr, a) == 0);
	assert(addElem(arr, a) == 1);
	assert(addElem(arr, b) == 0);
	assert(addElem(arr, a) == 1);
	assert(addElem(arr, b) == 1);
	//Test inRepo function
	assert(inRepo(arr,"Water") == 1);
	assert(inRepo(arr,"water") == 0);
	assert(inRepo(arr,"velPitar") == 0);
	assert(inRepo(arr,"velpitar") == 0);
	assert(inRepo(arr,"VelPitar") == 0);
	assert(inRepo(arr,"Velpitar") == 0);
	assert(inRepo(arr,"Bread") == 1);
	//Test asc, desc functions
	assert(asc(getQuantity(a), getQuantity(b)) == 1);
	assert(asc(getQuantity(b), getQuantity(a)) == 0);
	assert(desc(getQuantity(b), getQuantity(a)) == 1);
	assert(desc(getQuantity(a), getQuantity(b)) == 0);
	//Test goodYear function
	assert(goodYear(a) == goodYear(b));
	//Test goodDate function
	assert(goodDate(a) == 1);
	assert(goodDate(b) == goodDate(a));
	//Test dateGT function
	assert(dateGT(getDate(a)) == 1);
	assert(dateGT(getDate(b)) == 1);
	assert(dateGT(getDate(c)) != dateGT(getDate(a)));
	assert(dateGT(getDate(b)) != dateGT(getDate(c)));
	//wipe the memory of the materials
	throwMaterial(a);
	throwMaterial(b);
	throwMaterial(c);

	Controller* ctrl = createController(arr);
	Material* d;
/**	d = newMaterial("", "Coca-Cola", 45, d3);
	assert(addMaterial(ctrl,d) == 2);
	//throwMaterial(d);

	d = newMaterial("Suc", "", 45, d3);
	assert(addMaterial(ctrl,d) == 2);
	//throwMaterial(d);

	d = newMaterial("Suc", "Coca-Cola", 0, d3);
	assert(addMaterial(ctrl,d) == 3);
	//throwMaterial(d);

	d = newMaterial("Water", "Coca-Cola", 45, d3);
	assert(addMaterial(ctrl,d) == 5);
	//throwMaterial(d);
*/
	free(ctrl);
	free(arr -> elems);
	free(arr);
	printf("All the tests ran succesfully!\n");
	return 0;
}