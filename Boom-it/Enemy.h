#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy
{
private:
	unsigned pointCount;

	sf::Texture texture;
	sf::Sprite sprite;
	
	int type;

	float speed;
	float damage;

	void initVariables();

	void initTexture();
	void initSprite();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	const sf::FloatRect getBounds() const;
	const int& getDamage() const;

	void update();
	void render(sf::RenderTarget* target);
};

#endif //!ENEMY_H