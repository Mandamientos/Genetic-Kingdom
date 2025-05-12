#include <iostream>
#include "player.hpp"

Player::Player() {}

void Player::addGold (int amount, sf::Text& textGold) {
    gold += amount;
    updateGold(gold, textGold);
}

bool Player::spendGold (int amount, sf::Text& textGold) {
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

void Player::updateGold (int currentGold, sf::Text& textGold) {
    textGold.setString("Gold: " + std::to_string(currentGold));
}