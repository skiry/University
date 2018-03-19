#include "planet.h"
#include <stdio.h>
#include "planetRepo.h"

int main() {

	Planet* planet =  create_planet("Venus", "Liveable", 50.000);

	printf("The name of the first planet is %s\n", get_name(planet));
	
	PlanetRepo* repository = createRepo();
	addPlanet(repository, planet);

	Planet* mars = create_planet("Mars", "White", 20.000);
	addPlanet(repository, mars);

	printf("The second planet is %s\n", get_name(mars));
	printf("The length of repo is %d\n", repository -> length);

	Planet* mars2 = create_planet("Mars2", "White", 20.000);
	addPlanet(repository, mars2);

	print_planets(repository);
	//destroy_planet(mars);
	print_planets(repository);

	destroyRepo(repository);
	return 0;
}