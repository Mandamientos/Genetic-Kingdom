#pragma once
#include "tilemap.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class towerType {
    ARCHER,
    MAGE,
    ARCHMAGE
};

enum class TowerAnimationState {
    Idle,
    Attacking
};

class towerUpgrade {
    private:
        int dmg;
        int level;
        int cost;
        int upgradeCost;
        towerType type;
    
    public:
        towerUpgrade(int damage, int lvl, int cost, towerType type);
        void upgrade();
        int getDamage() const;
        int getLevel() const { return level; };
        int getCost() const { return cost; }
        void setDamage(int damage);
        void setCost(int cost);
        void setLevel(int lvl);
        int getUpgradeCost() { return upgradeCost; }
};

class tower {
    private:
        int range;
        float attackSpeed;
        float specialAbilityCooldown;
        std::string attackType;
        std::pair<int, int> position;
        std::vector<std::pair<int, int>> areaOfEffect;
        TowerAnimationState animState;
        sf::SoundBuffer sfxBuffer;
        std::unique_ptr<sf::Sound> soundEffect;
    
    public:
        tower(const std::pair<int, int>& pos, towerUpgrade& stats);
        virtual ~tower() = default;
        animateSprite spriteTowerAnimated;
        Enemy* target = nullptr;
        towerUpgrade& stats;
        TileMap *mapRef;
        sf::Clock attackClock;
        sf::Clock specialAttackClock;
        sf::Clock animationClock;
        sf::RectangleShape specialAttackBackgroud, specialAttackForegroud;
        bool waitAnimToEnd;

        void update(float deltaTime, TileMap& map);
        void render(sf::RenderWindow& window);
        virtual void specialAttack() = 0;
        void calculateAreaOfEffect(int mapWidth, int mapHeight);

        void attackEnemy(TileMap& map);

        void setPosition(int x, int y) {
            position.first = x;
            position.second = y;
        }
        void setRange(int r) { range = r; };
        void setAttackSpeed(float speed) { attackSpeed = speed; };
        void setSpecialAbilityCooldown(float cooldown) { specialAbilityCooldown = cooldown; };
        void setAnimState(TowerAnimationState state) { animState = state; }
        void setAttackType(std::string type) { attackType = type; }
        void setSoundEffect(std::string route);

        int getRange() const { return range; };
        float getAttackSpeed() const { return attackSpeed; };
        float getSpecialAbilityCooldown() const { return specialAbilityCooldown; };
        const std::vector<std::pair<int, int>>& getAreaOfEffect() const { return areaOfEffect; };
        TowerAnimationState getAnimState() { return animState; }
        std::string getAttackType() { return attackType; }

        std::pair<int, int> getPosition() const;
};