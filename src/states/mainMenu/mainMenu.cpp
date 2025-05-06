#include "mainMenu.hpp"
#include "playState.hpp"
#include <SFML/Window.hpp>
#include <iostream>

mainMenu::mainMenu(gameStateManager& manager) : manager(manager), playText(font), quitText(font) {
    if(!font.openFromFile("assets/fonts/PERRYGOT.TTF")) {
        std::cerr << "Error loading font" << std::endl;
    }

    if (!logo.loadFromFile("assets/images/GenKing.png")) {
        std::cerr << "Error loading logo" << std::endl;
    } else {
        logoSprite.emplace(logo);
        logoSprite->setScale(sf::Vector2f(0.15f, 0.15f));
        logoSprite->setPosition(sf::Vector2f(45.f, -100.f));
    } 

    sf::Color color(0x57, 0x80, 0xD3);

    playText.setString("Iniciar Partida");
    playText.setCharacterSize(30);
    playText.setFillColor(sf::Color::White);
    playText.setPosition(sf::Vector2f(70.f, 315.f)); 
    //5d75a7

    playButton.setSize(sf::Vector2f(300.f, 65.f));
    playButton.setFillColor(sf::Color(0x5D, 0x75, 0xA7));
    playButton.setPosition(sf::Vector2f(60.f, 300.f));
    playButton.setOutlineThickness(2);


    quitText.setString("Salir del Juego");
    quitText.setCharacterSize(30);
    quitText.setFillColor(sf::Color::White);
    quitText.setPosition(sf::Vector2f(75.f, 415.f));

    quitButton.setSize(sf::Vector2f(300.f, 65.f));
    quitButton.setFillColor(sf::Color(0x5D, 0x75, 0xA7));
    quitButton.setPosition(sf::Vector2f(60.f, 400.f));
    quitButton.setOutlineThickness(2);

}

void mainMenu::handleEvent(sf::RenderWindow& window, sf::Event& event) {
    if (event.is<sf::Event::Closed>()) {
        window.close();
    }

    if(event.is<sf::Event::MouseButtonPressed>()) {
        auto mousePos = sf::Mouse::getPosition(window);
        if(playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            manager.pushState(std::make_unique<playState>(manager));
        }
        if(quitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            std::cout << "Quit button clicked!" << std::endl;
            window.close();
        }
    }

    auto mousePos = sf::Mouse::getPosition(window);
    if(playButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) { //1c52bf
        playButton.setFillColor(sf::Color(0x1C, 0x52, 0xBF));
        playText.setFillColor(sf::Color::Black);
        playButton.setOutlineColor(sf::Color(0x1C, 0x52, 0xBF));
    } else {
        playText.setFillColor(sf::Color::White);
        playButton.setFillColor(sf::Color(0x5D, 0x75, 0xA7));
        playButton.setOutlineColor(sf::Color::White);
    }

    if(quitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        quitButton.setFillColor(sf::Color(0x1C, 0x52, 0xBF));
        quitText.setFillColor(sf::Color::Black);
        quitButton.setOutlineColor(sf::Color(0x1C, 0x52, 0xBF));
    } else {
        quitText.setFillColor(sf::Color::White);
        quitButton.setFillColor(sf::Color(0x5D, 0x75, 0xA7));
        quitButton.setOutlineColor(sf::Color::White);
    }
}

void mainMenu::update(sf::RenderWindow& window) {
}

void mainMenu::render(sf::RenderWindow& window) { // 5780d3
    sf::Color color(0x57, 0x80, 0xD3);
    window.clear(color);

    if (logoSprite.has_value())
        window.draw(*logoSprite);

    window.draw(playButton);
    window.draw(playText);
    window.draw(quitButton);
    window.draw(quitText);

    window.display();
}