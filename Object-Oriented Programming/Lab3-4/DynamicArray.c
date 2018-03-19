#include "DynamicArray.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

DynamicArray* newArray() {

	DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
	arr -> capacity = 10;
	arr -> len = 0;
	arr -> elems = (void**)malloc(10 * sizeof(Material*));
	return arr;
}

DynamicArray* resize(DynamicArray* arr) {
	arr -> capacity *= 2;
	arr -> elems = (void**)realloc(arr -> elems, arr -> capacity * sizeof(DynamicArray));
	return arr;
}

DynamicArray* copyOfRepo(DynamicArray* arr2) {

	DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
	arr -> capacity = arr2 -> capacity;
	arr -> len = arr2 -> len;
	arr -> elems = (void**)malloc(arr2 -> capacity * sizeof(Material*));
	for (int i = 0; i < arr -> len; i++) {
		Material* m = arr2 -> elems[i];
		arr -> elems[i] = newMaterial(getName(m), getSupplier(m), getQuantity(m), getDate(m));
	}
	return arr;
}

void wipeArray(DynamicArray* arr) {
	for (int i = 0; i < arr -> len; i++) {
		throwMaterial(arr -> elems[i]);
	}
	free(arr -> elems);
	free(arr);
}

int addElem(DynamicArray* arr, void* element) {
	Material* elem = element;
	Material* copy;
	int done = 0;
	if (arr -> len == arr -> capacity - 1)
		arr = resize(arr);

	for (int i = 0; i < arr -> len; i++) {
		copy = arr -> elems[i];
		if (strcmp(getName(copy), elem -> name) == 0) {
			copy -> quantity += elem -> quantity;
			done = 1;
		}
	}

	if (!done) arr -> elems[arr -> len++] = elem;
	return done;
}

void swap(void** a, void** b) {
	void *c = *a;
	*a = *b;
	*b = c;
}

int removeByValue(DynamicArray* arr, value* val) {
	for (int i = 0; i < arr -> len; i++) {
		if (combination(getName(arr -> elems[i]), val)) {
			swap(&arr -> elems[i], &arr -> elems[arr -> len - 1]);
			throwMaterial(arr -> elems[arr -> len - 1]);
			arr -> len --;
			return 1;
		}
	}
	return 0;
}

void updateByValue(DynamicArray* arr, value* val, void* thiss) {
	Material* this = thiss;
	for (int i = 0; i < arr -> len; i++) {
		if (combination(getName(arr -> elems[i]), val)) {
			throwMaterial(arr -> elems[i]);
			arr -> elems[i] = this;
		}
	}
}

void printDyn(DynamicArray* arr) {
	for (int i = 0; i < arr -> len; i++) {
		Date d = getDate(arr -> elems[i]);
		printf("\n The product %s produced by %s has %d pieces and expires on day %d of the month %d, %d.",
		       getName(arr -> elems[i]), getSupplier(arr -> elems[i]),
		       getQuantity(arr -> elems[i]), d.day, d.month, d.year);
	}
}


int inRepo(DynamicArray* arr, value* val) {
	for (int i = 0; i < arr -> len; i++) {
		if (combination(getName(arr -> elems[i]), val) &&
		        strlen(getName(arr -> elems[i])) == strlen(val)) return 1;
	}

	return 0;
}

int combination(char* a, char* b) {
	int len1 = strlen(a), len2 = strlen(b);
	for (int i = 0; i < len1; ++i) {
		int counter = 0, index = i;
		for (int j = 0; j < len2; ++j)
			if (index >= len1) return 0;
			else if (a[index++] == b[j]) ++counter;
		if (counter == len2) return 1;
	}
	return 0;
}

int suppMats(DynamicArray *repo, char* sup, DynamicArray** result) {
	int length = 0;
	Material* new;
	for (int i = 0; i < repo -> len; ++i) {
		if (combination(getSupplier(repo -> elems[i]), sup) &&
		        strlen(getSupplier(repo -> elems[i])) == strlen(sup)) {
			Material* el = repo -> elems[i];
			new = newMaterial(getName(el), getSupplier(el), getQuantity(el), getDate(el));
			addElem(*result, new);
			length++;
		}

	}

	return length;
}

int asc(int a, int b) {
	if (a > b) return 1;
	return 0;
}

int desc(int a, int b) {
	if (a < b) return 1;
	return 0;
}

int repOpts(DynamicArray* repo, char* sup, int nr, DynamicArray** res, int(*function)(int a, int b)) {
	int length = 0;
	Material* new;
	for (int i = 0; i < repo -> len; ++i) {
		if (combination(getSupplier(repo -> elems[i]), sup) &&
		        strlen(getSupplier(repo -> elems[i])) == strlen(sup) &&
		        getQuantity(repo -> elems[i]) < nr) {
			Material* el = repo -> elems[i];
			new = newMaterial(getName(el), getSupplier(el), getQuantity(el), getDate(el));
			addElem(*res, new);
			length++;
		}

	}
	for (int i = 0; i < length - 1; ++i)
		for (int j = i + 1; j < length; ++j)
			if (function(getQuantity((*res) -> elems[i]), getQuantity((*res) -> elems[j])))
				swap(&(*res) -> elems[i], &(*res) -> elems[j]);

	return length;
}

int goodYear(Material* a) {
	if (getDate(a).year == 2018) return 1;
	return 0;
}

int goodDate(Material* a) {
	if (dateGT(getDate(a))) return 1;
	return 0;
}

int thYear(DynamicArray* repo, char* string, DynamicArray** result, int(*choose)(Material* a)) {
	int length = 0;
	Material* new;
	for (int i = 0; i < repo -> len; ++i) {
		if (combination(getSupplier(repo -> elems[i]), string) && choose(repo -> elems[i])) {
			Material* el = repo -> elems[i];
			new = newMaterial(getName(el), getSupplier(el), getQuantity(el), getDate(el));
			addElem(*result, new);
			length++;
		}

	}

	return length;
}

int dateGT(Date a) {
	time_t now;
	struct tm* date;
	time(&now);
	date = localtime(&now);

	int isOk = 0;

	if (a.year < date -> tm_year + 1900) isOk = 3;
	if (a.year == date -> tm_year + 1900 && a.month < date -> tm_mon + 1) isOk = 3;
	if (a.year == date -> tm_year + 1900 && a.month == date -> tm_mon + 1) {
		if (a.day <= date -> tm_mday) isOk = 3;
	}
	if (isOk == 3) return 1;
	return 0;
}
/*
it4
bonus 2
*/