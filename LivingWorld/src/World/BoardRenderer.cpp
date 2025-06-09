#include "BoardRenderer.h"
#include "World.h"
#include "../Abstractions/Organism.h"
#include <sstream>
#include <vector>

std::string BoardRenderer::render(World& world) {
    int worldX = world.getWorldX();
    int worldY = world.getWorldY();
    char separator = '.';
    std::vector<std::vector<char>> board(worldY, std::vector<char>(worldX, separator));
    const auto& organisms = world.getAllOrganisms();
    for (const auto& org : organisms) {
        int x = org->getPosition().getX();
        int y = org->getPosition().getY();
        char symbol = '?';
        std::string species = org->getSpecies();
        if (species == "S") symbol = 'S';
        else if (species == "W") symbol = 'W';
        else if (species == "D") symbol = 'D';
        else if (species == "T") symbol = 'T';
        else if (species == "P") symbol = 'P';
        board[y][x] = symbol;
    }
    std::ostringstream oss;
    for (int y = 0; y < worldY; ++y) {
        for (int x = 0; x < worldX; ++x) {
            oss << board[y][x] << ' ';
        }
        oss << '\n';
    }
    return oss.str();
}

