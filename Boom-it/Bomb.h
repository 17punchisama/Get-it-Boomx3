#ifndef BOMB_H

#define BOMB_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Bomb
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	sf::Sprite effectSprite;
	sf::Texture effectTexture;

	sf::Clock clock;
	sf::Window* window;
	sf::IntRect currentFrame;
	sf::IntRect bombFrame;

	float explosionTine;

	bool exploded;

	void initTexture();
	void initSprite();

	void initTextureEffect();
	void initSpriteEffect();

	void updateInput();
	void explodedCondition();
	void bombAnimation();

public:
	Bomb(float x, float y);
	Bomb();
	~Bomb();

	sf::FloatRect getGlobalBounds() const;
	void updateBombAnimation();
	void update();
	void render(sf::RenderTarget* target) const;
	bool shouldExplode() const;
	void setPosition(sf::Vector2f) const;
	void renderEffect(sf::RenderTarget* target) const;
};

#endif // !BOMB_H