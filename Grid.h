#pragma once
#include <vector>

#include "Ship.h"

class Grid :
	public Ship
{
public:
	/* The five ships of type Ship */
	Ship carrier;
	Ship battleship;
	Ship cruiser;
	Ship submarine;
	Ship destroyer;

	/* The two grids for the user and AI */
	std::vector<int> guessGrid;
	std::vector<int> shipGrid;

	/* These functions set up the grids with the ships */
	virtual void setGuessGrid() = 0;
	virtual void setShipGrid(Ship carrier, Ship battleship, Ship cruiser, Ship submarine, Ship destroyer) = 0;

	/* Functions to print the grids */
	virtual void displayGuessGrid() = 0;
	virtual void displayShipGrid() = 0;

	/* A guess, which will update the guessGrid of the user and the shipGrid of the AI, and vice versa. */
	virtual void aGuess(std::string aGuess) = 0;

	/* Helper functions to aGuess */
	virtual bool isHit(std::string aGuess) = 0;
	virtual bool isMiss(std::string aGues) = 0;
	virtual bool shipIsSunk(std::string aGuess) = 0;
};

