#pragma once
#include "../World/World.h"
#include <SFML/Graphics.hpp>
#include <string>

class WorldWindow {
public:
    WorldWindow(int width, int height);
    void renderWorld(const World& world);
    void run(World& world);
private:
    int windowWidth;
    int windowHeight;
    int cellSize;
    sf::RenderWindow window;
    std::string selectedInfo;
};
