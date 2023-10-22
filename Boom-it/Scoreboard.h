#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Scoreboard
{
private:
	sf::Text backText;
	sf::Font font;

	sf::Vector2i mousePosition;

public:
	Scoreboard();
	~Scoreboard();

	void draw(sf::RenderWindow& window);
	void updateMouseInput(sf::RenderWindow& window);
	std::string checkState;
};