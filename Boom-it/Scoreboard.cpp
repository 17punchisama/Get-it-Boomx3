#include "Scoreboard.h"

Scoreboard::Scoreboard() {
    if (!font.loadFromFile("fonts/VCR_OSD_MONO_1.001.ttf")) {
        std::cout << "Can't Open VCR font" << std::endl;
    }

    this->texture.loadFromFile("images/scoreboard.png");
    this->sprite.setTexture(this->texture);

    backText.setFont(this->font);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(sf::Vector2f(800, 970));
    backText.setCharacterSize(50);
    backText.setOutlineThickness(1.5);
    backText.setString("Back To Home");

    // อย่าลืมเรียก loadTopPlayers() เพื่อโหลดข้อมูล
    loadTopPlayers();
}

void Scoreboard::loadTopPlayers() {
    // Code for loading top players' scores from "scores.txt"
    std::vector<std::pair<std::string, int>> scores;

    std::ifstream inputFile("scores.txt");
    if (inputFile.is_open()) {
        std::string name;
        int score;
        while (inputFile >> name >> score) {
            scores.push_back(std::make_pair(name, score));
        }
        inputFile.close();
    }
    else {
        std::cerr << "can't open scores.txt" << std::endl;
        return;
    }

    // Sort scores from highest to lowest
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    // Set the top 5 players' names and scores
    std::string topPlayersString = "Top 5 Players:\n";
    for (size_t i = 0; i < 5 && i < scores.size(); ++i) {
        topPlayersText[i].setFont(font);
        topPlayersText[i].setCharacterSize(80);
        topPlayersText[i].setFillColor(sf::Color::White);
        topPlayersText[i].setString(scores[i].first + +"  " + "Score " + std::to_string(scores[i].second));
        topPlayersText[i].setOutlineThickness(2);

        sf::FloatRect textBounds = topPlayersText[i].getLocalBounds();
        float centerX = (1920 - textBounds.width) / 2;
        float centerY = 350 + i * 100; // Adjust the position as needed
        topPlayersText[i].setPosition(centerX, centerY);
    }
}



void Scoreboard::draw(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);

    window.draw(sprite);

    for (int i = 0; i < 5; i++)
    {
        window.draw(topPlayersText[i]);
    }
    

    // Draw the "Back To Home" text
    window.draw(backText);


}

void Scoreboard::updateMouseInput(sf::RenderWindow& window) {
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
