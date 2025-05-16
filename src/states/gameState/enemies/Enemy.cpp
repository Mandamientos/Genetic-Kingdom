#include "Enemy.hpp"
#include "tilemap.hpp"
#include "aStar.hpp"
#include <cmath>
#include <iostream>

Enemy::Enemy(float h, float s, float ra, float rm, float rt)
    : health(h), speed(s), resistArrow(ra), resistMagic(rm), resistArtillery(rt), gridPosition(0, 0){
    healthBarBackground.setSize(sf::Vector2f(35.f, 5.f));
    healthBarBackground.setFillColor(sf::Color(50, 50, 50, 200));

    healthBarForeground.setSize(sf::Vector2f(35.f, 5.f));
    healthBarForeground.setFillColor(sf::Color(255, 0, 0, 200));

    this->maxHealth = h;
    }

void Enemy::takeDamage(float amount, const std::string& damageType) {
    float effectiveDamage = amount;

    if (damageType == "arrow") effectiveDamage *= (1.0f - resistArrow);
    else if (damageType == "magic") effectiveDamage *= (1.0f - resistMagic);
    else if (damageType == "artillery") effectiveDamage *= (1.0f - resistArtillery);
    health -= effectiveDamage;

    float ratio = health / maxHealth;
    healthBarForeground.setSize(sf::Vector2f(40.f * ratio, 5.f));
}   

void Enemy::update(float deltaTime, TileMap& map, castle& castle) {
    if (sprite) {
        sf::Vector2f currentPos = sprite->getPosition();
        currentPos.y -= 10.f;
        healthBarBackground.setPosition(currentPos);
        healthBarForeground.setPosition(currentPos);
    }

    if(!path.empty()) {
        auto mapGrid = map.getGrid();
        auto nextTile = path[0];
        if(!map.getGrid()[nextTile.y][nextTile.x].isWalkable) {
            AStarPathfinder pathfinder;
            std::pair<int, int> goal = map.getGoal();
            std::pair<int, int> start = {gridPosition.x, gridPosition.y};
            auto newPath = pathfinder.findPath(map, start, goal);
            if (!newPath.empty()) {
                path.clear();
                for (const auto& p : newPath) {
                    path.push_back(sf::Vector2i(p.first, p.second));
                }
                gridPosition = path[0];
                lastGridPosition = gridPosition;
            } else {
                std::cout << "No valid path found!" << std::endl;
            }
        }
    }

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
    } else {
        castle.receiveDmg(health);
        health = 0;
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
