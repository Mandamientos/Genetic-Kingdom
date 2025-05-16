#pragma once
#include <SFML/Graphics.hpp>
#include "tilemap.hpp"
#include "tower.hpp"
#include "castle.hpp"

class Player {
    public:
        Player(sf::Text& goldText);

        int getGold() const;
        void addGold(int amount);
        bool spendGold(int amount);

        void castleUpdate(float dt) { playerCastle->update(dt); }
        void castleRender(sf::RenderWindow& window) { playerCastle->render(window); }

        castle* getCastle() { return playerCastle.get(); }

        std::vector<std::unique_ptr<towerUpgrade>> upgrades;
        std::vector<std::unique_ptr<tower>> towers;

        sf::Text& goldText;

        towerType selectedTowerType;
        bool isCardSelected = false;

        std::vector<std::pair<int, int>> areaOfEffect;
    
    private:
        int gold = 9999;
        std::unique_ptr<castle> playerCastle;
        void updateGold(int amount);
};