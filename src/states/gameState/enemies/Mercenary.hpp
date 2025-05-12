#pragma once
#include "Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <optional>

class Mercenary: public Enemy {
public:
    Mercenary(const sf::Texture& texture);
    void draw(sf::RenderWindow& window) override;
};
