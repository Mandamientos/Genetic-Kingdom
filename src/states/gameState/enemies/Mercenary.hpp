#pragma once
#include "Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <optional>

class Mercenary: public Enemy {
private:
    std::optional<sf::Sprite> sprite;

public:
    Mercenary(const sf::Texture& texture);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
};
