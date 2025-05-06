#include "playState.hpp"
#include <iostream>

playState::playState(gameStateManager& manager) : manager(manager), map(10, 10) {
    map.setStart(0, 0);
    map.setGoal(9, 9);
}

void playState::handleEvent(sf::RenderWindow& window, sf::Event& event) {
    if (event.is<sf::Event::Closed>()) {
        window.close();
    }
}

void playState::update(sf::RenderWindow& window) {

}

void playState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    window.display();
}