#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "genetics/EnemyGenome.hpp"

class Enemy {
protected:
    std::optional<sf::Sprite> sprite;
    float health;
    float speed;
    float resistArrow;
    float resistMagic;
    float resistArtillery;
    sf::Vector2f scale = sf::Vector2f(1.f, 1.f); 
    sf::Vector2i gridPosition;
    sf::Vector2i lastGridPosition;
    std::vector<sf::Vector2i> path;
    EnemyGenome genome;

public:
    Enemy(float h, float s, float ra, float rm, float rt);
    virtual ~Enemy() = default;

    void update(float deltaTime);
    virtual void draw(sf::RenderWindow& window) = 0;

    void takeDamage(float amount, const std::string& damageType);

    bool isDead() const;
    sf::Vector2i getPosition() const;
    void setPath(const std::vector<sf::Vector2i>& newPath);

    sf::Vector2i getLastGridPosition() const { return lastGridPosition; }
    void setLastGridPosition(const sf::Vector2i& pos) { lastGridPosition = pos; }
    virtual void applyGenome(const EnemyGenome& g) {
        genome = g;
        health = g.health;
        speed = g.speed;
        resistArrow = g.resistArrow;
        resistMagic = g.resistMagic;
        resistArtillery = g.resistArtillery;
    }

    EnemyGenome& getGenome() { return genome; }
};
