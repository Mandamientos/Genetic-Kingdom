#pragma once
#include "Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <optional>

class Ogre : public Enemy {
public:
    Ogre(const sf::Texture& texture);
    void draw(sf::RenderWindow& window) override;
};
