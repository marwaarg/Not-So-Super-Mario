#include "Mario.h"
#include <iostream>

Mario::Mario(int initialLives) { //set lives to initial lives and all numbers to 0
    lives = initialLives;
    powerLevel = 0;
    coins = 0;
    posX = posY = 0;
    hasDefeatedBoss = false;  // Initialize the new member
}

void Mario::move(char direction, int gridSize) { //checks how to move in grid with x and y coordinates
    switch (direction) {
        case 'U': 
        posX = (posX - 1 + gridSize) % gridSize; 
        break;
        case 'D': 
        posX = (posX + 1) % gridSize; 
        break;
        case 'L': 
        posY = (posY - 1 + gridSize) % gridSize; 
        break;
        case 'R': 
        posY = (posY + 1) % gridSize; 
        break;
    }
}

void Mario::interact(char entity, std::ofstream& outputFile) { //how to interact with every character and what to output to file
    switch (entity) {
        case 'c':
            coins++;
            outputFile << "Mario collected a coin. ";
            break;
        case 'g':
            if (powerLevel == 0) {
                lives--;
                outputFile << "Mario encountered a goomba and lost. ";
            } else {
                outputFile << "Mario encountered a goomba and won. ";
            }
            break;
        case 'k':
            if (powerLevel == 0) {
                lives--;
                outputFile << "Mario encountered a koopa and lost. ";
            } else {
                outputFile << "Mario encountered a koopa and won. ";
            }
            break;
        case 'm':
            powerLevel = 1;
            outputFile << "Mario ate a mushroom. ";
            break;
        case 'b':  // New case for boss
            if (powerLevel > 0) {
                hasDefeatedBoss = true;
                outputFile << "Mario defeated the boss! ";
            } else {
                lives--;
                outputFile << "Mario encountered the boss and lost. ";
            }
            break;
        case 'x':
            outputFile << "Mario visited an empty space. ";
            break;
    }
}

bool Mario::isAlive() { //checking if mario is alive
    return lives > 0;
}