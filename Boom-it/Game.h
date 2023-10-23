#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include "Player.h"
#include "MainMenu.h"
#include "LogIn.h"
#include "About.h"
#include "Scoreboard.h"
#include "Item.h"
#include "Enemy.h"
#include "Item.h"
#include "PlayerData.h"

enum class GameState {
    MainMenu,
    LogIn,
    Playing,
    Scoreboard,
    About,
    GameOver,
};


class Game
{
private:
    sf::RenderWindow window;
    sf::View statusView;

    bool endGame;
    bool canPlaceBomb;
    bool isBombExploded;

    unsigned points;
    int type;

    sf::Font font;
    sf::Text scoreText;
    sf::Text hpText;
    sf::Text nameText;
    sf::Text text;

    std::string playerNameIn = "";

    //Items
    float spawnTimerMaxCherries;
    float spawnTimerCherries = 0;

    float spawnTimerMaxHeart;
    float spawnTimerHeart = 0;

    float spawnTimerMaxPoison;
    float spawnTimerPoison = 0;

    float spawnTimer;
    float spawnTimerMax;

    bool itemSpawn = false;

    std::vector<Item*> items;

    std::vector<Enemy*> enemies;

    std::vector<PlayerData> players;

    sf::Clock clock;
    sf::Clock heartTime;
    sf::Clock poisonTime;

    sf::Clock itemSpawnTimer;
    sf::Event sfmlEvent;
    sf::Texture explosionTexture;
    sf::Sprite explosionSprite;
    sf::Texture texture;
    sf::Sprite sprite;

    Player player;

    MainMenu mainMenu;
    GameState gameState;
    LogIn login;
    About about;
    Scoreboard scoreboard;

    //Item item;

    sf::Music menuMusic;
    
    void initEnemies();
    void initItems();

    void initVariables();
    void initWindow();
    void initTextures();
    
    void initText();

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