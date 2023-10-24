#include "Enemy.h"

void Enemy::initVariables()
{
	this->type = rand() % 3;
	switch (this->type)
	{
	case 0:
		this->damage = 5;
		this->speed = 1.f;
		break;
	case 1:
		this->damage = 10;
		this->speed = 5.f;
		break;
	case 2:
		this->damage = 15;
		this->speed = 8.0f;
		break;
	}
}


void Enemy::initTexture()
{
	switch (this->type)
	{
	case 0:
		if (!texture.loadFromFile("images/ballpurple3.png"))
		{

		}
		break;
	case 1:
		if (!texture.loadFromFile("images/botzorange4.png"))
		{

		}
		break;
	case 2:
		if (!texture.loadFromFile("images/botred1.png"))
		{
			std::cout << "Can't Open case 3" << std::endl;
		}
		break;
	}
}

void Enemy::initSprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(1.75f, 1.75f);
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initTexture();
	this->initSprite();

	this->sprite.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

void Enemy::update()
{
	this->sprite.move(-this->speed, 0.f);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
