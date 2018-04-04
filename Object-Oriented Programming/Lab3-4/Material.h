#pragma once

typedef struct {
	int day;
	int month;
	int year;
} Date;

typedef struct {
	char* name;
	char* supplier;
	int quantity;
	Date expDate;
} Material;

Material* newMaterial(char* name, char* supplier, int quantity, Date expDate);
/*
input : name, supplier, quantity, date
ouput : the material with the respectively data
*/

void throwMaterial(Material* m);
//delete the material, free the memory

void setName(Material* m, char* name);
//name setter

char* getName(Material* m);
//name getter

char* getSupplier(Material* m);
//supplier getter

int getQuantity(Material* m);
//quantity getter

Date getDate(Material* m);
//date getter