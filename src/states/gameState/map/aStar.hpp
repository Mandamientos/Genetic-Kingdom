#pragma once
#include <vector>
#include <utility>
#include "tilemap.hpp"

class AStarPathfinder {
public:
    std::vector<std::pair<int, int>> findPath(
        TileMap& map,
        std::pair<int, int> start,
        std::pair<int, int> goal
    );
};
