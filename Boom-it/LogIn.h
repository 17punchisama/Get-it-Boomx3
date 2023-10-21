#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

class LogIn
{
private:
	sf::Font font;
	sf::Text nextState;
	sf::Text backState;
	sf::Text playerNameText;

	bool enteringName;
	bool keyStates[26];
	bool backspacePressed;

	int delayMilliseconds = 100;
	
	std::string playerName;
	

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

