#include "Player.h"

void Player::initVariable()
{
	this->movementSpeed = 4.f;
	this->animationState = PLAYER_ANIMATION_STATES::IDLE;
	this->previousPosition = this->sprite.getPosition();
	this->score = 0;
	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Player::initShape()
{
	//edit player character after this !!
	this->texture.loadFromFile("images/Player-Choerry.png");
	this->sprite.setTexture(texture);
	this->currentFrame = sf::IntRect(0, 100, 50, 100);
	this->sprite.setPosition(400, 100);
	this->sprite.setScale(1.25f, 1.25f);
}

void Player::initAnimations()
{
	this->sprite.setTextureRect(this->currentFrame);
}

Player::Player(float x, float y)
{
	this->playerName = "";
	this->sprite.setPosition(x, y);
	this->initVariable();
	this->initShape();
	this->initAnimations();
	this->animationTimer.restart();
}


Player::~Player()
{
}

void Player::loseHp(int amount)
{
	hp -= amount;
	if (hp < 0) 
		hp = 0;
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
		this->previousState = "Left";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->sprite.move(this->movementSpeed, 0.f);
		this->animationState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
		this->previousState = "Right";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->sprite.move(0.f, -this->movementSpeed);
		this->animationState = PLAYER_ANIMATION_STATES::MOVING_UP;
		this->previousState = "Up";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->sprite.move(0.f, this->movementSpeed);
		this->animationState = PLAYER_ANIMATION_STATES::MOVING_DOWN;
		this->previousState = "Down";
	}

}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//Left
	if (this->sprite.getGlobalBounds().left <= 400.f)
		this->sprite.setPosition(400.f, this->sprite.getGlobalBounds().top);
	//Right
	else if (this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width >= target->getSize().x)
		this->sprite.setPosition(target->getSize().x - this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().top);
	//Top
	if (this->sprite.getGlobalBounds().top <= 0.f)
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, 0.f);
	//Bottom
	else if (this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height >= 1080)
		this->sprite.setPosition(this->sprite.getGlobalBounds().left, target->getSize().y - this->sprite.getGlobalBounds().height);
}

void Player::update(const sf::RenderTarget* target)
{
	this->updateInput();

	//Update Animation
	this->updateAnimation();

	//Window bounds collision
	this->updateWindowBoundsCollision(target);


}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}

void Player::takeDamage(int damage) {
	hp -= damage;
	if (hp < 0) {
		hp = 0;
	}
}

void Player::addPoints(int points) {
	score += points;
	std::cout << "Score: " << score << std::endl;
}

void Player::subtractPoints(int points) {
	score -= points;
	if (score < 0) {
		score = 0;
	}
}

void Player::heal(int amount)
{
	hp += amount;
	if (hp > hpMax) {
		hp = hpMax; 
	}

	if (hp <= 0) {
		std::cout << "Game Over" << std::endl;
		exit(0); // จบเกม
	}
	std::cout << "Hp: " << hp << std::endl;
}


sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

int Player::getScore() const {
	return score;
}

int Player::getHp() const {
	return hp;
}

void Player::writeDataToFile()
{
	std::ofstream playerDataFile("player_data.txt");

	if (playerDataFile.is_open()) {
		playerDataFile << "Player Name: " << playerName << "\n";
		playerDataFile << "Score: " << score << "\n";
		playerDataFile.close();
	}
	else {
		std::cout << "Unable to open player_data.txt for writing" << std::endl;
	}
}

void Player::setPlayerNameAndWriteToFile(const std::string& newName) {
	playerName = newName;
	// บันทึกข้อมูลลงในไฟล์
	writeDataToFile();
}

void Player::reset()
{
	this->hp = 100;
	this->score = 0;
	this->sprite.setPosition(400.0f, 100.0f);
	this->currentFrame = sf::IntRect(0, 100, 50, 100);
}
