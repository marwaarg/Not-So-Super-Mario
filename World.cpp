#include "World.h"
#include <iostream>
#include <fstream>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()

World::World(const std::string& filename) { 
    std::ifstream file(filename); //opening the file
    if (!file) {
        std::cerr << "Error opening file." << std::endl; // if file isnt able to open, error message
        exit(1);
    }

    file >> totalLevels >> gridSize >> lives; //reading the parameters from file
    file >> coinPercentage >> emptyPercentage >> goombaPercentage >> koopaPercentage >> mushroomPercentage; //"" but for percentages

    if (coinPercentage + emptyPercentage + goombaPercentage + koopaPercentage + mushroomPercentage != 100) {
        std::cerr << "Percentages do not sum to 100." << std::endl; //checking if all the percentages add up to 100 or else error
        exit(1);
    }

    currentLevel = 0;
    grid = new char*[gridSize]; //allocate memory for 2d grid
    for (int i = 0; i < gridSize; i++) {
        grid[i] = new char[gridSize](); //initializing each row of the grid
    }

    populateGrid(); //call function to fill grid with characters
}

World::~World() { //destructor
    for (int i = 0; i < gridSize; i++) { //goes through every line
        delete[] grid[i]; //deletes the memory allocated for each row
    }
    delete[] grid;
}

void World::nextLevel() {
    if (currentLevel < totalLevels - 1) { //check if there is a next level
        currentLevel++; //increment the current level
        populateGrid(); //populates grid for new level
    }
}

bool World::isGameComplete() const {
    return currentLevel >= totalLevels - 1; // check if the current level is greater than or equal to last level
} //if true game is done, if not keeping going

void World::populateGrid() {
    srand(time(0) + currentLevel);  // Use level in seed to get different layouts
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = empty;  // Initialize all cells to empty
        }
    }
    
    int totalCells = gridSize * gridSize; //calc num of cells
    fillGridWithEntity(coin, (coinPercentage * totalCells) / 100); //fills grid with characters and calc as a percentage
    fillGridWithEntity(goomba, (goombaPercentage * totalCells) / 100); 
    fillGridWithEntity(koopa, (koopaPercentage * totalCells) / 100);
    fillGridWithEntity(mushroom, (mushroomPercentage * totalCells) / 100);
}

void World::fillGridWithEntity(char entity, int count) {
    while (count > 0) {
        int x = rand() % gridSize; // x and y axis are randommized 
        int y = rand() % gridSize;
        if (grid[x][y] == empty) { //fill space if empty with character
            grid[x][y] = entity;
            count--;
        }
    }
}