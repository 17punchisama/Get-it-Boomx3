#include "Scoreboard.h"

Scoreboard::Scoreboard()
{
	if (!font.loadFromFile("fonts/VCR_OSD_MONO_1.001.ttf"))
	{
		std::cout << "Can't Open VCR font" << std::endl;
	}

	this->backText.setFont(this->font);
	this->backText.setFillColor(sf::Color::White);
	this->backText.setPosition(sf::Vector2f(800, 950));
	this->backText.setCharacterSize(50);
	this->backText.setOutlineThickness(1.5);
	this->backText.setString("Back To Home");
}

Scoreboard::~Scoreboard()
{

}

void Scoreboard::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);

	window.draw(backText);
}

void Scoreboard::updateMouseInput(sf::RenderWindow& window)
{
	this->mousePosition = sf::Mouse::getPosition(window);

	if (backText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
	{
		this->backText.setFillColor(sf::Color::Yellow);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->checkState = "Home";
		}
	}
	else
		this->backText.setFillColor(sf::Color::White);
}
