#include <iostream>
#include "player.hpp"

Player::Player () {}

void Player::addGold (int amount) {
    gold += amount;
}

bool Player::spendGold (int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    } else {
        std::cout << "Not enough gold!" << std::endl;
        return false;
    }
}

int Player::getGold () const {
    return gold;
}