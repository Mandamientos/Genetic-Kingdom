#pragma once
#include "tower.hpp"
#include "animateSprite.hpp"

class archerTower : public tower {
    private:
        animateSprite archerTowerAnimated;
        sf::Texture texture;
        sf::Clock attackClock;
        towerUpgrade& stats;
        Enemy* target = nullptr;

    public:
        archerTower(const sf::Texture& texture, const std::pair<int, int>& pos, towerUpgrade& stats);
        void update(float deltaTime, TileMap& map) override;
        void render(sf::RenderWindow& window) override;
        void attackEnemy(TileMap& map) override;
};