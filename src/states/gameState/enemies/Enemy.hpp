#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "castle.hpp"

class TileMap;

class Enemy {
protected:
    std::optional<sf::Sprite> sprite;
    float health;
    float maxHealth;
    float speed;
    float resistArrow;
    float resistMagic;
    float resistArtillery;
    sf::Vector2f scale = sf::Vector2f(1.f, 1.f); 
    sf::Vector2i gridPosition;
    sf::Vector2i lastGridPosition;
    std::vector<sf::Vector2i> path;
    sf::RectangleShape healthBarBackground;
    sf::RectangleShape healthBarForeground;


public:
    Enemy(float h, float s, float ra, float rm, float rt);
    virtual ~Enemy() = default;

    void update(float deltaTime, TileMap& map, castle& castle);
    virtual void draw(sf::RenderWindow& window) = 0;

    void takeDamage(float amount, const std::string& damageType);

    bool isDead() const;
    sf::Vector2i getPosition() const;
    void setPath(const std::vector<sf::Vector2i>& newPath);

    sf::Vector2i getLastGridPosition() const { return lastGridPosition; }
    void setLastGridPosition(const sf::Vector2i& pos) { lastGridPosition = pos; }
    
    int getRemainingSteps() const {return static_cast<int>(path.size()); }
    int getMaxHealth() const { return maxHealth; }

};
