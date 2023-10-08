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
	if (!font.loadFromFile("fonts/VT323-Regular.ttf"))
	{
		std::cout << "Can't open font" << std::endl;
	}
	this->initTexture();
	this->initSprite();

	this->nextState.setFont(this->font);
	this->nextState.setFillColor(sf::Color::White);
	this->nextState.setString("Click to start!");
	this->nextState.setPosition(sf::Vector2f(1590, 970));
	this->nextState.setCharacterSize(50);
	this->nextState.setOutlineThickness(1);
}

LogIn::~LogIn()
{
}

void LogIn::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Blue);
	window.draw(backgroundSprite);
	window.draw(nextState);
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
}
