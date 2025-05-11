#pragma once
#include "tilemap.hpp"
#include "gameState.hpp"
#include "animateSprite.hpp"
#include "gameStateManager.hpp"
#include "player.hpp"
#include "enemies/EnemyManager.hpp"
#include "aStar.hpp" 
#include <vector>

class playState : public gameState {
public:
    playState(gameStateManager& manager);
    void handleEvent(sf::RenderWindow& window, sf::Event& event) override;
    void update(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

private:
    gameStateManager& manager;
    Player player;
    TileMap map;
    sf::Texture playerGoldTexture;
    animateSprite goldAnimated;
    EnemyManager enemyManager;
    std::vector<sf::Vector2i> wavePath;
    AStarPathfinder pathfinder;
    std::vector<std::pair<int, int>> path;
    bool pathPrinted = false;
    bool waveStarted = false;
    int currentWave = 0;
    
    sf::Texture ogreTexture;
    sf::Texture darkElfTexture;
    sf::Texture harpyTexture;
    sf::Texture mercenaryTexture;

};
