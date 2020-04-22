#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>

#include "Ship.h"
#include "Grid.h"
#include "UserGrid.h"
#include "AIGrid.h"

int main()
{
    std::string exitChar = " "; // The exit character
    std::string aGuess = " "; // A user's guess
    char userInput; // User choice for playing or exiting
    std::ifstream shipFile("ship_placement.csv");
    UserGrid u;

    while (exitChar != "Q" && exitChar != "q") {
        std::cout << "----------------------------------------"
                  << "------\n";
        std::cout << "|\t    WELCOME TO BATTLESHIP\t     |\n";
        std::cout << "|\t A GAME CREATED FOR CSCI 2312\t     |\n";
        std::cout << "|\t    BY: CHASE WILLIAMSON\t     |\n";

        std::cout << "|\t------------------------------\t     |\n";
        std::cout << "|\t| PLAY ONE HIT KILL MODE (o) |\t     |\n";
        std::cout << "|\t------------------------------\t     |\n";

        std::cout << "|\t------------------------------\t     |\n";
        std::cout << "|\t|    PLAY CLASSIC MODE (c)   |\t     |\n";
        std::cout << "|\t------------------------------\t     |\n";

        std::cout << "|\t------------------------------\t     |\n";
        std::cout << "|\t|          EXIT (q)          |\t     |\n";
        std::cout << "|\t------------------------------\t     |\n";
        std::cout << "----------------------------------------"
            << "------\n\n";

        std::cin >> userInput;

        switch (userInput) {
        case 'o':
            

            u.inputShips(shipFile);
            
            // play one hit kill mode here
            break;

        case 'c':
            // play classic mode here
            break;

        case 'q':
            exitChar = userInput;
            //exit the game here (display board if needed)
            break;

        default:
            std::cout << "Invalid. Choose one of the options.\n";
            break;
        }

    }
}
