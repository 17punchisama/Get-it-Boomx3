#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Bomb.h"
#include "HeartBar.h"
#include "MainMenu.h"
#include "LogIn.h"
#include "About.h"
#include "Scoreboard.h"

enum class GameState {
    MainMenu,
    LogIn,
    Playing,
    Scoreboard,
    About,
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
    LogIn login;
    About about;
    Scoreboard scoreboard;

    sf::Music menuMusic;
    void initVariables();
    void initWindow();
    void initTextures();

    void updateMainMenu();
    void updatePlaying();
    void updateLogIn();
    void updateAbout();
    void updateScoreboard();

    void renderMainMenu();
    void renderPlaying();
    void renderLogIn();
    void renderAbout();
    void renderScoreboard();

    int selectedItemIndex;
    std::string clickedMenuState;

public:
    Game();
    ~Game();

    const bool running() const;
    void pollEvents();
    void update();
    void render();
    void initInput();

    void changeGameState(GameState newState);
};