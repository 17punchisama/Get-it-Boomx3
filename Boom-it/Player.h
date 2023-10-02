#pragma once

enum PLAYER_ANIMATION_STATES {IDLE = 0, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "HeartBar.h"
#include "Bomb.h"

//#include "Bomb.h"
class Bomb;

class Player
{
private:
	sf::RenderWindow* window;
	sf::Texture textureHolding;
	sf::Sprite spriteHoding;

	sf::Texture texture;
	sf::Sprite	sprite;
	sf::Vector2f previousPosition;

	std::vector<Bomb> bombs;

	//Animation
	sf::IntRect currentFrame;

	sf::Clock animationTimer;

	float movementSpeed;
	float yOffset;
	float xOffset;

	Bomb bomb;
	HeartBar heartBar;

	void initVariable();
	void initShape();
	void initAnimations();

public:
	Player(float x = 0.0f, float y = 0.0f);
	~Player();

	short animationState;
	bool checkCollision(const Bomb& bomb);
	void updateAnimation();
	void setPosition(float x, float y);
	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
	sf::Vector2f getPosition() const;
};