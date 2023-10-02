#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
{
	selectedItemIndex = 0;

	if (!font.loadFromFile("fonts/Roboto-Bold.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
	}

	if (!menuMusic.openFromFile("sounds/odd-front.mp3"))
	{
		std::cout << "Failed to load music" << std::endl;
	}
	else
	{
		menuMusic.setLoop(true);
		menuMusic.play();
	}
}

MainMenu::MainMenu(float width, float height)
{

	this->menu[0].setFont(this->font);
	this->menu[0].setFillColor(sf::Color::White);
	this->menu[0].setString("START");
	this->menu[0].setPosition(sf::Vector2f(width / (MAX_NUMBER_OF_ITEMS + 1) * 1, height / 2));

	this->menu[1].setFont(this->font);
	this->menu[1].setFillColor(sf::Color::White);
	this->menu[1].setString("TUTORIAL");
	this->menu[1].setPosition(sf::Vector2f(width / (MAX_NUMBER_OF_ITEMS + 1) * 2, height / 2));

	this->menu[2].setFont(this->font);
	this->menu[2].setFillColor(sf::Color::White);
	this->menu[2].setString("ABOUT");
	this->menu[2].setPosition(sf::Vector2f(width / (MAX_NUMBER_OF_ITEMS + 1) * 3, height / 2));
}

MainMenu::~MainMenu()
{
}

void MainMenu::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	window.draw(backgroundSprite);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}


void MainMenu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		this->menu[selectedItemIndex].setFillColor(sf::Color::White);

		this->selectedItemIndex--;
		if (selectedItemIndex == -1)
		{
			selectedItemIndex = MAX_NUMBER_OF_ITEMS - 1;
		}
		this->menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void MainMenu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		this->menu[selectedItemIndex].setFillColor(sf::Color::White);

		this->selectedItemIndex++;
		if (selectedItemIndex == MAX_NUMBER_OF_ITEMS)
		{
			selectedItemIndex = 0;
		}
		this->menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void MainMenu::initTexture()
{
	this->backgroundTexture.loadFromFile("images/MainMenu.png");
}

void MainMenu::initSprite()
{
	this->backgroundSprite.setTexture(this->backgroundTexture);
}