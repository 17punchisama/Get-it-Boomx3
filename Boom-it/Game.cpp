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
    if (!menuMusic.openFromFile("sounds/odd-front.mp3"))
    {
        std::cout << "Failed to load music" << std::endl;
    }

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
                    bombs.emplace_back(player.getPosition().x - 70, player.getPosition().y);
                    isBombExploded = false;
                    canPlaceBomb = false;
                    break;
                case PLAYER_ANIMATION_STATES::MOVING_RIGHT:
                    bombs.emplace_back(player.getPosition().x + 30, player.getPosition().y);
                    isBombExploded = false;
                    canPlaceBomb = false;
                    break;
                case PLAYER_ANIMATION_STATES::MOVING_UP:
                    bombs.emplace_back(player.getPosition().x - 15, player.getPosition().y - 100);
                    isBombExploded = false;
                    canPlaceBomb = false;
                    break;
                case PLAYER_ANIMATION_STATES::MOVING_DOWN:
                    bombs.emplace_back(player.getPosition().x - 15, player.getPosition().y + 50);
                    isBombExploded = false;
                    canPlaceBomb = false;
                    break;
                case PLAYER_ANIMATION_STATES::IDLE:
                    if (player.previousState == "Left")
                    {
                        bombs.emplace_back(player.getPosition().x - 70, player.getPosition().y);
                        isBombExploded = false;
                        canPlaceBomb = false;
                    }
                    if (player.previousState == "Right")
                    {
                        bombs.emplace_back(player.getPosition().x + 30, player.getPosition().y);
                        isBombExploded = false;
                        canPlaceBomb = false;
                    }
                    if (player.previousState == "Up")
                    {
                        bombs.emplace_back(player.getPosition().x - 15, player.getPosition().y - 100);
                        isBombExploded = false;
                        canPlaceBomb = false;
                    }
                    if (player.previousState == "Down")
                    {
                        bombs.emplace_back(player.getPosition().x - 15, player.getPosition().y + 50);
                        isBombExploded = false;
                        canPlaceBomb = false;
                    }
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

    clickedMenuState = mainMenu.menuState;

    if (clickedMenuState == "Playing")
    {
        //std::cout << "Playing rendering" << std::endl;
        gameState = GameState::LogIn;
        mainMenu.menuState = "";
    }
    if (clickedMenuState == "Scoreboard")
    {
        gameState = GameState::Scoreboard;
        mainMenu.menuState = "";
    }
    if (clickedMenuState == "About")
    {
        gameState = GameState::About;
        mainMenu.menuState = "";
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
        login.checkState = "";
    }
    if (login.checkState == "back")
    {
        gameState = GameState::MainMenu;
        login.checkState = "";
    }

    login.draw(window);
    window.display();
}

void Game::updateAbout()
{
    about.updateMouseInput(window);

    if (about.checkState == "Home")
    {
        gameState = GameState::MainMenu;
        mainMenu.menuState = "";
    }

    about.draw(window);
    window.display();
}

void Game::update()
{
    this->pollEvents();

    // Check the game state and perform actions accordingly
    if (gameState == GameState::MainMenu)
    {
        this->updateMainMenu();
        
        //std::cout << 1 << std::endl;
    }
    if (gameState == GameState::Playing)
    {
        this->updatePlaying();
        this->menuMusic.stop();
    }
    if (gameState == GameState::LogIn)
    {
        this->updateLogIn();
    }
    if (gameState == GameState::About)
    {
        this->updateAbout();
        //std::cout << 2 << std::endl;
    }
    
    if (gameState == GameState::About || gameState == GameState::Scoreboard || gameState == GameState::MainMenu || gameState == GameState::LogIn)
    {
        this->menuMusic.play();
    }
}

void Game::renderMainMenu()
{
    // Render the Main Menu
    //window.clear();
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

void Game::renderAbout()
{
    //window.clear();
    about.draw(window);
    window.display();
}

void Game::render()
{

    window.clear();

    if (gameState == GameState::MainMenu)
    {
        this->renderMainMenu();
       // std::cout << 1 << std::endl;
    }
    else if (gameState == GameState::Playing)
    {
        this->renderPlaying();
    }
    else if (gameState == GameState::LogIn)
    {
        this->renderLogIn();
    }
    else if (gameState == GameState::About)
    {
        this->renderAbout();
    }
    // Check the game state and choose the appropriate rendering function

}