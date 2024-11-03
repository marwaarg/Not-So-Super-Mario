#ifndef WORLD_H
#define WORLD_H

#include <string>

const char coin = 'c'; //intilaize all characters
const char goomba = 'g';
const char koopa = 'k';
const char mushroom = 'm';
const char empty = 'x';
const char hero = 'H';
const char warp = 'w';
const char boss = 'b';

class World {
public:
    int totalLevels; //initialize variables for .cpp file
    int currentLevel;
    int gridSize;
    int lives;
    int coinPercentage, emptyPercentage, goombaPercentage, koopaPercentage, mushroomPercentage;
    char** grid; 

    World(const std::string& filename); 
    ~World(); //destrcutor

    void nextLevel(); //initializing methods
    bool isGameComplete() const;

private:
    void populateGrid();
    void fillGridWithEntity(char entity, int count); 
};

#endif // WORLD_H