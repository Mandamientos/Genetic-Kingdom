#pragma once
#include "EnemyGenome.hpp"
#include <vector>
#include <random>

class GeneticManager {
private:
    float mutationRate = 0.1f;
    int generation = 0;

    std::default_random_engine rng{std::random_device{}()};
    std::uniform_real_distribution<float> mutationDist{-0.1f, 0.1f};
    std::uniform_real_distribution<float> zeroOne{0.0f, 1.0f};

public:
    int getGeneration() const { return generation; }
    void setMutationRate(float rate) { mutationRate = rate; }

    std::vector<EnemyGenome> evolve(const std::vector<EnemyGenome>& previous);
};