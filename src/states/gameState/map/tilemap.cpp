#include "tilemap.hpp"
#include <algorithm>

TileMap::TileMap(int w, int h) : width(w), height(h) {
    grid.resize(height, std::vector<tile>(width, tile(0, 0)));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid[y][x] = tile(x, y, TileType::EMPTY);
        }
    }
}

void TileMap::setStart(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[y][x].type = TileType::START;
        startPos = {x, y};
    } else {
        std::cerr << "Invalid start position" << std::endl;
    }
}

void TileMap::setGoal(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[y][x].type = TileType::GOAL;
        goalPos = {x, y};
    } else {
        std::cerr << "Invalid goal position" << std::endl;
    }
}

void TileMap::addEnemyToTile(int x, int y, Enemy* enemy) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[y][x].enemiesOnTile.push_back(enemy);
    } else {
        std::cerr << "Invalid tile position" << std::endl;
    }
}

void TileMap::removeEnemyFromTile(int x, int y, Enemy* enemy) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        auto& enemies = grid[y][x].enemiesOnTile;

        enemies.erase(
            std::remove(enemies.begin(), enemies.end(), enemy),
            enemies.end()
        );
    } else {
        std::cerr << "Invalid tile position in removeEnemyFromTile: (" << x << ", " << y << ")\n";
    }
}

void TileMap::placeTower(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        grid[y][x].type = TileType::TOWER;
        grid[y][x].isWalkable = false;
    } else {
        std::cerr << "Invalid tower position" << std::endl;
    }
}

const std::vector<std::vector<tile>>& TileMap::getGrid() {
    return grid;
}

std::pair<int, int> TileMap::getStart() const {
    return startPos;
}
std::pair<int, int> TileMap::getGoal() const {
    return goalPos;
}
