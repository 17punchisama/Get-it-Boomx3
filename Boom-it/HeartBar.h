#pragma once

#include <SFML/Graphics.hpp>

class HeartBar
{
private:
    sf::Sprite heartSprites[3];
    sf::Texture heartTexture;

    sf::IntRect currentFrame;

    int Hp;
    int HpMax;
    float x;
    float y;

    void initVariable();
    void initTexture();
    void initSprite();

public:
    HeartBar();
    HeartBar(float x, float y);

    
    void loseHeart();
    void resetHearts();
    void updateHearts(); // อัปเดตสถานะของหัวใจและเปลี่ยน current frame ของรูป
    void update(const sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};