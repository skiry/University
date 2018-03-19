#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Material.h"
#include <string.h>
#include "DynamicArray.h"
#include <assert.h>

int main() {


	Date d1, d2, d3;
	d1.day = 8;
	d1.month = 3;
	d1.year = 2018;
	d2 = d3 = d1;
	d2.day += 10;
	d3.day += 5;
	d3.month += 2;

	Material* a, *b, *c;
	a = newMaterial("Water", "Dorna", 100, d1);
	b = newMaterial("Bread", "Velpitar", 20, d1);
	c = newMaterial("Juice", "Coca-Cola", 45, d1);

	//tester function for Material modules
	assert(strcmp(getName(a),"Water") == 0);
	assert(strcmp(getSupplier(b),"Velpitar") == 0);
	assert(strcmp(getSupplier(c),"Fanta") < 0);

	assert(getQuantity(a) == 100);
	assert(getQuantity(b) == 20);
	assert(getQuantity(c) == 45);

	setName(c,"Suc");
	assert(strcmp(getName(c),"Suc") == 0);
	
	throwMaterial(a);
	throwMaterial(b);
	throwMaterial(c);
	
	printf("All the tests ran succesfully!\n");
	return 0;
}