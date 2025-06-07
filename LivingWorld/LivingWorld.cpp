#include <iostream>
#include "src/Abstractions/Position.h"
#include "src/Abstractions/Organism.h"
#include "src/Abstractions/Plant.h"
#include "src/Abstractions/Animal.h"
#include "src/World/World.h"
#include "src/Organisms/Sheep.h"
#include "src/Organisms/Wolf.h"
#include "src/Organisms/Dandelion.h"
#include "src/Organisms/Toadstool.h"
#include <memory>
#include <vector>

using namespace std;

int main()
{
	World world(20, 20); // większa siatka

	// Dodajemy kilka owiec
	for (int i = 0; i < 6; ++i) {
		world.addOrganism(std::make_unique<Sheep>(Position(2 + i, 2 + i)));
	}

	// Dodajemy dwa wilki
	world.addOrganism(std::make_unique<Wolf>(Position(10, 10)));
	world.addOrganism(std::make_unique<Wolf>(Position(11, 10)));

	// Dodajemy kilka mniszków
	for (int i = 0; i < 1; i++) {
		world.addOrganism(std::make_unique<Dandelion>(Position(5 + i, 15 - i)));
	}

	// Dodajemy jednego muchomora
	world.addOrganism(std::make_unique<Toadstool>(Position(18, 18)));

	// Wyświetl stan świata
	cout << world.toString() << endl;

	// Symulacja 20 tur
	for (int t = 0; t < 20; ++t) {
		world.makeTurn();
		cout << "\nTura: " << (t + 1) << endl;
		cout << world.toString() << endl;
	}

	// Możesz dodać zapis/odczyt, itp.
	// world.writeWorld("world.txt");
	// world.readWorld("world.txt");

	return 0;
}
