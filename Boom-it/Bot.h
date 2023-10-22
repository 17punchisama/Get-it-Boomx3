#ifndef BOT_H
#define BOT_H

#include <utility>
#include <iostream>

#include <SFML/Graphics.hpp>

class Bot {
public:
    Bot();
    void move(const std::string& direction);
    void approachPlayer(std::pair<int, int> playerPosition);
    std::pair<int, int> getPosition() const;

    void render(sf::RenderWindow* window);

private:
    std::pair<int, int> position;
};

#endif

