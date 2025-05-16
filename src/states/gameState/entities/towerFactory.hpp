#include "tower.hpp"
#include "archerTower.hpp"
#include "mageTower.hpp"
#include "archMageTower.hpp"
#include "tilemap.hpp"
#include <memory>

class towerFactory {
    public:
        static std::unique_ptr<tower> createTower(towerType type, const sf::Texture& texture, const std::pair<int, int>& pos, towerUpgrade& stats, TileMap& map) {
            switch (type) {
                case towerType::ARCHER:
                    map.placeTower(pos.first, pos.second);
                    return std::make_unique<archerTower>(texture, pos, stats, map);
                case towerType::MAGE:
                    map.placeTower(pos.first, pos.second);
                    return std::make_unique<mageTower>(texture, pos, stats, map);
                case towerType::ARCHMAGE:
                    map.placeTower(pos.first, pos.second);
                    return std::make_unique<archMageTower>(texture, pos, stats, map);
                default:
                    throw std::invalid_argument("Invalid TowerType");
            }
        }
};