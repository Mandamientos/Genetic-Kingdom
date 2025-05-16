#pragma once
#include "tower.hpp"
#include "animateSprite.hpp"

class mageTower : public tower {
    private:
        sf::Texture texture;
        sf::Clock specialAttackAux;

    public:
        mageTower(const sf::Texture& texture, const std::pair<int, int>& pos, towerUpgrade& stats, TileMap &map);
        void specialAttack() override;
};