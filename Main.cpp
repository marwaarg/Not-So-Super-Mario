#include "GameManager.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) {//check the number of command line arguments
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return 1; 
    }

    GameManager game(argv[1], argv[2]); //pass input file and output file
    game.startGame(); //starts game

    std::cout << "The game was finished. Results are in: " << argv[2] << std::endl;

    return 0;
}