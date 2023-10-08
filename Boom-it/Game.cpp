#include "Game.h"

void Game::changeGameState(GameState newState)
{
    this->gameState = newState;
}

void Game::initVariables()
{
    this->endGame = false;
    this->canPlaceBomb = true;
    this->isBombExploded = false;
    this->gameState = GameState::MainMenu;
}

void Game::initWindow()
{
    this->texture.loadFromFile("images/bg.JPEG");
    this->sprite.setTexture(texture);

    sf::VideoMode videoMode(1920, 1080);

    window.create(videoMode, "GET IT BOOM BOOM BOOM !!", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(144);

    mainMenu.initTexture();
    mainMenu.initSprite();
}

void Game::initTextures()
{
    // Initialize other textures if needed
}

void Game::initInput()
{
    // Handle input initialization if necessary
}

Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    // Deallocate any resources if necessary
}

const bool Game::running() const
{
    return this->window.isOpen();
}

void Game::pollEvents()
{
    while (window.pollEvent(sfmlEvent))
    {
        switch (sfmlEvent.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (sfmlEvent.key.code == sf::Keyboard::Escape)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canPlaceBomb)
            {
                // Check the player's animation state and place a bomb accordingly
                switch (player.animationState) {
                case PLAYER_ANIMATION_STATES::MOVING_LEFT:
                    bombs.emplace_back(player.getPosition().x - 50, player.getPosition().y);
                    isBombExploded = false;
                    canPlaceBomb = false;
                    break;
                case PLAYER_ANIMATION_STATES::MOVING_RIGHT:
                    bombs.emplace_back(player.getPosition().x + 50, player.getPosition().y);
                    isBombExploded = false;
                    canPlaceBomb = false;
                    break;
                case PLAYER_ANIMATION_STATES::MOVING_UP:
                    bombs.emplace_back(player.getPosition().x - 15, player.getPosition().y - 70);
                    isBombExploded = false;
                    canPlaceBomb = false;
                    break;
                case PLAYER_ANIMATION_STATES::MOVING_DOWN:
                    bombs.emplace_back(player.getPosition().x - 15, player.getPosition().y + 50);
                    isBombExploded = false;
                    canPlaceBomb = false;
                    break;
                default:
                    bombs.emplace_back(player.getPosition().x, player.getPosition().y);
                    isBombExploded = false;
                    canPlaceBomb = false;
                    break;
                }
            }
        }
    }
}

void Game::updateMainMenu()
{
    // Update and render the Main Menu
    mainMenu.updateMouseInput(window);

    clickedMenuState = mainMenu.getMenuState();

    if (clickedMenuState == "Playing")
    {
        //std::cout << "Playing rendering" << std::endl;
        gameState = GameState::LogIn;
    }
    if (clickedMenuState == "Scoreboard")
    {
        gameState = GameState::Scoreboard;
    }
    if (clickedMenuState == "About")
    {
        gameState = GameState::About;
    }
    mainMenu.draw(window);
    window.display();
}

void Game::updatePlaying()
{
    // Update game logic when in the Playing state
    this->player.update(&window);

    for (auto it = bombs.begin(); it != bombs.end();)
    {
        it->update();
        if (this->player.checkCollision(*it))
        {
            // Handle player collision with bombs
        }
        if (it->shouldExplode())
        {
            it = bombs.erase(it);
            isBombExploded = true;
            canPlaceBomb = true;
        }
        else
        {
            it++;
        }
    }

    window.draw(sprite);

    player.render(&window);
    heartBar.render(&window);

    for (const Bomb& bomb : bombs)
    {
        if (!bomb.shouldExplode())
        {
            bomb.render(&window);
        }
    }

    for (const Bomb& bomb : bombs)
    {
        if (bomb.shouldExplode())
        {
            bomb.renderEffect(&window);
        }
    }

    window.display();
}

void Game::updateLogIn()
{
    login.updateMouseInput(window);

    if (login.checkState == "next")
    {
        gameState = GameState::Playing;
    }

    login.draw(window);
    window.display();
}

void Game::update()
{
    this->pollEvents();

    // Check the game state and perform actions accordingly
    switch (gameState) {
    case GameState::MainMenu:
        this->updateMainMenu();
        break;
    case GameState::Playing:
        this->updatePlaying();
        break;
    case GameState::LogIn:
        this->updateLogIn();
        break;
    }
}

void Game::renderMainMenu()
{
    // Render the Main Menu
    mainMenu.draw(window);
    window.display();
}

void Game::renderPlaying()
{
    window.draw(sprite);

    player.render(&window);
    heartBar.render(&window);

    for (const Bomb& bomb : bombs)
    {
        if (!bomb.shouldExplode())
        {
            bomb.render(&window);
        }
    }

    for (const Bomb& bomb : bombs)
    {
        if (bomb.shouldExplode())
        {
            bomb.renderEffect(&window);
        }
    }

    window.display();
}

void Game::renderLogIn()
{
    login.draw(window);
    window.display();
}

void Game::render()
{

    window.clear();

    // Check the game state and choose the appropriate rendering function
    switch (gameState) {
    case GameState::MainMenu:
        this->renderMainMenu();
        break;
    case GameState::Playing:
        this->renderPlaying();
        break;
    case GameState::LogIn:
        this->renderLogIn();
    }
}