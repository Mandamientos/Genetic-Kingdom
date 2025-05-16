#pragma once
#include "Enemy.hpp"
#include <vector>
#include <utility>
#include <iostream>

enum class TileType {
    EMPTY,
    TOWER,
    PATH,
    START,
    GOAL
};

struct tile
{
    int x, y;
    TileType type;
    bool isWalkable;
    int G = 0;
    int H = 0;
    int F() const {return G+H;}
    std::pair<int, int> parent = {-1, -1};
    std::vector<Enemy*> enemiesOnTile;

    tile(int x, int y, TileType type = TileType::EMPTY)
        : x(x), y(y), type(type) {
            isWalkable = (type == TileType::EMPTY || type == TileType::PATH || type == TileType::START);
        }
};

class TileMap {
    int width, height;
    std::vector<std::vector<tile>> grid;
    std::pair<int, int> startPos;
    std::pair<int, int> goalPos;

    public:
        TileMap(int w, int h);

        void setStart(int x, int y);
        void setGoal(int x, int y);
        void placeTower(int x, int y);
        void addEnemyToTile(int x, int y, Enemy* enemy);
        void removeEnemyFromTile(int x, int y, Enemy* enemy);
        void freeTile(int x, int y);
        std::vector<Enemy*> getEnemiesOnTile(int x, int y) { 
            return grid[y][x].enemiesOnTile; 
        }

        const std::vector<std::vector<tile>>& getGrid();
        std::pair<int, int> getStart() const;
        std::pair<int, int> getGoal() const;
    };
