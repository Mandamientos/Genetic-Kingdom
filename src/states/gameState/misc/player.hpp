#pragma once
#include <SFML/Graphics.hpp>
#include "tilemap.hpp"
#include "tower.hpp"

class Player {
    public:
        Player();

        int getGold() const;
        void addGold(int amount, sf::Text& textGold);
        bool spendGold(int amount, sf::Text& textGold);

        std::vector<std::unique_ptr<towerUpgrade>> upgrades;
        std::vector<std::unique_ptr<tower>> towers;

        towerType selectedTowerType;
        bool isCardSelected = false;

        std::vector<std::pair<int, int>> areaOfEffect;
    
    private:
        int gold = 100;
        void updateGold(int amount, sf::Text& textGold);
};