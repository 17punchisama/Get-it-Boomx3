#include "MainMenu.h"
#include <iostream>
using namespace std;

MainMenu::MainMenu()
{
	selectedItemIndex = 0;
	if (!font.loadFromFile("fonts/VT323-Regular.ttf"))
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

	this->menu[0].setFont(this->font);
	this->menu[0].setFillColor(sf::Color::White);
	this->menu[0].setString("START");
	this->menu[0].setPosition(sf::Vector2f(460, 450));
	this->menu[0].setCharacterSize(80);
	this->menu[0].setOutlineThickness(1.5);

	this->menu[1].setFont(this->font);
	this->menu[1].setFillColor(sf::Color::White);
	this->menu[1].setString("SCOREBOARD");
	this->menu[1].setPosition(sf::Vector2f(800, 450));
	this->menu[1].setCharacterSize(80);
	this->menu[1].setOutlineThickness(1.5);

	this->menu[2].setFont(this->font);
	this->menu[2].setFillColor(sf::Color::White);
	this->menu[2].setString("ABOUT");
	this->menu[2].setPosition(sf::Vector2f(1300, 450));
	this->menu[2].setCharacterSize(80);
	this->menu[2].setOutlineThickness(1.5);

}



MainMenu::~MainMenu()
{
}

void MainMenu::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	//cout << "draw" << endl;
	window.draw(backgroundSprite);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}

	//window.draw(backgroundSprite);
	//this->initAnimation();
	
}


void MainMenu::initTexture()
{
	this->backgroundTexture.loadFromFile("images/MainMenu.png");
}

void MainMenu::initSprite()
{
	this->backgroundSprite.setTexture(this->backgroundTexture);
	this->currentFrame = sf::IntRect(0, 0, 1920, 1080);
	this->backgroundSprite.setTextureRect(this->currentFrame);
}

void MainMenu::updateMouseInput(sf::RenderWindow& window)
{
	this->mousePosition = sf::Mouse::getPosition(window);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		if (menu[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
		{
			this->menu[i].setFillColor(sf::Color::Magenta);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				handleMouseClick(i);
			}
		}
		else
			this->menu[i].setFillColor(sf::Color::White);

	}
}

void MainMenu::initAnimation()
{
	if (clock.getElapsedTime().asSeconds() >= 2.0f)
	{
		this->currentFrame.left += 1920.0f;
		if (currentFrame.left >= 3840.0f)
		{
			this->currentFrame.left = 0;
		}
		this->clock.restart();
		this->backgroundSprite.setTextureRect(this->currentFrame);
	}
}

void MainMenu::handleMouseClick(int selectedItemIndex)
{
	switch (selectedItemIndex)
	{
	case 0:
		this->menuState = "Playing";
		std::cout << "Start Click" << std::endl;
		break;
	case 1:
		this->menuState = "Scoreboard";
		std::cout << "Scoreboard Click" << std::endl;
		break;
	case 2:
		this->menuState = "About";
		std::cout << "About Click" << std::endl;
		break;
	default:
		break;

	}
}

std::string MainMenu::getMenuState() const
{
	return menuState;
}
