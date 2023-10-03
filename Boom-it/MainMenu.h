#pragma once

#define MAX_NUMBER_OF_ITEMS 3

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MainMenu
{
public:
	MainMenu();
	MainMenu(float width, float height);
	~MainMenu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void initTexture();
	void initSprite();


private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Music menuMusic;
	sf::IntRect currentFrame;
	sf::Clock clock;

	sf::Text texttest;

	void initAnimation();

};