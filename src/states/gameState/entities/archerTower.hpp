#pragma once
#include "tower.hpp"
#include "animateSprite.hpp"

class archerTower : public tower {
    private:
        sf::Texture texture;
        sf::Clock specialAttackAux;

    public:
        archerTower(const sf::Texture& texture, const std::pair<int, int>& pos, towerUpgrade& stats, TileMap &map);
        void specialAttack() override;
};