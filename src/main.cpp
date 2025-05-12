#include <SFML/Graphics.hpp>
#include "gameStateManager.hpp"
#include "mainMenu.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 900}), "Genetic Kingdom");

    gameStateManager stateManager;
    stateManager.pushState(std::make_unique<mainMenu>(stateManager));

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if(stateManager.getCurrentState()) {
                stateManager.getCurrentState()->handleEvent(window, *event);
            }
        }

        if(stateManager.getCurrentState()) {
            stateManager.getCurrentState()->update(window);
        }
        window.clear();

        if(stateManager.getCurrentState()) {
            stateManager.getCurrentState()->render(window);
        }
        window.display();
    }


    return 0;
}