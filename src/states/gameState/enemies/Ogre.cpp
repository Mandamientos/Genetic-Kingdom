#include "Ogre.hpp"
#include <cmath>
#include <iostream>

Ogre::Ogre(const sf::Texture& texture)
    : Enemy(200.f, 35.f, 0.5f, 0.2f, 0.1f) {
    sprite.emplace(texture); 
    sprite->setScale(scale);
    sprite->setPosition(sf::Vector2f(0.f, 0.f));
}

void Ogre::draw(sf::RenderWindow& window) {
    if (sprite) {
        window.draw(*sprite);
        window.draw(healthBarBackground);
        window.draw(healthBarForeground);
    }
}