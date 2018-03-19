#pragma once
#include "Material.h"
#include "DynamicArray.h"

typedef struct {
	DynamicArray* vect;
} Repository;

Repository* newRepo();
//repository creator

void deleteRepo(Repository* repo);

void addElem(Repository* repo, Material* mat);

void updElem(Repository* repo, char* nume, Material* mat);

void delElem(Repository* repo, char* nume);
