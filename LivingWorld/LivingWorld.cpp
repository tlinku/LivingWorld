#include <iostream>
#include "src/Abstractions/Position.h"
#include "src/World/World.h"
#include "src/Organisms/Sheep.h"
#include "src/Organisms/Wolf.h"
#include "src/Organisms/Dandelion.h"
#include "src/Organisms/Toadstool.h"
#include "src/World/WorldWindow.h"
#include <memory>

using namespace std;

int main()
{
    World world(30, 20); // większa mapa

    // Dodajemy "trawę" (Dandelion) w skupisku
    for (int i = 5; i < 10; ++i) {
        for (int j = 5; j < 8; ++j) {
            world.addOrganism(std::make_unique<Dandelion>(Position(i, j)));
        }
    }

    // Dodajemy owce blisko trawy
    world.addOrganism(std::make_unique<Sheep>(Position(6, 4)));
    world.addOrganism(std::make_unique<Sheep>(Position(7, 4)));
    world.addOrganism(std::make_unique<Sheep>(Position(8, 4)));
    world.addOrganism(std::make_unique<Sheep>(Position(5, 8)));
    world.addOrganism(std::make_unique<Sheep>(Position(9, 7)));
    world.addOrganism(std::make_unique<Sheep>(Position(8, 8)));

    // Dodajemy wilki daleko od owiec, ale w zasięgu dojścia
    world.addOrganism(std::make_unique<Wolf>(Position(25, 15)));
    world.addOrganism(std::make_unique<Wolf>(Position(22, 18)));
    world.addOrganism(std::make_unique<Wolf>(Position(28, 10)));

    // Dodajemy muchomory między trawą
    world.addOrganism(std::make_unique<Toadstool>(Position(7, 6)));
    world.addOrganism(std::make_unique<Toadstool>(Position(8, 5)));

    // Dodajemy pojedyncze trawy w innych miejscach
    world.addOrganism(std::make_unique<Dandelion>(Position(15, 2)));
    world.addOrganism(std::make_unique<Dandelion>(Position(20, 10)));

    // Dodajemy owcę "zagubioną" daleko od trawy
    world.addOrganism(std::make_unique<Sheep>(Position(2, 17)));

    WorldWindow window(960, 640); // większe okno
    window.run(world);

    return 0;
}
