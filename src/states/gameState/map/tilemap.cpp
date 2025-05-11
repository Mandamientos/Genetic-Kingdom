#include "tilemap.hpp"

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

void TileMap::placeTower(int x, int y) {
    grid[y][x].type = TileType::TOWER;
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
