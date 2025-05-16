#include "tower.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <cmath>

tower::tower(const std::pair<int, int>& pos, towerUpgrade& stats) : position(pos), stats(stats) {
    specialAttackBackgroud.setSize(sf::Vector2f(30.f, 5.f));
    specialAttackBackgroud.setFillColor(sf::Color(50, 50, 50, 200));

    specialAttackForegroud.setSize(sf::Vector2f(30.f, 5.f));
    specialAttackForegroud.setFillColor(sf::Color(70, 130, 180, 200));
}

std::pair<int, int> tower::getPosition() const {
    return this->position;
}

void tower::calculateAreaOfEffect(int mapWidth, int mapHeight) {
    areaOfEffect.clear();
    int range = getRange();
    for (int i = -range; i <= range; ++i) {
        for (int j = -range; j <= range; ++j) {
            if (i * i + j * j <= range * range) {
                int x = this->getPosition().first + i;
                int y = this->getPosition().second + j;

                if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) {
                    areaOfEffect.emplace_back(x, y);
                }
            }
        }
    }
}

void tower::attackEnemy(TileMap& map) {
    if(target && !target->isDead()) {
        auto enemyPos = target->getPosition();
        std::pair<int, int> targetTile = {
            static_cast<int>(enemyPos.x),
            static_cast<int>(enemyPos.y)
        };

        std::pair<int, int> enemyTile = { target->getPosition().x, target->getPosition().y };
        if (std::find(getAreaOfEffect().begin(), getAreaOfEffect().end(), enemyTile) != getAreaOfEffect().end()) {
            bool isEnemyOnRight = enemyPos.x > this->getPosition().first;
            spriteTowerAnimated.setDirection(isEnemyOnRight);
            if(attackClock.getElapsedTime().asSeconds() >= getAttackSpeed()) {
                target->takeDamage(stats.getDamage(), getAttackType());
                attackClock.restart();
                animationClock.restart();
                waitAnimToEnd = true;
                soundEffect->play();
                spriteTowerAnimated.setFrameTime(getAttackSpeed() / 11.f);
                if (getAnimState() != TowerAnimationState::Attacking) {
                    spriteTowerAnimated.setRow(3);
                    spriteTowerAnimated.setFrameCount(11);
                    spriteTowerAnimated.setFrameTime(getAttackSpeed() / 11.f);
                    setAnimState(TowerAnimationState::Attacking);
                }
            }
        } else {
            target = nullptr;
        }
    } else {
        std::vector<Enemy*> enemiesInRange;

        for (int i = 0; i < getAreaOfEffect().size(); ++i) {
            auto enemies = map.getEnemiesOnTile(getAreaOfEffect()[i].first, getAreaOfEffect()[i].second);
            for (Enemy* enemy : enemies) {
                if (!enemy->isDead()) {
                    enemiesInRange.push_back(enemy);
                }
            }   
        }

        if(!enemiesInRange.empty()) {
            Enemy* closestToGoal = enemiesInRange[0];
            int minDistance = closestToGoal->getRemainingSteps();

            for(Enemy* enemy : enemiesInRange) {
                int distance = enemy->getRemainingSteps();
                if (distance < minDistance) {
                    minDistance = distance;
                    closestToGoal = enemy;
                }
            }

            target = closestToGoal;
        } else {
            target = nullptr;
        }
    }
}

void tower::setSoundEffect(std::string route) {
    if(!sfxBuffer.loadFromFile(route)) {
        std::cerr << "Error loading sfx.." << std::endl;
    }

    soundEffect = std::make_unique<sf::Sound>(sfxBuffer);
    soundEffect->setBuffer(sfxBuffer);
    soundEffect->setVolume(25);
}

void tower::update(float deltaTime, TileMap& map) {
    spriteTowerAnimated.update(deltaTime);

    attackEnemy(map);
    specialAttack();

    if (!target && getAnimState() == TowerAnimationState::Attacking) {
        if(waitAnimToEnd && animationClock.getElapsedTime().asSeconds() >= getAttackSpeed()) {
            spriteTowerAnimated.setRow(0);
            spriteTowerAnimated.setFrameCount(4);
            spriteTowerAnimated.setFrameTime(0.2f);
            setAnimState(TowerAnimationState::Idle);
            spriteTowerAnimated.setDirection(false);
            waitAnimToEnd = false;
        }
    }

}

void tower::render(sf::RenderWindow& window) {
    window.draw(spriteTowerAnimated);
    window.draw(specialAttackBackgroud);
    window.draw(specialAttackForegroud);
}


towerUpgrade::towerUpgrade(int damage, int lvl, int cost, towerType type) : dmg(damage), level(lvl), cost(cost), type(type) {
    this->upgradeCost = this->cost * 2;
}

int towerUpgrade::getDamage() const {
    return dmg;
}

void towerUpgrade::upgrade() {
    if (level <= 3) {
        level += 1;
        dmg *= 2;
        upgradeCost *= 2;
    }
}