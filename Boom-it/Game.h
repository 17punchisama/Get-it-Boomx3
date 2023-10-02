#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Bomb.h"
#include "HeartBar.h"
#include "MainMenu.h"

enum class GameState {
    MainMenu,
    LogIn,
    Tutorial,
    Playing,
    // เพิ่มสถานะอื่น ๆ ตามที่คุณต้องการ
};


class Game
{
private:
    sf::RenderWindow window;
    sf::View statusView;
    bool endGame;
    bool canPlaceBomb;
    bool isBombExploded;
    sf::Event sfmlEvent;
    sf::Texture explosionTexture;
    sf::Sprite explosionSprite;
    sf::Texture texture;
    sf::Sprite sprite;

    std::vector<Bomb> bombs;

    Player player;
    HeartBar heartBar;
    MainMenu mainMenu;
    GameState gameState;

    void changeGameState(GameState newState);
    void initVariables();
    void initWindow();
    void initTextures();
    void updateMainMenu();
    void updatePlaying();
    void renderMainMenu();
    void renderPlaying();

public:
    Game();
    ~Game();

    const bool running() const;
    void pollEvents();
    void update();
    void render();
    void initInput();
};