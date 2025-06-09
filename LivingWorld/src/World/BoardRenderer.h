#pragma once
#include <string>
#include <vector>

class Organism;
class World;

class BoardRenderer {
public:
    static std::string render(World& world);
};
