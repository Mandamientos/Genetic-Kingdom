#include "GeneticManager.hpp"
#include <algorithm>

EnemyGenome crossover(const EnemyGenome& p1, const EnemyGenome& p2) {
    return EnemyGenome(
        (p1.health + p2.health) / 2.f,
        (p1.speed + p2.speed) / 2.f,
        (p1.resistArrow + p2.resistArrow) / 2.f,
        (p1.resistMagic + p2.resistMagic) / 2.f,
        (p1.resistArtillery + p2.resistArtillery) / 2.f,
        (p1.type)
    );
}

void mutate(EnemyGenome& g, std::default_random_engine& rng, std::uniform_real_distribution<float>& dist, float mutationRate) {
    auto maybeMutate = [&](float& gene) {
        if (std::uniform_real_distribution<float>(0.0f, 1.0f)(rng) < mutationRate) {
            gene += dist(rng);
            if (gene < 0.f) gene = 0.f;
        }
    };

    maybeMutate(g.health);
    maybeMutate(g.speed);
    maybeMutate(g.resistArrow);
    maybeMutate(g.resistMagic);
    maybeMutate(g.resistArtillery);
}

std::vector<EnemyGenome> GeneticManager::evolve(const std::vector<EnemyGenome>& previous) {
    generation++;

    auto sorted = previous;
    std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
        return a.fitness > b.fitness;
    });

    int survivors = std::max(2, (int)(sorted.size() / 2));
    std::vector<EnemyGenome> newGen;

    for (int i = 0; i < sorted.size(); ++i) {
        const EnemyGenome& p1 = sorted[i % survivors];
        const EnemyGenome& p2 = sorted[(i + 1) % survivors];

        EnemyGenome child = crossover(p1, p2);
        mutate(child, rng, mutationDist, mutationRate);
        newGen.push_back(child);
    }

    return newGen;
}
