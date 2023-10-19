#include "About.h"

About::About()
{
	if (!font.loadFromFile("fonts/VCR_OSD_MONO_1.001.ttf"))
	{
		std::cout << "Can't Open VCR font" << std::endl;
	}

	this->Text.setFont(this->font);
	this->Text.setFillColor(sf::Color::White);
	this->Text.setPosition(sf::Vector2f(800, 950));
	this->Text.setCharacterSize(40);
	this->Text.setString("Back To Home");
}

About::~About()
{
}

void About::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	window.draw(Text);
}

void About::updateMouseInput(sf::RenderWindow& window)
{
	this->mousePosition = sf::Mouse::getPosition(window);

	if (Text.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
	{
		this->Text.setFillColor(sf::Color::Magenta);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->checkState = "Home";
		}
	}
	else
		this->Text.setFillColor(sf::Color::White);
}
