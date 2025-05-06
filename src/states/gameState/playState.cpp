#include "playState.hpp"
#include <iostream>

playState::playState(gameStateManager& manager) : manager(manager), map(26, 19) {
    map.setStart(0, 0);
    map.setGoal(25, 9);

    Player player = Player();

    if (!playerGoldTexture.loadFromFile("assets/sprites/coin.png")) {
        std::cerr << "Error loading texture" << std::endl;
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

    float deltaTime = clock.restart().asSeconds();
    goldAnimated.update(deltaTime);
}

void playState::render(sf::RenderWindow& window) {
    static sf::Clock clock;
    window.clear(sf::Color(0x57, 0x80, 0xD3));

    const auto& tiles = map.getGrid();

    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            sf::RectangleShape tileShape(sf::Vector2f(25.f, 25.f));
            tileShape.setPosition(sf::Vector2(tile.x * 25.f, tile.y * 25.f));

            switch (tile.type)
            {
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

    window.display();
}