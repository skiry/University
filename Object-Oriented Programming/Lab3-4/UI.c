#include <stdio.h>
#include "UI.h"
#include "DynamicArray.h"
#include <string.h>
#include <stdlib.h>

UI* createUI(Controller* ctrl) {
	UI* ui = (UI*)malloc(sizeof(UI));
	ui -> ctrl = ctrl;

	return ui;
}

void run(UI* ui) {
	int True = 1;
	Controller* ctrl = ui -> ctrl;
	///
	Date d1, d2, d3, d4, d5;
	d1.day = 8;
	d1.month = 3;
	d1.year = 2018;

	Material* a = newMaterial("Apa", "Dorna", 100, d1);

	d2 = d1;
	d2.day += 12;
	d2.month = 7;
	Material* b = newMaterial("Water", "Aqua", 20, d2);

	d3.day = 20;
	d3.month = 10;
	d3.year = 2015;
	Material* c = newMaterial("Chips", "Lays", 10, d3);

	d4.day = 20;
	d4.month = 10;
	d4.year = 2019;
	Material* d = newMaterial("Banana", "Colombia", 200, d4);

	d5.day = 1;
	d5.month = 1;
	d5.year = 2016;
	Material* e = newMaterial("Premium Water", "Blk.", 5, d5);

	Material* f = newMaterial("Milk", "Cow's milk", 210, d4);
	Material* g = newMaterial("Juice", "Olympus", 120, d2);
	Material* h = newMaterial("Candies", "Chockotoff", 30, d3);
	//Material* i = newMaterial("Bread", "Brutarelu", 890, d5);
	addMaterial(ctrl, a);
	addMaterial(ctrl, b);
	addMaterial(ctrl, c);
	addMaterial(ctrl, d);
	addMaterial(ctrl, e);
	addMaterial(ctrl, f);
	addMaterial(ctrl, g);
	addMaterial(ctrl, h);
	//addMaterial(ctrl, i);
	//Material* j = newMaterial("Sticks", "Chio", 4000, d1);

	while (True) {
		printf("\n0. Exit.");
		printf("\n1. Add a material. \n2. Update a material. \n3. Remove a material.");
		printf("\n4. See materials past their exp date, search by string.");
		printf("\n5. For a given supplier sort materials ascending by name.");
		printf("\n6. See materials with quantity less than a number, search by supplier.");
		printf("\n7. See materials from this year, search by string.");
		printf("\n8. Print all\n");
		int first;
		scanf("%d", &first);
		switch (first) {
		case 0:
			printf("bye");
			break;
		case 1:
			readAdd(ctrl);
			break;
		case 2:
			readUpdate(ctrl);
			break;
		case 3:
			readDelete(ctrl);
			break;
		case 4:
			thisYear(ctrl, goodDate);
			break;
		case 5:
			readSupp(ctrl);
			break;
		case 6:
			readOpt(ctrl);
			break;
		case 7:
			thisYear(ctrl, goodYear);
			break;
		case 8:
			printAll(ctrl);
			break;
		default:
			printf("\nPay attention!");
			break;
		}
		if (first == 0) True = 0;
	}
}


void readAdd(Controller* ctrl) {
	char *name = (char*)malloc(100 * sizeof(char)), *supp = (char*)malloc(100 * sizeof(char));
	int q;
	printf("\nName: ");
	scanf("%s", name);
	printf("\nSupplier: ");
	scanf("%s", supp);
	printf("\nQuantity: ");
	scanf("%d", &q);
	Date expDate = readDate();

	Material* this = newMaterial(name, supp, q, expDate);

	int result = addMaterial(ctrl, this);
	switch (result) {
	case 2:
		printf("\nNames should not be empty.");
		break;
	case 3:
		printf("\nYou added quantity 0.");
		break;
	case 4:
		printf("\nDate not valid.");
		break;
	case 5:
		printf("\nExistent material.");
		break;
	default:
		printf("\nMaterial added succesfully!");
		break;
	}
	free(supp);
	free(name);
}

Date readDate() {
	Date a;
	int day, month, year;
	printf("\nDay: ");
	scanf("%d", &day);
	printf("\nMonth: ");
	scanf("%d", &month);
	printf("\nYear: ");
	scanf("%d", &year);

	a.day = day;
	a.month = month;
	a.year = year;

	return a;
}

void printAll(Controller* ctrl) {
	printDyn(ctrl -> repo);
}

void readUpdate(Controller* ctrl) {
	char* name = (char*)malloc(100 * sizeof(char)), *supp = (char*)malloc(100 * sizeof(char));
	char* old = (char*)malloc(100 * sizeof(char));
	int q;
	printf("\nOld Name: ");
	scanf("%s", old);
	printf("\nNew Name: ");
	scanf("%s", name);
	printf("\nNew Supplier: ");
	scanf("%s", supp);
	printf("\nNew Quantity: ");
	scanf("%d", &q);
	Date expDate = readDate();

	Material* this = newMaterial(name, supp, q, expDate);

	int result = updateByName(ctrl, old, this);
	switch (result) {
	case 2:
		printf("\nNames should not be empty.");
		break;
	case 3:
		printf("\nYou added quantity 0.");
		break;
	case 4:
		printf("\nDate not valid.");
		break;
	case 5:
		printf("\nMaterial not found.");
		throwMaterial(this);
		break;
	case 6:
		printf("\nCannot update with sth existent already.");
		throwMaterial(this);
		break;
	default:
		printf("\nMaterial added succesfully!");
		break;
	}
	free(old);
	free(name);
	free(supp);
}

void readDelete(Controller* ctrl) {
	char* name = (char*)malloc(100 * sizeof(char));
	printf("\nProduct to throw away: ");
	scanf("%s", name);

	if (delMaterial(ctrl, name)) printf("\nMaterial thrown away");
	else printf("\nMaterial not found");

	free(name);
}

void readSupp(Controller* ctrl) {
	//For a given supplier, see all materials, sorted ascending by name
	char* supp = (char*)malloc(100 * sizeof(char));;
	printf("\nSupplier to check: ");
	scanf("%s", supp);
	DynamicArray *result = newArray();
	int length = seeMats(ctrl, supp, &result);

	for (int i = 0; i < length - 1; ++i)
		for (int j = i + 1; j < length; ++j)
			if (strcmp(getName(result -> elems[i]), getName(result -> elems[j])) > 0)
				swap(&result -> elems[i], &result -> elems[j]);
	for (int i = 0; i < length; ++i)
		printf("\nName %d is %s ", i + 1, getName(result -> elems[i]));

	wipeArray(result);
	free(supp);

}

void deleteAll(UI* ui) {
	deleteCtrl(ui -> ctrl);
	free(ui);
}

void readOpt(Controller* ctrl) {
	char* supp = (char*)malloc(100 * sizeof(char));;
	printf("\nSupplier to check: ");
	scanf("%s", supp);

	int nr, ch;
	printf("\nNumber: ");
	scanf("%d", &nr);

	printf("\n1. Ascending.\n2. Descending.\n");
	scanf("%d", &ch);
	DynamicArray *result = newArray();
	int length;
	if (ch == 1) length = seeOpts(ctrl, supp, nr, &result, asc);
	else if (ch == 2) length = seeOpts(ctrl, supp, nr, &result, desc);

	for (int i = 0; i < length; ++i)
		printf("\nThe product %s produced by '%s' has the quantity(%d) less than %d.",
		       getName(result -> elems[i]), getSupplier(result -> elems[i]),
		       getQuantity(result -> elems[i]), nr);

	wipeArray(result);
	free(supp);

}

void thisYear(Controller* ctrl, int(*choose)(Material* a)) {
	char* string = (char*)malloc(100 * sizeof(char));
	size_t sz = 99;
	printf("\nString to look for: ");
	getline(&string, &sz, stdin); // read the previous \n
	getline(&string, &sz, stdin); // read the string which may be empty
	string[strlen(string) - 1] = '\0'; // replace \n with \0
	DynamicArray *result = newArray();
	int length;
	length = filterYear(ctrl, string, &result, choose);
	Date d;
	for (int i = 0; i < length; ++i) {
		d = getDate(result -> elems[i]);
		if (choose == goodYear)
			printf("\nThe product %s is produced on %d/%d/%d, this year.",
			       getName(result -> elems[i]), d.day, d.month, d.year);
		else if (choose == goodDate)
			printf("\nThe product %s has '%s' in its name and it is past its expiration date.",
			       getName(result -> elems[i]), string);
	}
	wipeArray(result);
	free(string);
}