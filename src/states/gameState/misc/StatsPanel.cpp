#include "StatsPanel.hpp"
#include <sstream>

StatsPanel::StatsPanel()
    : generationText(font, "", 18),
      deadEnemiesText(font, "", 18),
      mutationText(font, "", 18) 
{
    font.openFromFile("assets/fonts/MedievalSharp-Regular.ttf");

    generationText.setFillColor(sf::Color::White);
    generationText.setPosition(sf::Vector2f(700.f, 50.f));

    deadEnemiesText.setFillColor(sf::Color::White);
    deadEnemiesText.setPosition(sf::Vector2f(700.f, 80.f));

    mutationText.setFillColor(sf::Color::White);
    mutationText.setPosition(sf::Vector2f(700.f, 110.f));
}

void StatsPanel::update(int generation, int deadEnemies,
                        const std::vector<float>& fitnessValues,
                        const std::vector<int>& towerLevels,
                        int mutationCount) {
    this->mutationCount = mutationCount;

    generationText.setString("Gen: " + std::to_string(generation));
    deadEnemiesText.setString("Muertos esta oleada: " + std::to_string(deadEnemies));
    mutationText.setString("Mutaciones: " + std::to_string(mutationCount) +
                           " (" + std::to_string((int)(mutationProbability * 100)) + "%)");

    fitnessTexts.clear();
    for (size_t i = 0; i < fitnessValues.size(); ++i) {
        sf::Text text(font, "", 14);
        text.setFillColor(sf::Color::Yellow);
        text.setPosition(sf::Vector2f(700.f, 140.f + i * 20));
        text.setString("Fitness [" + std::to_string(i) + "]: " + std::to_string(fitnessValues[i]));
        fitnessTexts.push_back(text);
    }

    towerLevelTexts.clear();
    for (size_t i = 0; i < towerLevels.size(); ++i) {
        sf::Text text(font, "", 14);
        text.setFillColor(sf::Color::Cyan);
        text.setPosition(sf::Vector2f(700.f, 300.f + i * 20));
        text.setString("Torre [" + std::to_string(i) + "] Lv: " + std::to_string(towerLevels[i]));
        towerLevelTexts.push_back(text);
    }
}

void StatsPanel::draw(sf::RenderWindow& window) {
    window.draw(generationText);
    window.draw(deadEnemiesText);
    window.draw(mutationText);

    for (auto& t : fitnessTexts)
        window.draw(t);

    for (auto& t : towerLevelTexts)
        window.draw(t);
}
