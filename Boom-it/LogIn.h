#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

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
	

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Vector2i mousePosition;


	void initTexture();
	void initSprite();
	sf::FloatRect textRect;
	
public:
	LogIn();
	~LogIn();

	void draw(sf::RenderWindow& window);
	void updateMouseInput(sf::RenderWindow& window);
	std::string checkState;
	std::string playerName;
	std::string playerNameOutput();

	void loadPlayerData();

};

