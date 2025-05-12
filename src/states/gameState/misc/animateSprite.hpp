#pragma once
#include <SFML/Graphics.hpp>

class animateSprite : public sf::Drawable, public sf::Transformable {
    public:
        animateSprite();

        void setTexture(const sf::Texture& tex, int frameWidth, int frameHeight, int frameCount, float frameTime, int row = 0);
        void update(float deltaTime);
        void setRow(int row);
        void play();
        void pause();
        void stop();
        void setDrawSize(const sf::Vector2f& size);
        void setPosition(const sf::Vector2f& position);
        void setDirection(bool facingRight);
        void setCol(const sf::Color& color);
        sf::Vector2f getPosition() const;
    
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        std::optional<sf::Sprite> sprite;
        const sf::Texture* texture;
        int frameWidth, frameHeight, frameCount;
        int currentFrame;
        int currentRow;
        float frameTime;
        float currentTime;
        float timeAccumulated;
        bool isPlaying;
};