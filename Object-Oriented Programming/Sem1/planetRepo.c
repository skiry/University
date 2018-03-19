#include "planetRepo.h"
#include <stdlib.h>
#include <stdio.h>

PlanetRepo* createRepo() {

	PlanetRepo* planets = (PlanetRepo*)malloc(sizeof(PlanetRepo));
	planets -> length = 0;
	return planets;
}

void destroyRepo(PlanetRepo* repo) {

	for (int i = 0; i < repo -> length; i++)
		destroy_planet(repo -> vect[i]);

	free(repo);
}

void addPlanet(PlanetRepo* repo, Planet* p) {

	repo -> vect[(repo -> length)++] = p;
}

void print_planets(PlanetRepo* repo) {

	for (int i = 0; i < repo -> length; i++)
		printf("Planet %d is %s\n", i + 1, get_name(repo -> vect[i]));
	}