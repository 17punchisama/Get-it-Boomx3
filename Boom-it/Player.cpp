#include "Player.h"


bool Player::checkCollision(const Bomb& bomb)
{
	sf::FloatRect playerBounds = this->sprite.getGlobalBounds();
	sf::FloatRect bombBounds = bomb.getGlobalBounds();

	if (playerBounds.intersects(bombBounds))
	{
		sf::Vector2f newPosition = this->sprite.getPosition();

		// Calculate the horizontal and vertical overlap
		float xOverlap = std::min(playerBounds.left + playerBounds.width, bombBounds.left + bombBounds.width) -
			std::max(playerBounds.left, bombBounds.left);
		float yOverlap = std::min(playerBounds.top + playerBounds.height, bombBounds.top + bombBounds.height) -
			std::max(playerBounds.top, bombBounds.top);

		// Adjust the position based on the overlap
		if (xOverlap < yOverlap)
		{
			// Horizontal overlap is smaller, adjust horizontally
			if (playerBounds.left < bombBounds.left)
			{
				// Character is to the left of the bomb, place at the left edge
				newPosition.x = bombBounds.left - playerBounds.width;
			}
			else
			{
				// Character is to the right of the bomb, place at the right edge
				newPosition.x = bombBounds.left + bombBounds.width;
			}
		}
		else
		{
			// Vertical overlap is smaller or equal, adjust vertically
			if (playerBounds.top < bombBounds.top)
			{
				// Character is above the bomb, place at the top edge
				newPosition.y = bombBounds.top - playerBounds.height;
			}
			else
			{
				// Character is below the bomb, place at the bottom edge
				newPosition.y = bombBounds.top + bombBounds.height;
			}
		}

		// Set the character's position to the new calculated position
		this->sprite.setPosition(newPosition);

		return true; // Collision detected
	}

	return false; // No collision detected
}


void Player::initVariable()
{
	this->movementSpeed = 2.f;
	this->animationState = PLAYER_ANIMATION_STATES::IDLE;
	this->previousPosition = this->sprite.getPosition();
}

void Player::initShape()
{
	//edit player character after this !!
	this->texture.loadFromFile("images/Player-Choerry.png");
	this->sprite.setTexture(texture);
	this->currentFrame = sf::IntRect(0, 100, 50, 100);
	this->sprite.setPosition(100, 100);
}

void Player::initAnimations()
{
	this->sprite.setTextureRect(this->currentFrame);
}

Player::Player(float x, float y)
{
	this->sprite.setPosition(x, y);
	this->spriteHoding.setPosition(x, y);
	this->initVariable();
	this->initShape();
	this->initAnimations();
	this->animationTimer.restart();
	this->heartBar = HeartBar(x, y);
}

Player::~Player()
{
}

void Player::updateAnimation()
{
	//idle animation
	if (animationState == PLAYER_ANIMATION_STATES::IDLE)
	{
			this->currentFrame.left = 50.0f;
			this->sprite.setTextureRect(this->currentFrame);
	}
	//movement animation
	else if (animationState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (animationTimer.getElapsedTime().asSeconds() >= 0.17f)
		{
			this->currentFrame.top = 0.0f;
			this->currentFrame.left += 50.0f;
			if (currentFrame.left >= 150.0f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (animationState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (animationTimer.getElapsedTime().asSeconds() >= 0.17f)
		{
			this->currentFrame.top = 300.0f;
			this->currentFrame.left += 50.0f;
			if (currentFrame.left >= 150.0f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (animationState == PLAYER_ANIMATION_STATES::MOVING_UP)
	{
		if (animationTimer.getElapsedTime().asSeconds() >= 0.17f)
		{
			this->currentFrame.top = 200.0f;
			this->currentFrame.left += 50.0f;
			if (currentFrame.left >= 150.0f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (animationState == PLAYER_ANIMATION_STATES::MOVING_DOWN)
	{
		if (animationTimer.getElapsedTime().asSeconds() >= 0.17f)
		{
			this->currentFrame.top = 100.0f;
			this->currentFrame.left += 50.0f;
			if (currentFrame.left >= 150.0f)
			{
				this->currentFrame.left = 0;
			}
			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
}


sf::Vector2f Player::getPosition() const
{
	return sprite.getPosition();
}


void Player::updateInput()
{
	//Keyboard input
	
	//Left
	this->animationState = PLAYER_ANIMATION_STATES::IDLE;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->sprite.move(-this->movementSpeed, 0.f);
		this->animationState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->sprite.move(this->movementSpeed, 0.f);
		this->animationState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->sprite.move(0.f, -this->movementSpeed);
		this->animationState = PLAYER_ANIMATION_STATES::MOVING_UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->sprite.move(0.f, this->movementSpeed);
		this->animationState = PLAYER_ANIMATION_STATES::MOVING_DOWN;
	}

}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//Left
	if (this->sprite.getGlobalBounds().left <= 0.f)
		this->sprite.setPosition(0.f, this->sprite.getGlobalBounds().top);
	//Right
	else if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target->getSize().x)
		this->sprite.setPosition(target->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
	//Top
	if (this->sprite.getGlobalBounds().top <= 0.f)
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, 0.f);
	//Bottom
	else if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= target->getSize().y)
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, target->getSize().y - this->sprite.getGlobalBounds().height);
}

void Player::update(const sf::RenderTarget* target)
{
	this->updateInput();

	//Update Animation
	this->updateAnimation();

	//Window bounds collision
	this->updateWindowBoundsCollision(target);

	this->heartBar.update(target);

}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	this->heartBar.render(target);
}


