#include <SFML/Graphics.hpp>

int main() {
    sf::Vector2u windowSize(800, 600);
    
    sf::RenderWindow window(sf::VideoMode(windowSize), "SFML Window");

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}