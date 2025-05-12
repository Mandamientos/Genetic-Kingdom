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
    sf::Texture playerGoldTexture, ogreTexture, darkElfTexture, harpyTexture, mercenaryTexture;
    sf::Texture archerTowerTexture, archMageTowerTexture, mageTowerTexture;
    animateSprite goldAnimated, archerTowerAnimated, mageTowerAnimated, archMageTowerAnimated;
    EnemyManager enemyManager;
    std::vector<sf::Vector2i> wavePath;
    AStarPathfinder pathfinder;
    std::vector<std::pair<int, int>> path;
    bool pathPrinted = false;
    sf::Font fontP;
    sf::Text textGold, textArcherTower, textArchMageTower, textMageTower;
    sf::RectangleShape archerTowerButton, mageTowerButton, archMageTowerButton;

    bool waveStarted = false;
    int currentWave = 0;

};
