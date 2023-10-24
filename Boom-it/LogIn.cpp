#include "LogIn.h"

void LogIn::initTexture()
{
	if (!backgroundTexture.loadFromFile("images/login-page-ver.png"))
	{
		std::cout << "Can't open picture" << std::endl;
	}
}

void LogIn::initSprite()
{
	this->backgroundSprite.setTexture(this->backgroundTexture);
}

LogIn::LogIn()
{
	if (!font.loadFromFile("fonts/VCR_OSD_MONO_1.001.ttf"))
	{
		std::cout << "Can't open font" << std::endl;
	}
	this->initTexture();
	this->initSprite();

	this->nextState.setFont(this->font);
	this->nextState.setFillColor(sf::Color::Yellow);
	this->nextState.setString("NEXT");
	this->nextState.setPosition(sf::Vector2f(1750, 970));
	this->nextState.setCharacterSize(50);
	this->nextState.setOutlineThickness(1);

	this->backState.setFont(this->font);
	this->backState.setFillColor(sf::Color::Yellow);
	this->backState.setString("BACK");
	this->backState.setPosition(sf::Vector2f(50, 970));
	this->backState.setCharacterSize(50);
	this->backState.setOutlineThickness(1);

	this->playerNameText.setFont(this->font);
	this->playerNameText.setFillColor(sf::Color::White);
	this->playerNameText.setString("Enter Player Name");
	this->playerNameText.setPosition(sf::Vector2f(900, 300));
	this->playerNameText.setCharacterSize(60);
	this->playerNameText.setOutlineThickness(3);

    //playerName = "";

    for (int i = 0; i < 26; i++)
    {
        keyStates[i] = false;
    }

}

LogIn::~LogIn()
{
}

void LogIn::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color::Blue);
	window.draw(backgroundSprite);
	window.draw(nextState);
	window.draw(backState);
    //window.draw(nameText);
    this->textRect = playerNameText.getLocalBounds();
    playerNameText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
    playerNameText.setPosition(sf::Vector2f(1200, 340));
	window.draw(playerNameText);
}

void LogIn::updateMouseInput(sf::RenderWindow& window)
{
    this->mousePosition = sf::Mouse::getPosition(window);

    if (enteringName)
    {
        // Handle text input
        bool keyPressed = false; // เพิ่มตัวแปรสำหรับตรวจสอบการกดครั้งแรก

        for (int key = sf::Keyboard::A; key <= sf::Keyboard::Z; key++)
        {
            if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key)) && playerName.length()<12)
            {
                char inputChar = 'a' + (key - sf::Keyboard::A);

                // Check if Shift key is pressed for uppercase letters
                bool shiftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
                if (shiftPressed)
                {
                    inputChar = std::toupper(inputChar);
                }

                // Check if the key was not pressed in the previous frame
                if (!keyStates[key])
                {
                    playerName += inputChar;
   
                    keyPressed = true; // กำหนดให้ keyPressed เป็น true เมื่อมีการกด
                }
                keyStates[key] = true;
            }
            else
            {
                keyStates[key] = false;
            }
        }

        // Handle backspace to delete characters
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && playerName.length() > 0)
        {
            // Delete the last character from the player's name
            playerName.pop_back();
            keyPressed = true; // กำหนดให้ keyPressed เป็น true เมื่อมีการกด
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
        } 

        // Handle Enter to finish entering the name
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            enteringName = true;
            keyPressed = true; // กำหนดให้ keyPressed เป็น true เมื่อมีการกด
        }

        // Clear the player name text only if a key was pressed
        if (keyPressed)
        {
            playerNameText.setString("");
        }
    }
    else
    {
        if (playerNameText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // Clicked on the name input area, so allow the player to enter their name
                enteringName = true;
                playerNameText.setString(""); // Clear the initial "Enter Player Name" text
                this->textRect = playerNameText.getLocalBounds();
                playerNameText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
                playerNameText.setPosition(sf::Vector2f(900, 300));
            }
        }
    }

    // Update the player's name on the display
    if (!enteringName)
    {
        playerNameText.setString("Enter Player Name");
    }
    else
    {
        playerNameText.setString(playerName);
        //std::cout << playerName << std::endl;
    }

    if (nextState.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
    {
        this->nextState.setFillColor(sf::Color::Magenta);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->checkState = "next";
            std::ofstream playDataFile("player_data.txt");
            if (playDataFile.is_open())
            {
                // เขียนชื่อผู้เล่นลงในไฟล์
                playDataFile << playerName;
                playDataFile.close();
            }
            else
            {
                std::cout << "Unable to open player_data.txt for writing" << std::endl;
            }

        }
    }
    else
        this->nextState.setFillColor(sf::Color::White);

    if (backState.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)))
    {
        this->backState.setFillColor(sf::Color::Magenta);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->checkState = "back";
        }
    }
    else
        this->backState.setFillColor(sf::Color::White);
}

std::string LogIn::playerNameOutput()
{
    return playerName;
}

void LogIn::renderName(sf::RenderWindow& window)
{
    nameText.setFont(font);
    nameText.setCharacterSize(40);
    nameText.setFillColor(sf::Color::Magenta);
    nameText.setPosition(50, 400);
    nameText.setOutlineThickness(1.5);

    nameText.setString(playerName);

    window.draw(nameText);
}
