#include "Material.h"
#include <string.h>
#include <stdlib.h>

Material* newMaterial(char* name, char* supplier, int quantity, Date expDate) {

	Material* m = (Material*)malloc(sizeof(Material));

	m -> name = (char*)malloc(sizeof(char) * strlen(name) + 1);
	strcpy(m -> name, name);

	m -> supplier = (char*)malloc(sizeof(char) * strlen(supplier) + 1);
	strcpy(m -> supplier, supplier);
	
	m -> quantity = quantity;
	m -> expDate = expDate;

	return m;
}

void throwMaterial(Material* m) {

	free(m -> name);
	free(m -> supplier);
	free(m);
}

char* getName(Material* m) {
	return m -> name;
}

void setName(Material* m, char* name) {
	strcpy(m -> name, name);
}

char* getSupplier(Material* m) {
	return m -> supplier;
}

int getQuantity(Material* m) {
	return m -> quantity;
}

Date getDate(Material* m) {
	return m -> expDate;
}