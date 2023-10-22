#include "Bot.h"

Bot::Bot() : position(std::make_pair(0, 0)) {}

void Bot::move(const std::string& direction) {
    if (direction == "up") {
        position.second++;
    }
    else if (direction == "down") {
        position.second--;
    }
    else if (direction == "left") {
        position.first--;
    }
    else if (direction == "right") {
        position.first++;
    }
}

void Bot::approachPlayer(std::pair<int, int> playerPosition) {
    int dx = playerPosition.first - position.first;
    int dy = playerPosition.second - position.second;

    if (dx > 0) {
        move("right");
    }
    else if (dx < 0) {
        move("left");
    }

    if (dy > 0) {
        move("up");
    }
    else if (dy < 0) {
        move("down");
    }
}

std::pair<int, int> Bot::getPosition() const {
    return position;
}

void Bot::render(sf::RenderWindow* window) {
    // สร้างรูปภาพสำหรับบอท (ตัวอย่างเช่น: sprite)
    sf::RectangleShape botShape(sf::Vector2f(30, 30)); // สร้างรูปร่างสี่เหลี่ยมลักษณะของบอท
    botShape.setFillColor(sf::Color::Red); // ตั้งสีของบอท

    // ตั้งตำแหน่งของรูปร่างของบอท
    botShape.setPosition(position.first, position.second);

    // แสดงรูปร่างของบอทบนหน้าต่าง
    window->draw(botShape);
}
