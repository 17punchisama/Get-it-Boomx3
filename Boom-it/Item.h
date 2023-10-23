#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <iostream>

enum ItemType
{
	Cherry,
	Heart,
	Poison,
};

class Item
{
private:
	sf::Texture Texture;
	sf::Sprite Sprite;

	ItemType type;

	float randomX;
	float randomY;

	void initTexture();
	void initSprite();
	void initVariable();

public:
	Item(float pos_x, float pos_y, ItemType itemType);
	~Item();

	const sf::FloatRect getBounds() const;
	ItemType getType() const;

	void update();
	void render(sf::RenderTarget* target);
	void setPosition(float x, float y);
	sf::Vector2f getPosition() const;

};

#endif
