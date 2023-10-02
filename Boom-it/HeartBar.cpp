#include "HeartBar.h"
#include <iostream>

void HeartBar::initVariable()
{
	this->HpMax = 3;
	this->Hp = this->HpMax;
}

void HeartBar::initTexture()
{
	if (!this->heartTexture.loadFromFile("images/heart.png"))
	{
		std::cout << "Failed to load heart" << std::endl;
	}
}

void HeartBar::initSprite()
{
	for (int i = 0; i < 3; ++i)
	{
		this->heartSprites[i].setTexture(this->heartTexture);
		this->currentFrame = sf::IntRect(0, 0, 32, 32);

		this->heartSprites[i].setTextureRect(this->currentFrame);
		this->heartSprites[i].setPosition(10.0f + i * 40.0f, 10.0f); // กำหนดตำแหน่ง X แต่ละหัวใจให้เรียงติดกัน
	}
}


HeartBar::HeartBar()
{

}

HeartBar::HeartBar(float x, float y)
{
	this->initVariable();
	this->initTexture();
	this->initSprite();
}

void HeartBar::loseHeart()
{
	if (this->Hp > 0)
	{
		this->Hp--;
	}
}

void HeartBar::resetHearts()
{
	this->Hp = HpMax;
}

void HeartBar::updateHearts()
{
	for (int i = 0; i < HpMax; i++)
	{
		if (i < Hp)
		{
			this->currentFrame.left = 0;
		}
		else
		{
			this->currentFrame.left = 32;
		}
		this->heartSprites[i].setTextureRect(this->currentFrame);
	}
}

void HeartBar::update(const sf::RenderTarget* target)
{
	this->initVariable();
	this->initTexture();
	this->initSprite();
	this->loseHeart();
	this->resetHearts();
}

void HeartBar::render(sf::RenderTarget* target)
{
	for (int i = 0; i < 3; ++i)
	{
		target->draw(this->heartSprites[i]);
	}
}
