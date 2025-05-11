#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Enemy {
protected:
    float health;
    float speed;
    float resistArrow;
    float resistMagic;
    float resistArtillery;
    sf::Vector2i gridPosition;
    std::vector<sf::Vector2i> path;

public:
    Enemy(float h, float s, float ra, float rm, float rt);
    virtual ~Enemy() = default;

    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    void takeDamage(float amount, const std::string& damageType);
    bool isDead() const;
    sf::Vector2i getPosition() const;
    void setPath(const std::vector<sf::Vector2i>& newPath);
};
