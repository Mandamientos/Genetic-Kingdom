#include "Mercenary.hpp"
#include <cmath>

Mercenary::Mercenary(const sf::Texture& texture)
    : Enemy(180.f, 180.f, 0.6f, 0.2f, 0.6f) {
    sprite.emplace(texture);
    sprite->setScale(sf::Vector2f(0.5f, 0.5f));
    sprite->setPosition(sf::Vector2f(0.f, 0.f));
}

void Mercenary::update(float deltaTime) {
    if (sprite && !path.empty()) {
        sf::Vector2f currentPos = sprite->getPosition();
        sf::Vector2f targetPos(path[0].x * 25.f, path[0].y * 25.f);
        sf::Vector2f direction = targetPos - currentPos;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance < speed * deltaTime) {
            gridPosition = path[0];
            path.erase(path.begin());
            sprite->setPosition(targetPos);
        } else {
            direction /= distance;
            sprite->move(direction * speed * deltaTime);
        }
    }
}

void Mercenary::draw(sf::RenderWindow& window) {
    if (sprite) window.draw(*sprite);
}
