#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "World.h"
#include "Mario.h"
#include <fstream>
#include <string>

class GameManager {
private:
    World* world;
    Mario* mario;
    std::ofstream outputFile;

    void placeMario();
    void placeBoss(); // New function to place the boss
    void printGrid();
    char getRandomMove();
    void announceMove(char move);

public:
    GameManager(const std::string& filename, const std::string& outputFilename);
    ~GameManager();
    void startGame();
};

#endif // GAMEMANAGER_H