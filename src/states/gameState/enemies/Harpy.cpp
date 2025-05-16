#include "Harpy.hpp"
#include <cmath>

Harpy::Harpy(const sf::Texture& texture)
    : Enemy(120.f, 50.f, 0.3f, 0.5f, 0.0f) {
    sprite.emplace(texture);
    sprite->setScale(scale);
    sprite->setPosition(sf::Vector2f(0.f, 0.f));
}

void Harpy::draw(sf::RenderWindow& window) {
    if (sprite) {
        window.draw(*sprite);
        window.draw(healthBarBackground);
        window.draw(healthBarForeground);
    }
}
