#include "aStar.hpp"
#include <queue>
#include <set>
#include <algorithm>
#include <cmath>

// Calculado la distancia (H) desde un nodo actual nodo objetivo .

static int heuristic(const tile& a, const tile& b) {
    
    int dx = std::abs(a.x - b.x);
    int dy = std::abs(a.y - b.y);
    return static_cast<int>(10 * std::sqrt(dx * dx + dy * dy));
}

// Obteniendo los "vecinos" de la casilla (verticales, horizontales y diagonales).

static std::vector<std::pair<int, int>> getNeighbors(const tile& t, int width, int height, const std::vector<std::vector<tile>>& grid) {
    std::vector<std::pair<int, int>> neighbors;
    const std::vector<std::pair<int, int>> directions = {
        { 0, -1}, { 1,  0}, { 0,  1}, {-1,  0}, 
    //    {-1, -1}, { 1, -1}, { 1,  1}, {-1,  1}  
    };

    for (const auto& [dx, dy] : directions) {
        int nx = t.x + dx;
        int ny = t.y + dy;
        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
            if (dx != 0 && dy != 0) {
                int adjX = t.x + dx;
                int adjY = t.y;
                int adjY2 = t.y + dy;
                int adjX2 = t.x;

                if (!grid[adjY][adjX2].isWalkable || !grid[adjY2][adjX].isWalkable)
                    continue;
            }

            neighbors.emplace_back(nx, ny);
        }
    }

    return neighbors;
}

// Reconstruyendo el path para obtener el camino desde goal hasta start.
// Empieza goal y retrocede hasta encontrar start, que tiene parent (-1, -1).
static std::vector<std::pair<int, int>> reconstructPath(
    const std::vector<std::vector<tile>>& grid,
    std::pair<int, int> goal
) {
    std::vector<std::pair<int, int>> path;
    std::pair<int, int> current = goal;

    while (grid[current.second][current.first].parent != std::make_pair(-1, -1)) {
        path.push_back(current);
        current = grid[current.second][current.first].parent;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<std::pair<int, int>> AStarPathfinder::findPath(
    TileMap& map,
    std::pair<int, int> start,
    std::pair<int, int> goal
) {
    auto grid = map.getGrid();
    int width = grid[0].size();
    int height = grid.size();

    std::set<std::pair<int, int>> closedSet; // Casillas que ya se evaluaron (closedlist)

    // Comparando para ordenar la priority queue por menor F = G + H
    auto cmp = [&grid](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return grid[a.second][a.first].F() > grid[b.second][b.first].F();
    };

    // Priority queue de openlist ordenados por su valor F
    std::priority_queue<
        std::pair<int, int>,
        std::vector<std::pair<int, int>>,
        decltype(cmp)
    > openList(cmp);

    tile& startTile = grid[start.second][start.first];
    tile& goalTile = grid[goal.second][goal.first];

    startTile.G = 0;
    startTile.H = heuristic(startTile, goalTile);
    openList.push(start);

    while (!openList.empty()) {
        auto [cx, cy] = openList.top();
        openList.pop();

        if (std::make_pair(cx, cy) == goal) {
            return reconstructPath(grid, goal);
        }

        closedSet.insert({cx, cy});

        for (auto [nx, ny] : getNeighbors(grid[cy][cx], width, height, grid)) {
            tile& neighbor = grid[ny][nx];

            if (neighbor.type != TileType::EMPTY && 
                neighbor.type != TileType::START && 
                neighbor.type != TileType::GOAL) {
                continue;
            }
            
            if (closedSet.count({nx, ny})) {
                continue;
            }

            
            bool isDiagonal = std::abs(nx - cx) == 1 && std::abs(ny - cy) == 1;
            int movementCost = isDiagonal ? 14 : 10; 

            int tentativeG = grid[cy][cx].G + movementCost;

            if (tentativeG < neighbor.G || neighbor.G == 0) {
                neighbor.G = tentativeG;
                neighbor.H = heuristic(neighbor, goalTile);
                neighbor.parent = {cx, cy};

                openList.push({nx, ny});
            }
        }
    }

    return {}; 
}
