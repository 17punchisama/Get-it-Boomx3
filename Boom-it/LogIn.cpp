#include "LogIn.h"

void LogIn::initTexture()
{
	if (!backgroundTexture.loadFromFile("images/login-test.png"))
	{
		std::cout << "Can't open picture" << std::endl;
	}
}

void LogIn::initSprite()
{
	this->backgroundSprite.setTexture(this->backgroundTexture);
}

LogIn::LogIn()
{
	if (!font.loadFromFile("fonts/VCR_OSD_MONO_1.001.ttf"))
	{
		std::cout << "Can't open font" << std::endl;
	}
	this->initTexture();
	this->initSprite();

	this->nextState.setFont(this->font);
	this->nextState.setFillColor(sf::Color::White);
	this->nextState.setString("NEXT");
	this->nextState.setPosition(sf::Vector2f(1750, 970));
	this->nextState.setCharacterSize(50);
	this->nextState.setOutlineThickness(1);

	this->backState.setFont(this->font);
	this->backState.setFillColor(sf::Color::White);
	this->backState.setString("BACK");
	this->backState.setPosition(sf::Vector2f(50, 970));
	this->backState.setCharacterSize(50);
	this->backState.setOutlineThickness(1);
}

LogIn::~LogIn()
{
}

void LogIn::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Blue);
	window.draw(backgroundSprite);
	window.draw(nextState);
	window.draw(backState);
}

void LogIn::updateMouseInput(sf::RenderWindow& window)
{
	this->mousePosition = sf::Mouse::getPosition(window);

	if (nextState.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
	{
		this->nextState.setFillColor(sf::Color::Magenta);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->checkState = "next";
		}
	}
	else
		this->nextState.setFillColor(sf::Color::White);

	if (backState.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
	{
		this->backState.setFillColor(sf::Color::Magenta);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->checkState = "back";
		}
	}
	else
		this->backState.setFillColor(sf::Color::White);
}
