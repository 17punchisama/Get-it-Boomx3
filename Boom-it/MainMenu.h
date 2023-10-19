#pragma once

#define MAX_NUMBER_OF_ITEMS 3

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MainMenu
{
public:
	MainMenu();
	//MainMenu(float width, float height);
	~MainMenu();

	int selectedItemIndex;

	void draw(sf::RenderWindow& window);
	void initTexture();
	void initSprite();
	void updateMouseInput(sf::RenderWindow& window);
	void handleMouseClick(int selectedItemIndex);

	std::string menuState;
	//std::string getMenuState() const;

private:
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Music menuMusic;
	sf::IntRect currentFrame;
	sf::Clock clock;
	sf::Event event;

	sf::RenderWindow* menuwindow;
	sf::Vector2i mousePosition;

	void initAnimation();
	
};