#include "Harpy.hpp"
#include <cmath>

Harpy::Harpy(const sf::Texture& texture)
    : Enemy(120.f, 220.f, 0.3f, 0.5f, 0.0f) {
    sprite.emplace(texture);
    sprite->setScale(sf::Vector2f(0.5f, 0.5f));
    sprite->setPosition(sf::Vector2f(0.f, 0.f));
}

void Harpy::update(float deltaTime) {
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

void Harpy::draw(sf::RenderWindow& window) {
    if (sprite) window.draw(*sprite);
}
