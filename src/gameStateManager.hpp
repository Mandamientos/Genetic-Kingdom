#pragma once
#include "gameState.hpp"
#include <memory>
#include <stack>

class gameStateManager {
    std::stack<std::unique_ptr<gameState>> states;

    public:
        void pushState(std::unique_ptr<gameState> state) {
            states.push(std::move(state));
        }

        void popState() {
            if (!states.empty()) {
                states.pop();
            }
        }

        gameState* getCurrentState() {
            if (!states.empty()) {
                return states.top().get();
            }
            return nullptr;
        }
};
