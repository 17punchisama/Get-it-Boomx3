#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class About
{
private:
	sf::Text Text;
	sf::Font font;

	sf::Text headline;
	sf::Font headlineFont;

	sf::Texture aboutTexture;
	sf::Sprite aboutSprite;

	sf::Vector2i mousePosition;
	
public:
	About();
	~About();

	void draw(sf::RenderWindow& window);
	void updateMouseInput(sf::RenderWindow& window);
	std::string checkState;
};

