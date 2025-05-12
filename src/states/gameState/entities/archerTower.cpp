#include "archerTower.hpp"

archerTower::archerTower(const sf::Texture& texture, const std::pair<int, int>& pos, towerUpgrade& stats)
    : tower(pos), stats(stats) {
        archerTowerAnimated.setTexture(texture, 32, 32, 4, 0.2f, 0);
        archerTowerAnimated.setPosition(
            sf::Vector2f(pos.first * 35.f - 20.f, pos.second * 35.f - 43.f)
        );
        archerTowerAnimated.setDrawSize(sf::Vector2f(80.f, 80.f));
        archerTowerAnimated.setDirection(false);

        setRange(5);
        setAttackSpeed(1.0f);
        setSpecialAbilityCooldown(15.f);

        std::cout << "Archer Tower created at position: (" << pos.first << ", " << pos.second << ")" << "stats: " << stats.getDamage() << std::endl;

        calculateAreaOfEffect(26, 19);
}


void archerTower::update(float deltaTime, TileMap& map) {
    archerTowerAnimated.update(deltaTime);

    attackEnemy(map);
}

void archerTower::render(sf::RenderWindow& window) {
    for (const auto& tile : getAreaOfEffect()) {
        sf::RectangleShape rangeTile(sf::Vector2f(35.f, 35.f)); // Tamaño de cada casilla
        rangeTile.setFillColor(sf::Color(0, 255, 0, 50));  // Color semitransparente
        rangeTile.setPosition(sf::Vector2f(tile.first * 35.f, tile.second * 35.f));  // Posición en el mapa
        window.draw(rangeTile);
    }

    window.draw(archerTowerAnimated);
}

void archerTower::attackEnemy(TileMap& map) {
    /*
    if(target) {
        auto enemyPos = target->getPosition();
        std::pair<int, int> targetTile = {
            static_cast<int>(enemyPos.x),
            static_cast<int>(enemyPos.y)
        };
        
        if(std::find(getAreaOfEffect().begin(), getAreaOfEffect().end(), std::make_pair(static_cast<int>(enemyPos.x), static_cast<int>(enemyPos.y))) != getAreaOfEffect().end()) {
            if(attackClock.getElapsedTime().asSeconds() >= getAttackSpeed()) {
                target->takeDamage(stats.getDamage(), "arrow");
                attackClock.restart();
            }
        } else {
            target = nullptr; // Reset target if it's out of range
        }
    }*/
}


