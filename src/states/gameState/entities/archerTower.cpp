#include "archerTower.hpp"
#include <algorithm>
#include <vector>
#include <memory>
#include <cmath>

archerTower::archerTower(const sf::Texture& texture, const std::pair<int, int>& pos, towerUpgrade& stats, TileMap &map)
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
        setRange(5);
        setAttackSpeed(0.5f);
        setSpecialAbilityCooldown(20.f);
        calculateAreaOfEffect(26, 19);
        setSoundEffect("assets/sfx/shoot.ogg");
        setAttackType("arrow");

        mapRef = &map;
}

void archerTower::specialAttack() {
    if (specialAttackClock.getElapsedTime().asSeconds() >= getSpecialAbilityCooldown() && specialAttackClock.isRunning()) {
        specialAttackClock.restart();
        specialAttackClock.stop();

        setAttackSpeed(0.2f);

        specialAttackAux.restart();
    } else {
        specialAttackForegroud.setSize(sf::Vector2f(30.f * specialAttackClock.getElapsedTime().asSeconds()/getSpecialAbilityCooldown(), 5.f));
    }

    if(!specialAttackClock.isRunning()) {
        if(specialAttackAux.getElapsedTime().asSeconds() >= 5.f) {
            setAttackSpeed(0.5f);
            specialAttackClock.start();
        }
    }
    
}

