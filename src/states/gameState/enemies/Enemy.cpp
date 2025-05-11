#include "Enemy.hpp"
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

bool Enemy::isDead() const {
    return health <= 0;
}

sf::Vector2i Enemy::getPosition() const {
    return gridPosition;
}

void Enemy::setPath(const std::vector<sf::Vector2i>& newPath) {
    std::cout << "setPath() llamado. Primer punto: " << newPath[0].x << ", " << newPath[0].y << std::endl;
    path = newPath;
}
