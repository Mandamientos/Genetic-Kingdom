#include "playState.hpp"
#include "towerFactory.hpp"
#include "enemies/EnemyManager.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>

void configureButton(sf::RectangleShape& button, const sf::Vector2f& size, const sf::Color& fillColor, const sf::Color& outlineColor, float outlineThickness, const sf::Vector2f& position) {
    button.setSize(size);
    button.setFillColor(fillColor);
    button.setOutlineThickness(outlineThickness);
    button.setOutlineColor(outlineColor);
    button.setPosition(position);
}

void configureText(sf::Text& text, const std::string& str, const sf::Font& font, unsigned int characterSize, const sf::Color& fillColor, const sf::Color& outlineColor, float outlineThickness, const sf::Vector2f& position) {
    text.setString(str);
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setFillColor(fillColor);
    text.setOutlineThickness(outlineThickness);
    text.setOutlineColor(outlineColor);
    text.setPosition(position);
}

void calculateAreaOfEffect(std::vector<std::pair<int, int>>& areaOfEffect, int range, const std::pair<int, int>& position, int mapWidth, int mapHeight) {
    areaOfEffect.clear();
    for (int i = -range; i <= range; ++i) {
        for (int j = -range; j <= range; ++j) {
            if (i * i + j * j <= range * range) {
                int x = position.first + i;
                int y = position.second + j;

                if (x >= 0 && x < mapWidth && y >= 0 && y < mapHeight) {
                    areaOfEffect.emplace_back(x, y);
                }
            }
        }
    }
}

playState::playState(gameStateManager& manager) : manager(manager), map(26, 19), textGold(fontP), textArcherTower(fontP), textArchMageTower(fontP), textMageTower(fontP), player(textGold), upgradeTextArcherTower(fontP), upgradeTextArchMageTower(fontP), upgradeTextMageTower(fontP) {
    map.setStart(0, 0);
    map.setGoal(25, 9);
    
    srand(static_cast<unsigned>(time(nullptr)));

    if (!castleTexture.loadFromFile("assets/sprites/castle.gif")) {
        std::cerr << "Error loading ogre.png" << std::endl;
    }
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

    if (!playerGoldTexture.loadFromFile("assets/sprites/coin.png")) {
        std::cerr << "Error loading coin.png" << std::endl;
        return;
    } else {
        goldAnimated.setTexture(playerGoldTexture, 16, 16, 15, 0.1f);
    }

    if (!archerTowerTexture.loadFromFile("assets/sprites/MiniArcherMan.png")) {
        std::cerr << "Error loading texture" << std::endl;
        return;
    } else {
        archerTowerAnimated.setTexture(archerTowerTexture, 32, 32, 4, 0.2f, 0);
    }

    if (!mageTowerTexture.loadFromFile("assets/sprites/MiniMage.png")) {
        std::cerr << "Error loading texture" << std::endl;
        return;
    } else {
        mageTowerAnimated.setTexture(mageTowerTexture, 32, 32, 4, 0.2f, 0);
    }

    if (!archMageTowerTexture.loadFromFile("assets/sprites/MiniArchMage.png")) {
        std::cerr << "Error loading texture" << std::endl;
        return;
    } else {
        archMageTowerAnimated.setTexture(archMageTowerTexture, 32, 32, 4, 0.2f, 0);
    }

    if (!fontP.openFromFile("assets/fonts/PERRYGOT.TTF")) {
        std::cerr << "Error loading font" << std::endl;
    }

    if(!bgBuffer.loadFromFile("assets/sfx/battle.mp3")) {
        std::cerr << "Error loading sfx..." << std::endl; 
    }

    bgTheme = std::make_unique<sf::Sound>(bgBuffer);
    bgTheme->play();
    bgTheme->setVolume(15);
    bgTheme->setLooping(true);

    goldAnimated.setDrawSize(sf::Vector2f(50.f, 50.f));
    goldAnimated.setPosition(sf::Vector2f(520.f, 775.f));
    
    archerTowerAnimated.setDrawSize(sf::Vector2f(125.f, 125.f));
    archerTowerAnimated.setPosition(sf::Vector2f(15.f, 650.f)); // Ajustar posición
    archerTowerAnimated.setDirection(false);
    configureButton(archerTowerButton, sf::Vector2f(150.f, 100.f), sf::Color(0x5D, 0x75, 0xA7), sf::Color::White, 2.f, sf::Vector2f(28.f, 695.f));
    configureText(textArcherTower, "100", fontP, 20, sf::Color::White, sf::Color::Black, 0.f, sf::Vector2f(120.f, 735.f));
    
    mageTowerAnimated.setDrawSize(sf::Vector2f(125.f, 125.f));
    mageTowerAnimated.setPosition(sf::Vector2f(175.f, 650.f)); // Ajustar posición
    mageTowerAnimated.setDirection(false);
    configureButton(mageTowerButton, sf::Vector2f(150.f, 100.f), sf::Color(0x5D, 0x75, 0xA7), sf::Color::White, 2.f, sf::Vector2f(190.f, 695.f));
    configureText(textMageTower, "200", fontP, 20, sf::Color::White, sf::Color::Black, 0.f, sf::Vector2f(270.f, 735.f));
    
    archMageTowerAnimated.setDrawSize(sf::Vector2f(125.f, 125.f));
    archMageTowerAnimated.setPosition(sf::Vector2f(335.f, 650.f)); // Ajustar posición
    archMageTowerAnimated.setDirection(false);
    configureButton(archMageTowerButton, sf::Vector2f(150.f, 100.f), sf::Color(0x5D, 0x75, 0xA7), sf::Color::White, 2.f, sf::Vector2f(352.f, 695.f));
    configureText(textArchMageTower, "300", fontP, 20, sf::Color::White, sf::Color::Black, 0.f, sf::Vector2f(430.f, 735.f));
    
    configureButton(archMageTowerButton, sf::Vector2f(150.f, 100.f), sf::Color(0x5D, 0x75, 0xA7), sf::Color::White, 2.f, sf::Vector2f(352.f, 695.f));

    player.upgrades.push_back(std::make_unique<towerUpgrade>(35, 1, 100, towerType::ARCHER));
    player.upgrades.push_back(std::make_unique<towerUpgrade>(50, 1, 200, towerType::MAGE));
    player.upgrades.push_back(std::make_unique<towerUpgrade>(90, 1, 300, towerType::ARCHMAGE));

    configureText(textGold, std::to_string(player.getGold()), fontP, 20, sf::Color(255, 215, 0), sf::Color::Black, 3.f, sf::Vector2f(575.f, 790.f)); 

    configureButton(upgradeArcherButton, sf::Vector2f(150.f, 50.f), sf::Color(0x5D, 0x75, 0xA7), sf::Color::White, 2.f, sf::Vector2f(28.f, 825.f));
    configureText(upgradeTextArcherTower, std::to_string(player.upgrades[0]->getUpgradeCost()), fontP, 20, sf::Color(255, 215, 0), sf::Color::Black, 3.f, sf::Vector2f(76.f, 840.f)); 

    configureButton(upgradeMageButton, sf::Vector2f(150.f, 50.f), sf::Color(0x5D, 0x75, 0xA7), sf::Color::White, 2.f, sf::Vector2f(190.f, 825.f));
    configureText(upgradeTextMageTower, std::to_string(player.upgrades[1]->getUpgradeCost()), fontP, 20, sf::Color(255, 215, 0), sf::Color::Black, 3.f, sf::Vector2f(238.f, 840.f)); 

    configureButton(upgradeArchMageButton, sf::Vector2f(150.f, 50.f), sf::Color(0x5D, 0x75, 0xA7), sf::Color::White, 2.f, sf::Vector2f(352.f, 825.f));
    configureText(upgradeTextArchMageTower, std::to_string(player.upgrades[2]->getUpgradeCost()), fontP, 20, sf::Color(255, 215, 0), sf::Color::Black, 3.f, sf::Vector2f(400.f, 840.f)); 
}

void playState::handleEvent(sf::RenderWindow& window, sf::Event& event) {
    if (event.is<sf::Event::Closed>()) {
        window.close();
    }

    auto mousePos = sf::Mouse::getPosition(window);
    int row = mousePos.y / 35;
    int col = mousePos.x / 35;

    if (player.isCardSelected) {

        if(const auto* keyEvent = event.getIf<sf::Event::KeyPressed>()) {
            if(keyEvent->code == sf::Keyboard::Key::Escape) {
                player.isCardSelected = false;
                player.areaOfEffect.clear();
                return;
            }
        }

        std::pair<int, int> pos = {col, row};

        if (pos.first >= 0 && pos.first < 26 &&
        pos.second >= 0 && pos.second < 19) {
            const auto& mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
            player.areaOfEffect.clear();
            if(player.selectedTowerType == towerType::ARCHER) {
                calculateAreaOfEffect(player.areaOfEffect, 5, pos, 26, 19);
            } else if (player.selectedTowerType == towerType::MAGE) {
                calculateAreaOfEffect(player.areaOfEffect, 4, pos, 26, 19);
            } else if (player.selectedTowerType == towerType::ARCHMAGE) {
                calculateAreaOfEffect(player.areaOfEffect, 3, pos, 26, 19);
            }

            if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
                
                if (map.getGrid()[row][col].type == TileType::EMPTY && map.getGrid()[row][col].enemiesOnTile.empty()) {
                    map.placeTower(col, row);
                    if (!pathfinder.findPath(map, map.getStart(), map.getGoal()).empty()) {
                        std::unique_ptr<tower> tower;
                        if(player.selectedTowerType == towerType::ARCHER) { tower = towerFactory::createTower(player.selectedTowerType, archerTowerTexture, pos, *player.upgrades[static_cast<int>(player.selectedTowerType)], map); }
                        if(player.selectedTowerType == towerType::MAGE) { tower = towerFactory::createTower(player.selectedTowerType, mageTowerTexture, pos, *player.upgrades[static_cast<int>(player.selectedTowerType)], map); }
                        if(player.selectedTowerType == towerType::ARCHMAGE) { tower = towerFactory::createTower(player.selectedTowerType, archMageTowerTexture, pos, *player.upgrades[static_cast<int>(player.selectedTowerType)], map); }
                        
                        player.towers.push_back(std::move(tower));
                        player.isCardSelected = false;
                        player.areaOfEffect.clear();
                        player.spendGold(player.upgrades[static_cast<int>(player.selectedTowerType)]->getCost());
                    } else {
                        map.freeTile(col, row);
                    }
                }
            }
        }

    } else if (!player.isCardSelected) {
        for (sf::RectangleShape* button : {&archerTowerButton, &mageTowerButton, &archMageTowerButton}) {
            const auto& mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
            if (button->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                button->setFillColor(sf::Color(0x1C, 0x52, 0xBF));
                if(mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
                    if (button == &archerTowerButton && player.getGold() >= 100 && button->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        player.selectedTowerType = towerType::ARCHER;
                        button->setFillColor(sf::Color::Green);
                        player.isCardSelected = true;
                    } else if (button == &mageTowerButton && player.getGold() >= 200 && button->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        player.selectedTowerType = towerType::MAGE;
                        button->setFillColor(sf::Color::Green);
                        player.isCardSelected = true;
                    } else if (button == &archMageTowerButton && player.getGold() >= 300 && button->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        player.selectedTowerType = towerType::ARCHMAGE;
                        button->setFillColor(sf::Color::Green);
                        player.isCardSelected = true;
                    }
                    return;
                }
            } else {
                button->setFillColor(sf::Color(0x5D, 0x75, 0xA7));
            }
        }
    }

    for (sf::RectangleShape* button : {&upgradeArcherButton, &upgradeMageButton, &upgradeArchMageButton}) {
        if(button->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            button->setFillColor(sf::Color(0x1C, 0x52, 0xBF));
            const auto& mouseEvent = event.getIf<sf::Event::MouseButtonPressed>();
            if(mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
                if(button == &upgradeArcherButton) {
                    if(player.upgrades[0]->getUpgradeCost() < player.getGold() && player.upgrades[0]->getLevel() <= 3) {
                        button->setFillColor(sf::Color::Green);
                        player.spendGold(player.upgrades[0]->getUpgradeCost());
                        player.upgrades[0]->upgrade();
                        upgradeTextArcherTower.setString(std::to_string(player.upgrades[0]->getUpgradeCost()));
                    } else { button->setFillColor(sf::Color::Red); }
                } else if (button == &upgradeMageButton) {
                    if(player.upgrades[1]->getUpgradeCost() < player.getGold() && player.upgrades[1]->getLevel() <= 3) {
                        button->setFillColor(sf::Color::Green);
                        player.spendGold(player.upgrades[1]->getUpgradeCost());
                        player.upgrades[1]->upgrade();
                        upgradeTextMageTower.setString(std::to_string(player.upgrades[1]->getUpgradeCost()));
                    } else { button->setFillColor(sf::Color::Red); }
                } else if (button == &upgradeArchMageButton) {
                    if(player.upgrades[2]->getUpgradeCost() < player.getGold() && player.upgrades[2]->getLevel() <= 3) {
                        button->setFillColor(sf::Color::Green);
                        player.spendGold(player.upgrades[2]->getUpgradeCost());
                        player.upgrades[2]->upgrade();
                        upgradeTextArchMageTower.setString(std::to_string(player.upgrades[2]->getUpgradeCost()));
                    } else { button->setFillColor(sf::Color::Red); }
                }
            }
        } else {
            button->setFillColor(sf::Color(0x5D, 0x75, 0xA7));
        }
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

    for (const auto& tower : player.towers) {
        tower->update(deltaTime, map);
    }

    goldAnimated.update(deltaTime);
    archerTowerAnimated.update(deltaTime);
    mageTowerAnimated.update(deltaTime);
    archMageTowerAnimated.update(deltaTime); 
    player.castleUpdate(deltaTime);
    

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

    enemyManager.updateWave(deltaTime, wavePath, map, *player.getCastle(), player);

    static sf::Clock testWaveClock;
    if (testWaveClock.getElapsedTime().asSeconds() > 10.f) {
        waveStarted = false;
        testWaveClock.restart();
    }

    if(player.getCastle()->getHealth() <= 0) {
        manager.popState();
    }
}


void playState::render(sf::RenderWindow& window) {
    window.clear(sf::Color(0x57, 0x80, 0xD3));

    const auto& tiles = map.getGrid();

    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            sf::RectangleShape tileShape(sf::Vector2f(35.f, 35.f));
            tileShape.setPosition(sf::Vector2(tile.x * 35.f, tile.y * 35.f));

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

    if(player.isCardSelected) {
        for (const auto& tile : player.areaOfEffect) {
            sf::RectangleShape effectTile(sf::Vector2f(35.f, 35.f));
            effectTile.setFillColor(sf::Color(0, 255, 0, 100));
            effectTile.setPosition(sf::Vector2f(tile.first * 35.f, tile.second * 35.f)); // Posición en el mapa
            window.draw(effectTile);
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f spritePos = sf::Vector2f(static_cast<float>(mousePos.x) - 35.f, static_cast<float>(mousePos.y) - 35.f);

        if(player.selectedTowerType == towerType::ARCHER) {
            auto archerPreview = archerTowerAnimated;
            archerPreview.setPosition(spritePos);
           // archerPreview.setScale(sf::Vector2f(80.f, 80.f));
            archerPreview.setCol(sf::Color(255, 255, 255, 150));
            window.draw(archerPreview);
        } else if(player.selectedTowerType == towerType::MAGE) {
            auto magePreview = mageTowerAnimated;
            magePreview.setPosition(spritePos);
          //  magePreview.setScale(sf::Vector2f(80.f, 80.f));
            magePreview.setCol(sf::Color(255, 255, 255, 150));
            window.draw(magePreview);
        } else if(player.selectedTowerType == towerType::ARCHMAGE) {
            auto archMagePreview = archMageTowerAnimated;
            archMagePreview.setPosition(spritePos);
          //  archMagePreview.setScale(sf::Vector2f(80.f, 80.f));
            archMagePreview.setCol(sf::Color(255, 255, 255, 150));
            window.draw(archMagePreview);
        }
    }


    for (const auto& button: {archerTowerButton, mageTowerButton, archMageTowerButton, upgradeArcherButton, upgradeMageButton, upgradeArchMageButton}) {
        window.draw(button);
    }

    for (const auto& text: {textGold, textArcherTower, textArchMageTower, textMageTower, upgradeTextArcherTower, upgradeTextMageTower, upgradeTextArchMageTower}) {
        window.draw(text);
    }

    for (const auto& animation : {goldAnimated, archerTowerAnimated, mageTowerAnimated, archMageTowerAnimated}) {
        window.draw(animation);
    }

    for (const auto& tower : player.towers) {
        tower->render(window);
    }

    enemyManager.drawAll(window);
    player.castleRender(window);

    window.display();
}
