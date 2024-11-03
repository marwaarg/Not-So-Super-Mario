#include "GameManager.h"
#include <iostream>
#include <cstdlib>  // For rand()

GameManager::GameManager(const std::string& filename, const std::string& outputFilename) { 
    world = new World(filename); //new world object
    mario = new Mario(world->lives); // new mario object, intilized with lives
    outputFile.open(outputFilename); //opens game_output.txt
    if (!outputFile.is_open()) { //checks if correctly opened
        std::cerr << "Error opening output file." << std::endl; 
        exit(1);
    }
    placeMario(); //mario is placed in the world
    placeBoss(); // New: place the boss in the world
}

GameManager::~GameManager() { //destructor
    delete world; //delete world object
    delete mario; //delete mario object
    if (outputFile.is_open()) {  //check if file is still open, if so close it 
        outputFile.close();
    }
}

void GameManager::startGame() {
    printGrid();
    outputFile << "Mario is starting in position: (" << mario->posX << "," << mario->posY << ")" << std::endl; //print marios position
    outputFile << "==========" << std::endl;

    while (mario->isAlive() && !mario->hasDefeatedBoss) { //if mario is still alive and hasn't defeated the boss
        printGrid();
        outputFile << "Level: " << world->currentLevel << ". ";
        outputFile << "Mario is at position (" << mario->posX << ", " << mario->posY << "). ";
        outputFile << "Power level: " << mario->powerLevel << ". ";
        outputFile << "Lives: " << mario->lives << ". ";
        outputFile << "Coins: " << mario->coins << ". ";

        char move = getRandomMove();
        announceMove(move);
        
        //marios old positions are updated 
        int oldX = mario->posX;
        int oldY = mario->posY;
        
        mario->move(move, world->gridSize);
        
        // updating marios position on the grid so it does'nt run forever (claude.ai)
        world->grid[oldX][oldY] = empty;
        char entityAtNewPos = world->grid[mario->posX][mario->posY];
        world->grid[mario->posX][mario->posY] = hero;

        mario->interact(entityAtNewPos, outputFile);

        outputFile << std::endl << "==========" << std::endl;
    }
    //end claude.ai

    printGrid();  // Print the final state of the grid

    if (!mario->isAlive()) { //chekcing if mario isnt alive
        outputFile << "Mario lost all his lives!" << std::endl; //print status of mario and games
        outputFile << "WE LOST THE GAME :(" << std::endl;
    } else if (mario->hasDefeatedBoss) { //check if he defeated the boss
        outputFile << "Mario defeated the boss!" << std::endl; 
        outputFile << "WE WON THE GAME :)" << std::endl;
    }
}

void GameManager::placeMario() {
    while (true) {
        int x = rand() % world->gridSize; //random x + y coordinates
        int y = rand() % world->gridSize;

        if (world->grid[x][y] == empty) { //if grid is empty
            mario->posX = x;
            mario->posY = y;
            world->grid[x][y] = hero; //place mario
            break;
        }
    }
}

void GameManager::placeBoss() {
    while (true) {
        int x = rand() % world->gridSize;
        int y = rand() % world->gridSize;

        if (world->grid[x][y] == empty) {
            world->grid[x][y] = boss; // place boss
            break;
        }
    }
}

void GameManager::printGrid() { //printing grid
    for (int i = 0; i < world->gridSize; i++) {
        for (int j = 0; j < world->gridSize; j++) {
            outputFile << world->grid[i][j];
        }
        outputFile << std::endl;
    }
    outputFile << "==========" << std::endl;
}

char GameManager::getRandomMove() { //gets random move
    char moves[] = {'U', 'D', 'L', 'R'};
    return moves[rand() % 4];
}

void GameManager::announceMove(char move) { //print the move that mario is making 
    std::string direction;
    switch (move) {
        case 'U': direction = "UP"; break;
        case 'D': direction = "DOWN"; break;
        case 'L': direction = "LEFT"; break;
        case 'R': direction = "RIGHT"; break;
    }
    outputFile << "Mario is going to move " << direction << "." << std::endl; // print move mario is GOING to make
}