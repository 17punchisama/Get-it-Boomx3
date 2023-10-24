#include "About.h"

About::About()
{
	if (!font.loadFromFile("fonts/VCR_OSD_MONO_1.001.ttf"))
	{
		std::cout << "Can't Open VCR font" << std::endl;
	}

	if (!headlineFont.loadFromFile("fonts/VT323-Regular.ttf"))
	{

	}

	if (!aboutTexture.loadFromFile("images/about-me.png"))
	{
		std::cout << "Can't Open about me font" << std::endl;
	}

	this->aboutSprite.setTexture(this->aboutTexture);

	this->Text.setFont(this->font);
	this->Text.setFillColor(sf::Color::White);
	this->Text.setPosition(sf::Vector2f(800, 970));
	this->Text.setCharacterSize(50);
	this->Text.setOutlineThickness(1.5);
	this->Text.setString("Back To Home");

	this->headline.setFont(this->headlineFont);
	this->headline.setFillColor(sf::Color::Magenta);
	this->headline.setPosition(sf::Vector2f(730, 20));
	this->headline.setCharacterSize(150);
	this->headline.setOutlineThickness(1.5);
	this->headline.setString("About Me");
}

About::~About()
{
}

void About::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Black);
	window.draw(aboutSprite);
	window.draw(headline);
	window.draw(Text);
}

void About::updateMouseInput(sf::RenderWindow& window)
{
	this->mousePosition = sf::Mouse::getPosition(window);

	if (Text.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
	{
		this->Text.setFillColor(sf::Color::Yellow);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->checkState = "Home";
		}
	}
	else
		this->Text.setFillColor(sf::Color::White);
}
