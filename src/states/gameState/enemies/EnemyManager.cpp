#include "EnemyManager.hpp"
#include <algorithm>

void EnemyManager::startWave(int count, EnemyType type,
                             const sf::Texture& ogreTex,
                             const sf::Texture& darkElfTex,
                             const sf::Texture& harpyTex,
                             const sf::Texture& mercTex) {
    spawned = 0;
    enemiesToSpawn = count;
    currentType = type;
    waveClock.restart();

    ogreTexture = &ogreTex;
    darkElfTexture = &darkElfTex;
    harpyTexture = &harpyTex;
    mercenaryTexture = &mercTex;
}

void EnemyManager::updateWave(float dt, const std::vector<sf::Vector2i>& path, TileMap& map) {
    if (spawned < enemiesToSpawn && waveClock.getElapsedTime().asSeconds() > spawnInterval) {
        std::shared_ptr<Enemy> enemy;

        switch (currentType) {
            case EnemyType::Ogre:
                enemy = std::make_shared<Ogre>(*ogreTexture);
                break;
            case EnemyType::DarkElf:
                enemy = std::make_shared<DarkElf>(*darkElfTexture);
                break;
            case EnemyType::Harpy:
                enemy = std::make_shared<Harpy>(*harpyTexture);
                break;
            case EnemyType::Mercenary:
                enemy = std::make_shared<Mercenary>(*mercenaryTexture);
                break;
        }

        enemy->setPath(path);
        enemies.push_back(enemy);
        spawned++;
        waveClock.restart();
    }

    updateAll(dt, map);
}

void EnemyManager::updateAll(float dt, TileMap& map) {
    for (auto& e : enemies) {
        sf::Vector2i last = e->getLastGridPosition();
        e->update(dt);

        sf::Vector2i current = e->getPosition();

        if (current != last) {
            map.removeEnemyFromTile(last.x, last.y, e.get());
            map.addEnemyToTile(current.x, current.y, e.get());
            e->setLastGridPosition(current);
        }
    }
}

void EnemyManager::drawAll(sf::RenderWindow& window) {
    for (auto& e : enemies) {
        e->draw(window);
    }
}

std::vector<std::shared_ptr<Enemy>>& EnemyManager::getEnemies() {
    return enemies;
}
