#include "tower.hpp"

tower::tower(const std::pair<int, int>& pos) : position(pos) {}

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

towerUpgrade::towerUpgrade(int damage, int lvl, int cost, towerType type) : dmg(damage), level(lvl), cost(cost), type(type) {}

int towerUpgrade::getDamage() const {
    return dmg;
}