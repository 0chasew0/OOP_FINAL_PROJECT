#pragma once
#include <vector>

#include "Ship.h"

class Grid :
	public Ship
{
public:

	const size_t ROW = 10; // Size of a row in our vectors
	const size_t COL = 10; // Size of a column in our vectors

	struct gridsquare {
		char xCoord; // xCoordinate of grid square
		int yCoord; // yCoord
		bool isHit; // Square is in status of 'hit'
		bool isMiss; // Square is in status of 'miss'
		bool shipOnSquare; // Square is in status of 'shipOnSquare'
		bool shipSunk; // If the square has the status of 'shipsunk'
		Ship carrier; // Placeholder ships that are used for putting the entire length of a ship over multiple squares
		Ship battleship;
		Ship cruiser;
		Ship submarine;
		Ship destroyer;
	};

	int convertLetterToNumber(char c); // Our encoding system for turning A -> 1, B -> 2, etc.

	/* These functions set up the grids with the ships */
	virtual void setGuessGrid() = 0;
	virtual void setShipGrid() = 0;

	/* Functions to print the grids */
	virtual void displayGuessGrid() = 0;
	virtual void displayShipGrid() = 0;

};

