#include "Mercenary.hpp"
#include <cmath>

Mercenary::Mercenary(const sf::Texture& texture)
    : Enemy(180.f, 65.1f, 0.6f, 0.2f, 0.6f) {
    sprite.emplace(texture);
    sprite->setScale(scale);
    sprite->setPosition(sf::Vector2f(0.f, 0.f));
}

void Mercenary::draw(sf::RenderWindow& window) {
    if (sprite) {
        window.draw(*sprite);
        window.draw(healthBarBackground);
        window.draw(healthBarForeground);
    }
}
