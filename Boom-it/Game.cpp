#include "Game.h"

void Game::changeGameState(GameState newState)
{
    this->gameState = newState;
}

void Game::initVariables()
{
    this->endGame = false;
    this->gameState = GameState::MainMenu;

    this->spawnTimerMax = 20.f;
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
}

void Game::initTextures()
{
    // Initialize other textures if needed
}

void Game::initText()
{
    font.loadFromFile("fonts/VCR_OSD_MONO_1.001.ttf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(50, 450);  // ตำแหน่ง X, Y ของคะแนนบนหน้าต่าง
    //scoreText.setString("Score: " + std::to_string(player.getScore()));

    hpText.setFont(font);
    hpText.setCharacterSize(50);
    hpText.setFillColor(sf::Color::Black);
    hpText.setPosition(50, 500);  // ตำแหน่ง X, Y ของคะแนนบนหน้าต่าง
    //hpText.setString("Hp: " + std::to_string(player.getHp()));

  
    nameText.setFont(font);
    nameText.setCharacterSize(50);
    nameText.setFillColor(sf::Color::Magenta);
    nameText.setPosition(50, 400);
    nameText.setOutlineThickness(1.5);

    // อ่านชื่อผู้เล่นจากไฟล์ player_data.txt
    std::ifstream playDataFile("player_data.txt");
    if (playDataFile.is_open())
    {
        std::getline(playDataFile, playerNameIn);
        playDataFile.close();
    }
    else
    {
        std::cout << "Unable to open player_data.txt for reading" << std::endl;
    }

    nameText.setString(playerNameIn); 


    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(50, 350);
    text.setString("NAME" );
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
    if (!menuMusic.openFromFile("sounds/odd-front.mp3"))
    {
        std::cout << "Failed to load music" << std::endl;
    }
    clock.restart();
    heartTime.restart();
    poisonTime.restart();
    itemSpawnTimer.restart();

    this->initText();

    this->spawnTimerMaxCherries = .5f; // Initial maximum time for Cherries
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
        this->spawnTimerMax -= 0.1f; // ลดเวลาเกิดศัตรูลง 1 เฟรม
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

    this->initEnemies();

    window.display();
}


void Game::updateLogIn()
{
    login.updateMouseInput(window);

    if (login.checkState == "next")
    {
        gameState = GameState::Playing;
        playerNameIn = login.playerName;
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
        gameState = GameState::MainMenu;
    }
    scoreboard.draw(window);
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
    
    if (gameState == GameState::About || gameState == GameState::Scoreboard || gameState == GameState::MainMenu || gameState == GameState::LogIn)
    {
        this->menuMusic.play();
    }
    else
    {
        this->menuMusic.stop();
    }


    if (!running())
    {
        playerNameIn = ""; // รีเซ็ตค่าชื่อผู้เล่นใหม่
        changeGameState(GameState::LogIn); // เปิดหน้า LogIn อีกครั้ง
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
                // ทำตามการชนของ cherry
                player.addPoints(10);
            }
            else if (itemType == ItemType::Heart) {
                // ทำตามการชนของ heart
                player.heal(10);
            }
            else if (itemType == ItemType::Poison) {
                // ทำตามการชนของ poison
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
        player.writeDataToFile();
    }

    scoreText.setString("Score: " + std::to_string(player.getScore()));
    hpText.setString("Hp: " + std::to_string(player.getHp()));

    window.draw(scoreText);
    window.draw(hpText);
    window.draw(text);
    window.draw(nameText);

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
    // Check the game state and choose the appropriate rendering function

}

