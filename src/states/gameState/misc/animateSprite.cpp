#include "animateSprite.hpp"
#include <SFML/Graphics.hpp>

animateSprite::animateSprite() : texture(nullptr), frameWidth(0), frameHeight(0), frameCount(0), currentFrame(0), currentRow(0), frameTime(0.1f), currentTime(0.f), timeAccumulated(0.f), isPlaying(true) {}

void animateSprite::setTexture(const sf::Texture& tex, int fw, int fh, int fc, float ft, int row) {
    texture = &tex;
    sprite.emplace(tex);
    frameWidth = fw;
    frameHeight = fh;
    frameCount = fc;
    frameTime = ft;
    currentRow = row;
    currentFrame = 0;
    timeAccumulated = 0.f;

    (*sprite).setTextureRect(sf::IntRect(
        sf::Vector2i(0, row * frameHeight),
        sf::Vector2i(frameWidth, frameHeight)
    ));
}

void animateSprite::setRow(int row) {
    currentRow = row;
    currentFrame = 0;
    timeAccumulated = 0.f;

    if (sprite) {
        (*sprite).setTextureRect(sf::IntRect(
            sf::Vector2i(0, row * frameHeight),
            sf::Vector2i(frameWidth, frameHeight)
        ));
    }
}

void animateSprite::update(float deltaTime) {
    if (isPlaying && sprite) {
        timeAccumulated += deltaTime;

        if (timeAccumulated >= frameTime) {
            currentFrame = (currentFrame + 1) % frameCount;
            timeAccumulated -= frameTime;

            (*sprite).setTextureRect(sf::IntRect(
                sf::Vector2i(currentFrame * frameWidth, currentRow * frameHeight),
                sf::Vector2i(frameWidth, frameHeight)
            ));
        }
    }
}

void animateSprite::play() {
    isPlaying = true;
}

void animateSprite::pause() {
    isPlaying = false;
}

void animateSprite::stop() {
    isPlaying = false;
    currentFrame = 0;
    timeAccumulated = 0.f;

    if (sprite) {
        (*sprite).setTextureRect(sf::IntRect(
            sf::Vector2i(0, currentRow * frameHeight),
            sf::Vector2i(frameWidth, frameHeight)
        ));
    }
}

void animateSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (sprite) {
        states.transform *= getTransform();
        target.draw(*sprite, states);
    }
}