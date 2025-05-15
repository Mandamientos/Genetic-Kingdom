#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include "Ogre.hpp"
#include "DarkElf.hpp"
#include "Harpy.hpp"
#include "Mercenary.hpp"
#include "tilemap.hpp"
#include "EnemyType.hpp"
class EnemyManager {
private:
    std::vector<std::shared_ptr<Enemy>> enemies;
    sf::Clock waveClock;
    float spawnInterval = 1.0f;
    int enemiesToSpawn = 0;
    int spawned = 0;
    EnemyType currentType;

    const sf::Texture* ogreTexture = nullptr;
    const sf::Texture* darkElfTexture = nullptr;
    const sf::Texture* harpyTexture = nullptr;
    const sf::Texture* mercenaryTexture = nullptr;

public:
    void updateAll(float dt, TileMap& map);
    void drawAll(sf::RenderWindow& window);
    void startWaveFromGenomes(const std::vector<EnemyGenome>& genomes,
                   const sf::Texture& ogreTex,
                   const sf::Texture& darkElfTex,
                   const sf::Texture& harpyTex,
                   const sf::Texture& mercTex,
                   const std::vector<sf::Vector2i>& path);
    void updateWaveFromGenomes(float dt, const std::vector<sf::Vector2i>& path, TileMap& map);
    std::vector<std::shared_ptr<Enemy>>& getEnemies();
    std::vector<EnemyGenome> pendingGenomes;
    std::vector<sf::Vector2i> currentWavePath;

};
