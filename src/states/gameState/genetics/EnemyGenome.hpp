#pragma once
#include "EnemyType.hpp"

struct EnemyGenome {
    float health;
    float speed;
    float resistArrow;
    float resistMagic;
    float resistArtillery;
    float fitness = 0.0f;

    EnemyType type;

    EnemyGenome() = default;

    EnemyGenome(float h, float s, float ra, float rm, float rt, EnemyType t)
        : health(h), speed(s), resistArrow(ra), resistMagic(rm), resistArtillery(rt), type(t) {}
};
