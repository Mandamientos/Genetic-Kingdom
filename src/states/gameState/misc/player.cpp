#include <iostream>
#include "player.hpp"

Player::Player(sf::Text& goldText) : goldText(goldText) {
    playerCastle = std::make_unique<castle>();
}

void Player::addGold (int amount) {
    gold += amount;
    updateGold(gold);
}

bool Player::spendGold (int amount) {
    if (gold >= amount) {
        gold -= amount;
        updateGold(gold);
        return true;
    } else {
        std::cout << "Not enough gold!" << std::endl;
        return false;
    }
}

int Player::getGold () const {
    return gold;
}

void Player::updateGold (int currentGold) {
    goldText.setString(std::to_string(currentGold));
}