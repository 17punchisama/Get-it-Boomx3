#pragma once

#include <SFML/Graphics.hpp>

class GameOver

{
private:
	sf::Text backText;
	sf::Font font;

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i mousePosition;

public:
	GameOver();
	void draw(sf::RenderWindow& window);
	void updateMouseInput(sf::RenderWindow& window);
	std::string checkState;

};

