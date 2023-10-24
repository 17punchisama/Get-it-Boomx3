#include "GameOver.h"

GameOver::GameOver()
{
    if (!font.loadFromFile("fonts/VCR_OSD_MONO_1.001.ttf")) {
        //std::cout << "Can't Open VCR font" << std::endl;
    }

    this->texture.loadFromFile("images/gameover.png");
    this->sprite.setTexture(this->texture);

    backText.setFont(this->font);
    backText.setFillColor(sf::Color::Cyan);
    backText.setPosition(sf::Vector2f(610, 600));
    backText.setCharacterSize(100);
    backText.setOutlineThickness(1.5);
    backText.setString("Back To Home");
}

void GameOver::draw(sf::RenderWindow& window)
{
    window.clear();

    window.draw(sprite);
    window.draw(backText);
}

void GameOver::updateMouseInput(sf::RenderWindow& window)
{
    this->mousePosition = sf::Mouse::getPosition(window);

    if (backText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition))) {
        this->backText.setFillColor(sf::Color::Yellow);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->checkState = "Home";
        }
    }
    else {
        this->backText.setFillColor(sf::Color::White);
    }
}
