#include "castle.hpp"
#include <iostream>

castle::castle() : healthAmount(font) {
    if(!castleTexture.loadFromFile("assets/sprites/castle.gif")) {
        std::cout << "Error while loading..." << std::endl;
    }

    if(!font.openFromFile("assets/fonts/PERRYGOT.TTF")) {
        std::cout << "Error while loading..." << std::endl;
    }

    health = 1000;
    maxHealth = health;

    castleSprite.setTexture(castleTexture, 63, 72, 1, 5.f, 0);
    castleSprite.setScale(sf::Vector2f(3.f, 3.f));
    castleSprite.setPosition(sf::Vector2f(320.f, 70.f));

    healthBarBackground.setSize(sf::Vector2f(170.f, 20.f));
    healthBarBackground.setFillColor(sf::Color(50, 50, 50, 200));
    healthBarBackground.setPosition(sf::Vector2f(969.f, 450.f));

    healthBarForeground.setSize(sf::Vector2f(170.f, 20.f));
    healthBarForeground.setFillColor(sf::Color(255, 0, 0, 200));
    healthBarForeground.setPosition(sf::Vector2f(969.f, 450.f));

    healthAmount.setString(std::to_string(health));
    healthAmount.setFillColor(sf::Color::Red);
    healthAmount.setOutlineColor(sf::Color::White);
    healthAmount.setOutlineThickness(2);
    healthAmount.setPosition(sf::Vector2f(1010.f, 500.f));
}

void castle::receiveDmg(int amount) {
    health -= amount;
    healthBarForeground.setSize(sf::Vector2f(170.f * health/maxHealth, 20.f));
    healthAmount.setString(std::to_string(health));
}

void castle::update(float deltaTime) {
    castleSprite.update(deltaTime);
}

void castle::render(sf::RenderWindow& window) {
    window.draw(castleSprite);
    window.draw(healthBarBackground);
    window.draw(healthBarForeground);
    window.draw(healthAmount);
}