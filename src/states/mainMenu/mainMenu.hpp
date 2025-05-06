#pragma once
#include <SFML/Graphics.hpp>
#include "gameState.hpp"
#include "gameStateManager.hpp"

class mainMenu : public gameState {
    public:
        mainMenu(gameStateManager& manager);
        void handleEvent(sf::RenderWindow& window, sf::Event& event) override;
        void update(sf::RenderWindow& window) override;
        void render(sf::RenderWindow& window) override;

    private:
        gameStateManager& manager;
        sf::Font font;
        sf::Text playText, quitText;
        sf::RectangleShape playButton, quitButton;
        sf::Texture logo;
        std::optional<sf::Sprite> logoSprite;
    };