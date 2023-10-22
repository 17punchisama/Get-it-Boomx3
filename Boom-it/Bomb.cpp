#include "Bomb.h"
#include <iostream>

void Bomb::initTexture()
{
    if (!this->texture.loadFromFile("images/cherry-bomb-new.png")) {
        std::cout << "Failed to load texture" << std::endl;
    }
}

void Bomb::initSprite()
{
    this->sprite.setTexture(this->texture);
    this->explosionTime = 3.0f;
    this->clock.restart();
    this->sprite.setScale(0.75f, 0.75f);
    this->bombFrame = sf::IntRect(0, 0, 64, 64);
    this->sprite.setTextureRect(this->bombFrame);
}

void Bomb::initTextureEffect()
{
    if (!this->effectTexture.loadFromFile("images/effect.png")) {
        std::cout << "Failed to load effect" << std::endl;
    }
}

void Bomb::initSpriteEffect()
{
    this->effectSprite.setTexture(this->effectTexture);
    this->currentFrame = sf::IntRect(0, 0, 36, 36);
    this->effectSprite.setTextureRect(this->currentFrame);
}

void Bomb::updateInput()
{
}

Bomb::Bomb(float x, float y)
{
    this->initSprite();
    this->initTexture();
    
    this->sprite.setPosition(x + 20, y + 50);
    exploded = false;
    this->updateBombAnimation();
}

Bomb::Bomb()
{
    //
}

Bomb::~Bomb()
{
}

sf::FloatRect Bomb::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}

void Bomb::updateBombAnimation()
{
    if (this->clock.getElapsedTime().asSeconds() >= 0.6f)
    {
        if (this->explosionTime >= 0)
        {
            this->bombFrame.left += 64;
            if (bombFrame.left >= 320.0f)
                this->bombFrame.left = 0;

            this->sprite.setTextureRect(this->bombFrame);
            this->clock.restart();
        }
    }
}

void Bomb::update()
{
    if (!exploded)
    {
        float deltaTime = clock.restart().asSeconds();
        this->updateBombAnimation();
        if (this->explosionTime <= 0)
        {
            exploded = true;
            this->initTextureEffect();
            this->initSpriteEffect();
            this->updateBombAnimation();
        }
        else
        {
            this->explosionTime -= deltaTime;
        }
    }
}

void Bomb::render(sf::RenderTarget* target) const
{
    target->draw(this->sprite);
}

bool Bomb::shouldExplode() const
{
    return clock.getElapsedTime().asSeconds() >= explosionTime;
}

void Bomb::renderEffect(sf::RenderTarget* target) const
{
    target->draw(this->effectSprite);
}
