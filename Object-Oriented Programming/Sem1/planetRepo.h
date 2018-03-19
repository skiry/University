#pragma once
#include "planet.h"

typedef struct {
	Planet* vect[100];
	int length;
} PlanetRepo;

PlanetRepo* createRepo();

void destroyRepo(PlanetRepo* repo);

void addPlanet(PlanetRepo* repo, Planet* p);

void print_planets(PlanetRepo* repo);