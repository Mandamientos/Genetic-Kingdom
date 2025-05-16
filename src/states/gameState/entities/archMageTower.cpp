#include "archMageTower.hpp"
#include <algorithm>
#include <vector>
#include <memory>
#include <cmath>

archMageTower::archMageTower(const sf::Texture& texture, const std::pair<int, int>& pos, towerUpgrade& stats, TileMap &map)
    : tower(pos, stats) {
        spriteTowerAnimated.setTexture(texture, 32, 32, 4, 0.2f, 0);
        spriteTowerAnimated.setPosition(
            sf::Vector2f(pos.first * 35.f - 20.f, pos.second * 35.f - 43.f)
        );
        spriteTowerAnimated.setDrawSize(sf::Vector2f(80.f, 80.f));
        spriteTowerAnimated.setDirection(false);

        sf::Vector2f posSprite = spriteTowerAnimated.getPosition();

        specialAttackBackgroud.setPosition(sf::Vector2f(posSprite.x + 22.5f, posSprite.y + 80.f));
        specialAttackForegroud.setPosition(sf::Vector2f(posSprite.x + 22.5f, posSprite.y + 80.f));

        setAnimState(TowerAnimationState::Idle);
        setRange(3);
        setAttackSpeed(1.2f);
        setSpecialAbilityCooldown(5.f);
        calculateAreaOfEffect(26, 19);
        setSoundEffect("assets/sfx/magic1.wav");
        setAttackType("artillery");

        mapRef = &map;
}

void archMageTower::specialAttack() {
    if (specialAttackClock.getElapsedTime().asSeconds() >= getSpecialAbilityCooldown() && specialAttackClock.isRunning()) {
        specialAttackClock.restart();
        std::vector<std::pair<int, int>> aoe = getAreaOfEffect();
        for(const auto& tile : aoe) {
            int x = tile.first;
            int y = tile.second;

            auto enemies = mapRef->getEnemiesOnTile(x, y);
            for(Enemy* enemy : enemies ) {
                if(!enemy->isDead()) {
                    enemy->takeDamage(stats.getDamage()*3.f, "artillery");
                }
            }
        }
    } else {
        specialAttackForegroud.setSize(sf::Vector2f(30.f * specialAttackClock.getElapsedTime().asSeconds()/getSpecialAbilityCooldown(), 5.f));
    }
}

