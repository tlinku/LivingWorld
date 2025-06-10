#include "WorldWindow.h"
#include <SFML/Graphics.hpp>
#include <map>

WorldWindow::WorldWindow(int width, int height)
    : windowWidth(width), windowHeight(height), cellSize(32), window(sf::VideoMode(width, height), "Living World") {}

void WorldWindow::renderWorld(const World& world) {
    window.clear(sf::Color::White);
    int worldX = world.getWorldX();
    int worldY = world.getWorldY();
    std::map<std::string, sf::Color> colorMap = {
        {"S", sf::Color::Green},
        {"W", sf::Color::Red},
        {"D", sf::Color::Yellow},
        {"T", sf::Color(128, 0, 128)},
        {"P", sf::Color::Blue}
    };
    for (const auto& org : world.getAllOrganisms()) {
        int x = org->getPosition().getX();
        int y = org->getPosition().getY();
        sf::RectangleShape rect(sf::Vector2f(cellSize - 2, cellSize - 2));
        rect.setPosition(x * cellSize + 1, y * cellSize + 1);
        auto it = colorMap.find(org->getSpecies());
        if (it != colorMap.end())
            rect.setFillColor(it->second);
        else
            rect.setFillColor(sf::Color::Black);
        window.draw(rect);
    }
    if (!selectedInfo.empty()) {
        sf::Font font;
        if (font.loadFromFile("/System/Library/Fonts/SFNSMono.ttf")) { // systemowy font na macOS
            sf::Text text(selectedInfo, font, 18);
            text.setFillColor(sf::Color::Black);
            text.setPosition(10, windowHeight - 40);
            window.draw(text);
        }
    }
    window.display();
}

void WorldWindow::run(World& world) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                world.makeTurn();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int mx = event.mouseButton.x / cellSize;
                int my = event.mouseButton.y / cellSize;
                bool found = false;
                for (const auto& org : world.getAllOrganisms()) {
                    if (org->getPosition().getX() == mx && org->getPosition().getY() == my) {
                        selectedInfo = "Species: " + org->getSpecies() + " ";
                        auto history = org->getAncestryHistory();
                        if (!history.empty()) {
                            selectedInfo += "Ancestor history: ";
                            for (const auto& h : history) {
                                selectedInfo += "[" + std::to_string(h.first) + ", " + std::to_string(h.second) + "] ";
                            }
                        } else {
                            selectedInfo += "1st gen";
                        }
                        found = true;
                        break;
                    }
                }
                if (!found) selectedInfo = "";
            }
        }
        renderWorld(world);
        sf::sleep(sf::milliseconds(50));
    }
}
