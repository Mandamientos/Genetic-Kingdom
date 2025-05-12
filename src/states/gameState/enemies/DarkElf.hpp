#pragma once
#include "Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <optional>

class DarkElf : public Enemy {
public:
    DarkElf(const sf::Texture& texture);
    void draw(sf::RenderWindow& window) override;
};
