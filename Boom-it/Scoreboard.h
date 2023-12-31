#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

class Scoreboard
{
private:
	//sf::RenderWindow& window;
	sf::Text backText;
	sf::Font font;
	sf::Text topPlayersText[5];

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i mousePosition;

public:
	Scoreboard();
	//~Scoreboard();

	void draw(sf::RenderWindow& window);
	void updateMouseInput(sf::RenderWindow& window);
	std::string checkState;
	void loadTopPlayers();
};