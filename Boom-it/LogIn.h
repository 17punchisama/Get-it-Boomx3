#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class LogIn
{
private:
	sf::Font font;
	sf::Text nextState;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Vector2i mousePosition;

	void initTexture();
	void initSprite();
	void handleMouseClick();
	
public:
	LogIn();
	~LogIn();

	void draw(sf::RenderWindow& window);
	void updateMouseInput(sf::RenderWindow& window);
	std::string checkState;
};

