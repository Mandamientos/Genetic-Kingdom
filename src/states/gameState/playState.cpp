#include "playState.hpp"
#include "enemies/EnemyManager.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

playState::playState(gameStateManager& manager) : manager(manager), map(26, 19) {
    map.setStart(0, 0);
    map.setGoal(25, 9);
    

    srand(static_cast<unsigned>(time(nullptr)));

    if (!ogreTexture.loadFromFile("assets/sprites/ogre.png")) {
        std::cerr << "Error loading ogre.png" << std::endl;
    }
    if (!darkElfTexture.loadFromFile("assets/sprites/darkelf.png")) {
        std::cerr << "Error loading darkelf.png" << std::endl;
    }
    if (!harpyTexture.loadFromFile("assets/sprites/harpy.png")) {
        std::cerr << "Error loading harpy.png" << std::endl;
    }
    if (!mercenaryTexture.loadFromFile("assets/sprites/mercenary.png")) {
        std::cerr << "Error loading mercenary.png" << std::endl;
    }

    player = Player();

    if (!playerGoldTexture.loadFromFile("assets/sprites/coin.png")) {
        std::cerr << "Error loading coin.png" << std::endl;
        return;
    } else {
        goldAnimated.setTexture(playerGoldTexture, 16, 16, 15, 0.1f);
    }
}

void playState::handleEvent(sf::RenderWindow& window, sf::Event& event) {
    if (event.is<sf::Event::Closed>()) {
        window.close();
    }
}

void playState::update(sf::RenderWindow& window) {
    static sf::Clock clock;


    if (!pathPrinted) {
        path = pathfinder.findPath(map, map.getStart(), map.getGoal()); 
        
        std::cout << "Ruta encontrada:\n";
        for (const auto& pos : path) {
            std::cout << "(" << pos.first << ", " << pos.second << ")\n";
        }
        wavePath.clear();
        for (const auto& p : path) {
            wavePath.push_back(sf::Vector2i(p.first, p.second));
        }
    
        pathPrinted = true;
    }
    
    

    float deltaTime = clock.restart().asSeconds();

    goldAnimated.update(deltaTime);

    if (!waveStarted) {
        int randomIndex = rand() % 4;
        EnemyType type = static_cast<EnemyType>(randomIndex);
        int cantidad = 3 + (rand() % 8); 
        std::cout << "Oleada aleatoria #" << currentWave + 1 << ": ";
        switch (type) {
            case EnemyType::Ogre: std::cout << "Ogro"; break;
            case EnemyType::DarkElf: std::cout << "Elfo Oscuro"; break;
            case EnemyType::Harpy: std::cout << "Harpía"; break;
            case EnemyType::Mercenary: std::cout << "Mercenario"; break;
        }
        std::cout << " x" << cantidad << std::endl;

        enemyManager.startWave(cantidad, type,
            ogreTexture, darkElfTexture, harpyTexture, mercenaryTexture);

        waveStarted = true;
        currentWave++;
    }

    enemyManager.updateWave(deltaTime, wavePath);

    // TEST: reiniciar oleada cada 10 segundos
    //static sf::Clock testWaveClock;
    //if (testWaveClock.getElapsedTime().asSeconds() > 10.f) {
    //    waveStarted = false;
    //    testWaveClock.restart();
    //}
}


void playState::render(sf::RenderWindow& window) {
    window.clear(sf::Color(0x57, 0x80, 0xD3));

    const auto& tiles = map.getGrid();

    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            sf::RectangleShape tileShape(sf::Vector2f(25.f, 25.f));
            tileShape.setPosition(sf::Vector2(tile.x * 25.f, tile.y * 25.f));

            switch (tile.type) {
                case TileType::EMPTY:
                    tileShape.setFillColor(sf::Color(0x57, 0xA4, 0xD3));
                    break;
                case TileType::START:
                    tileShape.setFillColor(sf::Color::Green);
                    break;
                case TileType::GOAL:
                    tileShape.setFillColor(sf::Color::Red);
                    break;
                case TileType::TOWER:
                    tileShape.setFillColor(sf::Color::Blue);
                    break;
            }

            tileShape.setOutlineThickness(1);
            tileShape.setOutlineColor(sf::Color::White);
            window.draw(tileShape);
        }
    }

    window.draw(goldAnimated);
    enemyManager.drawAll(window);
    window.display();
}
