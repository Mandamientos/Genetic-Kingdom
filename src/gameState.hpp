#pragma once
#include <SFML/Graphics.hpp>

class gameState {
public:
    virtual void handleEvent(sf::RenderWindow& window, sf::Event& event) = 0;
    virtual void update(sf::RenderWindow& window) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual ~gameState() = default;
};