#include <string>

class PlayerData
{
public:
    PlayerData(const std::string& playerName, int playerScore)
        : name(playerName), score(playerScore) {}

    std::string name;
    int score;
};
