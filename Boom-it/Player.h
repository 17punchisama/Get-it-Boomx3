#pragma once

enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>

class Player
{
private:
	int hp;
	int hpMax;
	
std::string playerName;

	int points;
	sf::RenderWindow* window;
	sf::Texture textureHolding;
	sf::Sprite spriteHoding;

	sf::Texture texture;
	sf::Sprite	sprite;
	sf::Vector2f previousPosition;

	//Animation
	sf::IntRect currentFrame;

	sf::Clock animationTimer;

	float movementSpeed;
	float yOffset;
	float xOffset;

	void initVariable();
	void initShape();
	void initAnimations();

public:
	Player(float x = 0.0f, float y = 0.0f);
	~Player();

	void loseHp(int amount);

	sf::FloatRect getBounds() const;

	long long score = 0;;

	short animationState;
	void updateAnimation();
	void setPosition(float x, float y);
	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

	void takeDamage(int damage);
	void addPoints(int points);
	void subtractPoints(int points);
	void heal(int amount);

	int getScore() const;
	int getHp() const;

	std::string previousState;

	sf::Vector2f getPosition() const;

	void writeDataToFile();
	void setPlayerNameAndWriteToFile(const std::string& newName);
	void reset();
};