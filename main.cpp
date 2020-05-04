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
    std::ifstream shipFile("ship_placement.csv"); // The .csv for inputting ships
    UserGrid u; // UserGrid object
    AIGrid a; // AIGrid object

    /* Main menu loop controller by exitChar*/
    while (exitChar != "Q" && exitChar != "q") {

        /* Menu */
        std::cout << "----------------------------------------"
                  << "------\n";
        std::cout << "|\t    WELCOME TO BATTLESHIP\t     |\n";
        std::cout << "|\t A GAME CREATED FOR CSCI 2312\t     |\n";
        std::cout << "|\t    BY: CHASE WILLIAMSON\t     |\n";

        std::cout << "|\t------------------------------\t     |\n";
        std::cout << "|\t| PLAY ONE HIT KILL MODE (o) |\t     |\n";
        std::cout << "|\t------------------------------\t     |\n";

        std::cout << "|\t------------------------------\t     |\n";
        std::cout << "|\t|    PLAY CLASSIC MODE (WIP) |       |\n";
        std::cout << "|\t------------------------------\t     |\n";

        std::cout << "|\t------------------------------\t     |\n";
        std::cout << "|\t|          EXIT (q)          |\t     |\n";
        std::cout << "|\t------------------------------\t     |\n";
        std::cout << "----------------------------------------"
            << "------\n";

        std::cin >> userInput;

        switch (userInput) {
        // play one hit kill mode here
        case 'o':
            std::cout << "--Checking if the inputted ships are correct...\n\n";
            u.inputShips(shipFile);
            std::cout << "--All ships are valid! Starting game... \n";
            u.setGuessGrid(); // Sets up the user's guessing grid
            u.setShipGrid(); // Sets up the user's ship grid

            a.setGuessGrid(); // Sets up AI guess grid
            a.setShipGrid(); // Sets up AI ship grid

            std::cout << "\n--Press Q for your guess to exit at any time.\n\n";

            // Game loop, exits when user wants to exit or soneone wins 
            while (u.guess != "q" || u.guess != "Q") {

                /* Exits when user sinks five ships */
                if (UserGrid::numOfShipsSunk == 5) {
                    std::cout << "--User won! Congratulations!\n";
                    break;
                }
                
                /* Exits when AI sinks five ships */
                else if (AIGrid::numOfShipsSunk == 5) {
                    std::cout << "--Computer won! Better luck next time.\n";
                    break;
                }
            
                u.displayGuessGrid();
                u.displayShipGrid();
                
                u.aGuess();

                /* Checks if the user wanted to exit */
                if (u.guess == "q" || u.guess == "Q") {
                    break;
                }
                else {
                    a.aGuess();
                }
                
            }
            
            /* This is displayed always at the end regardless of user quit or game over */
            std::cout << "\n\n--Game was exited, or someone won. All the boards: \n\n";
            u.displayGuessGrid();
            u.displayShipGrid();
            a.displayGuessGrid();
            a.displayShipGrid();

            break;

        // play classic mode here
        case 'c':
            std::cout << "--This mode has not yet been added. Stay tuned! \n";
            break;
        
        /* exit case */
        case 'q':
            exitChar = userInput;
            std::cout << "--Goodbye!\n";
            break;
            
        /* default case */
        default:
            std::cout << "--Invalid. Choose one of the options.\n";
            break;
        }

    }
}
