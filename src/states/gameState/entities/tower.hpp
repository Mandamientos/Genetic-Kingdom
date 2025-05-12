#pragma once
#include "tilemap.hpp"
#include <SFML/Graphics.hpp>

enum class towerType {
    ARCHER,
    MAGE,
    ARCHMAGE
};

class towerUpgrade {
    private:
        int dmg;
        int level;
        int cost;
        towerType type;
    
    public:
        towerUpgrade(int damage, int lvl, int cost, towerType type);
        int getDamage() const;
        int getLevel() const;
        int getCost() const;
        void setDamage(int damage);
        void setCost(int cost);
        void setLevel(int lvl);
};

class tower {
    private:
        int range;
        float attackSpeed;
        float specialAbilityCooldown;
        std::pair<int, int> position;
        std::vector<std::pair<int, int>> areaOfEffect;
    
    public:
        tower(const std::pair<int, int>& pos);
        virtual ~tower() = default;

        virtual void update(float deltaTime, TileMap& map) = 0;
        virtual void render(sf::RenderWindow& window) = 0;
        void calculateAreaOfEffect(int mapWidth, int mapHeight);

        virtual void attackEnemy(TileMap& map) = 0;

        void setPosition(int x, int y) {
            position.first = x;
            position.second = y;
        }
        void setRange(int r) { range = r; };
        void setAttackSpeed(float speed) { attackSpeed = speed; };
        void setSpecialAbilityCooldown(float cooldown) { specialAbilityCooldown = cooldown; };

        int getRange() const { return range; };
        float getAttackSpeed() const { return attackSpeed; };
        float getSpecialAbilityCooldown() const { return specialAbilityCooldown; };
        const std::vector<std::pair<int, int>>& getAreaOfEffect() const { return areaOfEffect; };

        std::pair<int, int> getPosition() const;
};