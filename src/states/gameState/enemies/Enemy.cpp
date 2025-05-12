#include "Enemy.hpp"
#include <cmath>
#include <iostream>


Enemy::Enemy(float h, float s, float ra, float rm, float rt)
    : health(h), speed(s), resistArrow(ra), resistMagic(rm), resistArtillery(rt), gridPosition(0, 0) {}

void Enemy::takeDamage(float amount, const std::string& damageType) {
    float effectiveDamage = amount;

    if (damageType == "arrow") effectiveDamage *= (1.0f - resistArrow);
    else if (damageType == "magic") effectiveDamage *= (1.0f - resistMagic);
    else if (damageType == "artillery") effectiveDamage *= (1.0f - resistArtillery);

    health -= effectiveDamage;
}

void Enemy::update(float deltaTime) {
    if (sprite && !path.empty()) {
        sf::Vector2f currentPos = sprite->getPosition();
        sf::Vector2f targetPos(path[0].x * 35.f, path[0].y * 35.f);
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

bool Enemy::isDead() const {
    return health <= 0;
}

sf::Vector2i Enemy::getPosition() const {
    return gridPosition;
}

void Enemy::setPath(const std::vector<sf::Vector2i>& newPath) {
    path = newPath;
    if (!path.empty()) {
        gridPosition = path[0];
        lastGridPosition = gridPosition;
    }
}
