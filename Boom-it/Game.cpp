#include "Game.h"

void Game::changeGameState(GameState newState)
{
    this->gameState = newState;
}

void Game::initVariables()
{
    this->endGame = false;
    this->gameState = GameState::MainMenu;

    this->spawnTimerMax = 50.f;
    //this->playerNameIn = "";
}

void Game::initWindow()
{
    this->texture.loadFromFile("images/gameplay-page.png");
    this->sprite.setTexture(texture);

    sf::VideoMode videoMode(1920, 1080);

    window.create(videoMode, "GET IT BOOM BOOM BOOM !!", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(144);

    mainMenu.initTexture();
    mainMenu.initSprite();

    if (!menuMusic.openFromFile("sounds/odd-front.mp3"))
    {
        std::cout << "Failed to load music" << std::endl;
    }

    menuMusic.setLoop(true);
    menuMusic.setVolume(30);
    menuMusic.play();
}

void Game::initTextures()
{
    // Initialize other textures if needed
}

void Game::initText()
{
    font.loadFromFile("fonts/VCR_OSD_MONO_1.001.ttf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(50, 500);  // ตำแหน่ง X, Y ของคะแนนบนหน้าต่าง
    //scoreText.setString("Score: " + std::to_string(player.getScore()));

    hpText.setFont(font);
    hpText.setCharacterSize(40);
    hpText.setFillColor(sf::Color::Black);
    hpText.setPosition(50, 550);  // ตำแหน่ง X, Y ของคะแนนบนหน้าต่าง
    //hpText.setString("Hp: " + std::to_string(player.getHp()));


    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(50, 350);
    text.setString("PLAYER NAME" );
    text.setOutlineThickness(1.5);

    std::cout << "Player Name: " << playerNameIn << std::endl;

}

void Game::initInput()
{
    // Handle input initialization if necessary
}

Game::Game()
{
    this->initVariables();
    this->initWindow();
 
    if (!collisionBuffer.loadFromFile("sounds/Hurt.wav")) {
        std::cout << "Failed to load music" << std::endl;
    }
    this->collisionSound.setBuffer(collisionBuffer);

    if (!completeBuffer.loadFromFile("sounds/Confirm.wav")) {
        std::cout << "Failed to load music" << std::endl;
    }
    this->completeSound.setBuffer(completeBuffer);

    if (!clickBuffer.loadFromFile("sounds/Click.wav")) {
        std::cout << "Failed to load music" << std::endl;
    }
    this->clickSound.setBuffer(clickBuffer);

    if (!cancelBuffer.loadFromFile("sounds/Cancel.wav")) {
        std::cout << "Failed to load music" << std::endl;
    }
    this->cancelSound.setBuffer(cancelBuffer);

    clock.restart();
    heartTime.restart();
    poisonTime.restart();
    itemSpawnTimer.restart();

    this->initText();
    //this->login.renderName(window);

    this->spawnTimerMaxCherries = 1.0f; // Initial maximum time for Cherries
    this->spawnTimerCherries = this->spawnTimerMaxCherries;

    this->spawnTimerMaxHeart = 5.0f; // Initial maximum time for Hearts
    this->spawnTimerHeart = this->spawnTimerMaxHeart;

    this->spawnTimerMaxPoison = 15.0f; // Initial maximum time for Poisons
    this->spawnTimerPoison = this->spawnTimerMaxPoison;

    // Call initItems to spawn initial items
    this->initItems();
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
                
            
        }
    }
}


void Game::initEnemies()
{
    this->spawnTimer += 1.f;

    if (this->spawnTimer >= this->spawnTimerMax)
    {
        this->enemies.push_back(new Enemy(this->window.getSize().x, rand() % (this->window.getSize().y - 80)));

        this->spawnTimer = 0.f;

        // เพิ่มความยากของเกม 
        this->spawnTimerMax -= 0.05f; // ลดเวลาเกิดศัตรูลง 1 เฟรม
        if (this->spawnTimerMax < 10.f) // ลองปรับค่าตามความเหมาะสม
        {
            this->spawnTimerMax = 10.f; // ไม่ให้ลดเวลาเกิดศัตรูเรื่อย ๆ มากเกินไป
        }
    }

    // ตรวจสอบตำแหน่ง x ของทุก Enemy
    unsigned counter = 0;
    while (counter < this->enemies.size())
    {
        Enemy* enemy = this->enemies[counter];

        enemy->update();

        if (enemy->getBounds().left <= 400.f)
        {
            // ลบ enemy ที่อยู่ที่ตำแหน่ง x <= 400
            delete enemy;
            this->enemies.erase(this->enemies.begin() + counter);
        }
        else
        {
            // ไม่มีการลบ enemy ที่ยังไม่อยู่ที่ตำแหน่ง x <= 400
            counter++;
        }
    }
}


void Game::initItems()
{
    this->items.push_back(new Item(0, 0, ItemType::Cherry));
     this->items.back()->setPosition(std::rand() % (1920 - 400) + 400, std::rand() % 1080);

    // Spawn Hearts
    this->items.push_back(new Item(0, 0, ItemType::Heart));
    this->items.back()->setPosition(std::rand() % (1920 - 500) + 500, std::rand() % 1080);

    // Spawn Poisons
    this->items.push_back(new Item(0, 0, ItemType::Poison));
    this->items.back()->setPosition(std::rand() % (1920 - 5100) + 510, std::rand() % 1080);

}


void Game::updateMainMenu()
{
    // Update and render the Main Menu
    mainMenu.updateMouseInput(window);

    clickedMenuState = mainMenu.menuState;

    if (clickedMenuState == "Playing")
    {
        clickSound.play();
        //std::cout << "Playing rendering" << std::endl;
        gameState = GameState::LogIn;
        
        mainMenu.menuState = "";
    }
    if (clickedMenuState == "Scoreboard")
    {
        clickSound.play();
        gameState = GameState::Scoreboard;
        mainMenu.menuState = "";
    }
    if (clickedMenuState == "About")
    {
        clickSound.play();
        gameState = GameState::About;
        mainMenu.menuState = "";
    }
    mainMenu.draw(window);
    window.display();
}

// ใน Game.cpp

// ในส่วนของ Game::updatePlaying()
void Game::updatePlaying()
{
    // Update game logic when in the Playing state
    this->player.update(&window);

    window.draw(sprite);

    player.render(&window);

    // Spawn Cherries
    this->spawnTimerCherries += this->clock.restart().asSeconds();
    if (this->spawnTimerCherries >= this->spawnTimerMaxCherries)
    {
        this->items.push_back(new Item(0, 0, ItemType::Cherry));
        this->items.back()->setPosition(std::rand() % (1920 - 400) + 400, std::rand() % 1080);
        this->spawnTimerCherries = 0.f;
    }




    this->spawnTimerHeart += this->heartTime.restart().asSeconds();
    if (this->spawnTimerHeart >= this->spawnTimerMaxHeart)
    {
        for (Item* item : this->items) {
            if (item->getType() == ItemType::Heart) {
                sf::Vector2f heartPosition = item->getPosition();
                std::cout << "Heart position: x=" << heartPosition.x << ", y=" << heartPosition.y << std::endl;
            }
        }
        // Spawn a Heart
        //std::cout << "Heart spawned at position: x=" << .x << ", y=" << heartPosition.y << std::endl;
        this->items.push_back(new Item(0, 0, ItemType::Heart));
        this->items.back()->setPosition(std::rand() % (1920 - 400) + 400, std::rand() % 1080);
        this->spawnTimerHeart = 0.f;
    }

    this->spawnTimerPoison += this->poisonTime.restart().asSeconds();
    if (this->spawnTimerPoison >= this->spawnTimerMaxPoison)
    {
        // Spawn a Poison
        this->items.push_back(new Item(0, 0, ItemType::Poison));
        this->items.back()->setPosition(std::rand() % (1920 - 400) + 400, std::rand() % 1080);
        this->spawnTimerPoison = 0.f;
    }


    for (Item* item : this->items) {
        item->render(&window);
    }

    for (Enemy* enemy : this->enemies)
    {
        enemy->render(&window);
    }
    
    window.draw(scoreText);
    window.draw(hpText);
    window.draw(text);
    window.draw(nameText);

    login.renderName(window);

    this->initEnemies();

    window.display();
}


void Game::updateLogIn()
{
    login.updateMouseInput(window);

    if (login.checkState == "next")
    {
        clickSound.play();
        gameState = GameState::Playing;
        playerNameIn = login.playerName;
        login.checkState = "";
    }
    if (login.checkState == "back")
    {
        clickSound.play();
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
        clickSound.play();
        gameState = GameState::MainMenu;
        about.checkState = "";
        mainMenu.menuState = "";
    }

    about.draw(window);
    window.display();
}

void Game::updateScoreboard()
{
    scoreboard.updateMouseInput(window);

    if (scoreboard.checkState == "Home")
    {
        clickSound.play();
        gameState = GameState::MainMenu;
        scoreboard.checkState = "";
    }
    scoreboard.draw(window);
    window.display();
}

void Game::updateGameOver()
{
    gameOver.updateMouseInput(window);

    if (gameOver.checkState == "Home")
    {
        clickSound.play();
        gameState = GameState::MainMenu;
        gameOver.checkState = "";
    }

    gameOver.draw(window);
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
        //this->menuMusic.stop();
    }
    if (gameState == GameState::LogIn)
    {
        this->updateLogIn();

        if (login.checkState == "next")
        {
            playerNameIn = login.playerName;
            player.setPlayerNameAndWriteToFile(playerNameIn);  // กำหนดชื่อและเขียนข้อมูลลงในไฟล์
            gameState = GameState::Playing;
            login.checkState = "";
        }
    }
    if (gameState == GameState::About)
    {
        this->updateAbout();
        //std::cout << 2 << std::endl;
    }
    if (gameState == GameState::Scoreboard)
    {
        this->updateScoreboard();
    }
    
    if (gameState == GameState::GameOver)
    {
        this->updateGameOver();
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
    //item.render(&window);
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (player.getBounds().intersects(enemies[i]->getBounds())) {
            // ทำตามความเสียหายของศัตรู
            collisionSound.play();
            player.takeDamage(enemies[i]->getDamage());

            // ลบศัตรูที่ชน
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
        }
    }

    // ใน Game.cpp ในฟังก์ชัน Game::updatePlaying()
    for (size_t i = 0; i < items.size(); ++i) {
        if (player.getBounds().intersects(items[i]->getBounds())) {
            ItemType itemType = items[i]->getType();
            if (itemType == ItemType::Cherry) {
                completeSound.play();
                // ทำตามการชนของ cherry
                player.addPoints(10);
            }
            else if (itemType == ItemType::Heart) {
                // ทำตามการชนของ heart
                completeSound.play();
                player.heal(10);
            }
            else if (itemType == ItemType::Poison) {
                // ทำตามการชนของ poison
                cancelSound.play();
                player.subtractPoints(50);
            }

            // ลบไอเทมที่ชน
            delete items[i];
            items.erase(items.begin() + i);

        }
    }
    if (player.getHp() <= 0) {
        std::cout << "Game Over" << std::endl;
        gameState = GameState::GameOver; 
        
        std::ofstream scoreFile("scores.txt", std::ios::app); // ใช้ std::ios::app เพื่อแต่ละครั้งที่เขียนจะไม่ลบข้อมูลเก่า
        if (scoreFile.is_open()) {
            scoreFile << login.playerName << " " << player.getScore() << std::endl;
            scoreFile.close();
        }
        else {
            std::cerr << "ไม่สามารถเปิดไฟล์ scores.txt ได้" << std::endl;
        }
        this->resetGame();
    }

    scoreText.setString("Score: " + std::to_string(player.getScore()));
    hpText.setString("Hp: " + std::to_string(player.getHp()));

    window.draw(scoreText);
    window.draw(hpText);
    window.draw(text);
    window.draw(nameText);
    login.renderName(window);
    

    for (Enemy* enemy : this->enemies) {
        enemy->render(&window);
    }

    for (Item* item : this->items) {
        item->render(&window);
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

void Game::renderScoreboard()
{
    scoreboard.draw(window);
    window.display();
}

void Game::renderGameOver()
{
    gameOver.draw(window);
    window.display();
}

void Game::resetGame()
{
    player.reset(); 
    enemies.clear();
    items.clear();
    login.playerName = "";
    playerNameIn = "";
    login.enteringName = false;
    login.playerNameText.setString("Enter Player Name");
    //this->initVariables();
    clickedMenuState = "";
    menuMusic.play();
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
    else if (gameState == GameState::Scoreboard)
    {
        this->renderScoreboard();
    }
    else if (gameState == GameState::GameOver)
    {
        this->renderGameOver();
    }
    // Check the game state and choose the appropriate rendering function

}

