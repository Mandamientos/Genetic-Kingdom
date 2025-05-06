#pragma once

class Player {
    public:
        Player();

        int getGold() const;
        void addGold(int amount);
        bool spendGold(int amount);
    
    private:
        int gold = 0;
};