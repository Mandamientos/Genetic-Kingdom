#pragma once
#include <SFML/Graphics.hpp>

class animateSprite : public sf::Drawable, public sf::Transformable {
    public:
        animateSprite();

        void setTexture(const sf::Texture& texture, int frameWidth, int frameHeight, int frameCount, float frameTime, int row = 0);
        void update(float deltaTime);
        void setRow(int row);
        void play();
        void pause();
        void stop();
    
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        const sf::Texture* texture;
        std::optional<sf::Sprite> sprite;
        int frameWidth, frameHeight, frameCount;
        int currentFrame;
        int currentRow;
        float frameTime;
        float currentTime;
        float timeAccumulated;
        bool isPlaying;
};