#ifndef MARIO_H
#define MARIO_H

#include <fstream>

class Mario {
public:
    int lives;
    int powerLevel;
    int coins;
    int posX, posY;
    bool hasDefeatedBoss;  // Explicitly added member

    Mario(int initialLives);
    void move(char direction, int gridSize);
    void interact(char entity, std::ofstream& outputFile);
    bool isAlive();
};

#endif // MARIO_H