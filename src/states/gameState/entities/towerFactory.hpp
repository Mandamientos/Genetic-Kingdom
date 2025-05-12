#include "tower.hpp"
#include "archerTower.hpp"
#include "tilemap.hpp"
#include <memory>

class towerFactory {
    public:
        static std::unique_ptr<tower> createTower(towerType type, const sf::Texture& texture, const std::pair<int, int>& pos, towerUpgrade& stats, TileMap& map) {
            switch (type) {
                case towerType::ARCHER:
                    map.placeTower(pos.first, pos.second);
                    return std::make_unique<archerTower>(texture, pos, stats);
                case towerType::MAGE:
                    // return std::make_unique<mageTower>(texture, pos);
                case towerType::ARCHMAGE:
                    // return std::make_unique<archMageTower>(texture, pos);
                default:
                    throw std::invalid_argument("Invalid TowerType");
            }
        }
};