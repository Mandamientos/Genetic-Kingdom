#pragma once
#include "Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <optional>

class Harpy : public Enemy {
public:
    Harpy(const sf::Texture& texture);
    void draw(sf::RenderWindow& window) override;
};
