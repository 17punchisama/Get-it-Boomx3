#include "Item.h"

void Item::initTexture()
{
    switch (this->type)
    {
    case Cherry:
        if (!Texture.loadFromFile("images/Cherry-asset.png"))
        {
            std::cout << "Can't Open 1" << std::endl;
        }
        break;
    case Heart:
        if (!Texture.loadFromFile("images/Heart_pink.png"))
        {
            std::cout << "Can't Open 2" << std::endl;
        }
        break;
    case Poison:
        if (!Texture.loadFromFile("images/Poison.png"))
        {
            std::cout << "Can't Open 3" << std::endl;
        }
        break;
    }
}


void Item::initSprite()
{
    this->Sprite.setTexture(this->Texture);
    this->Sprite.setScale(.1f, .1f);
}

Item::Item(float pos_x, float pos_y, ItemType itemType)
{
    this->type = itemType;
    this->initTexture();
    this->initSprite();
}

Item::~Item()
{
}

void Item::update()
{

}

void Item::setPosition(float x, float y)
{
    this->Sprite.setPosition(x, y);
}

sf::Vector2f Item::getPosition() const
{
    return Sprite.getPosition();
}

void Item::render(sf::RenderTarget* target)
{
    target->draw(this->Sprite);
}

const sf::FloatRect Item::getBounds() const
{
    return this->Sprite.getGlobalBounds();
}

ItemType Item::getType() const
{
    return this->type;
}