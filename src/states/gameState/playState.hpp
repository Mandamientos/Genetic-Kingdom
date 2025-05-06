#pragma once
#include "tilemap.hpp"
#include "gameState.hpp"
#include "gameStateManager.hpp"

class playState : public gameState {
    public:
        playState(gameStateManager& manager);
        void handleEvent(sf::RenderWindow& window, sf::Event& event) override;
        void update(sf::RenderWindow& window) override;
        void render(sf::RenderWindow& window) override;
    
    private:
        gameStateManager& manager;
        TileMap map;
};