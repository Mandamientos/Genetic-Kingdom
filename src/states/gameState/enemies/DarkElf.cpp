#include "DarkElf.hpp"
#include <cmath>

DarkElf::DarkElf(const sf::Texture& texture)
    : Enemy(100.f, 300.f, 0.2f, 0.7f, 0.4f) {
    sprite.emplace(texture);
    sprite->setScale(scale);
    sprite->setPosition(sf::Vector2f(0.f, 0.f));
}

void DarkElf::draw(sf::RenderWindow& window) {
    if (sprite) window.draw(*sprite);
}
