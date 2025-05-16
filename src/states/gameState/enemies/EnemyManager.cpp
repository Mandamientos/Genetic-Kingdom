#include "EnemyManager.hpp"
#include <algorithm>

void EnemyManager::startWaveFromGenomes(
    const std::vector<EnemyGenome>& genomes,
    const sf::Texture& ogreTex,
    const sf::Texture& darkElfTex,
    const sf::Texture& harpyTex,
    const sf::Texture& mercTex,
    const std::vector<sf::Vector2i>& path
) {
    //enemies.clear();
    pendingGenomes = genomes;
    currentWavePath = path;
    waveClock.restart();

    ogreTexture = &ogreTex;
    darkElfTexture = &darkElfTex;
    harpyTexture = &harpyTex;
    mercenaryTexture = &mercTex;

    spawned = 0;
    enemiesToSpawn = genomes.size();
}

void EnemyManager::updateWaveFromGenomes(float dt, const std::vector<sf::Vector2i>& path, TileMap& map, castle& castle, Player& player) {
    if (!pendingGenomes.empty() && waveClock.getElapsedTime().asSeconds() > spawnInterval) {
        const EnemyGenome& genome = pendingGenomes.front();

        std::shared_ptr<Enemy> enemy;

        switch (genome.type) {
            case EnemyType::Ogre: enemy = std::make_shared<Ogre>(*ogreTexture); break;
            case EnemyType::DarkElf: enemy = std::make_shared<DarkElf>(*darkElfTexture); break;
            case EnemyType::Harpy: enemy = std::make_shared<Harpy>(*harpyTexture); break;
            case EnemyType::Mercenary: enemy = std::make_shared<Mercenary>(*mercenaryTexture); break;
        }

        if (enemy) {
            enemy->applyGenome(genome);
            enemy->setPath(currentWavePath);
            map.addEnemyToTile(currentWavePath[0].x, currentWavePath[0].y, enemy.get());
            enemies.push_back(enemy);
            spawned++;
        }

        pendingGenomes.erase(pendingGenomes.begin());
        waveClock.restart();
    }

    updateAll(dt, map, castle, player);
}

void EnemyManager::updateAll(float dt, TileMap& map, castle& castle, Player& player) {
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(), [&map, &player](const std::shared_ptr<Enemy>& e) { 
            if(e->isDead()) {
                sf::Vector2i last = e->getLastGridPosition();
                if(e->getLastGridPosition() != sf::Vector2i(25, 9)) { player.addGold(e->getMaxHealth()/6); }
                map.removeEnemyFromTile(last.x, last.y, e.get());
                std::cout << e->getMaxHealth() << std::endl;
                return true; 
            }
            return false;
        }),
        enemies.end());

    for (auto& e : enemies) {
        sf::Vector2i last = e->getLastGridPosition();
        e->update(dt, map, castle);

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

