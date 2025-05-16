#pragma once
#include "animateSprite.hpp"

class castle {
    private:
        animateSprite castleSprite;
        sf::Texture castleTexture;
        sf::RectangleShape healthBarBackground, healthBarForeground;
        sf::Font font;
        sf::Text healthAmount;
        int health;
        int maxHealth;
    
    public:
        castle();
        int getHealth() { return health; }
        void receiveDmg(int amount);
        void update(float dt);
        void render(sf::RenderWindow& window);
};