#pragma once
#include "Grid.h"
#include "UserGrid.h"

class UserGrid;

class AIGrid :
	public Grid
{

public:

	friend class UserGrid;

	/* The computer's ships */
	Ship AICarrier;
	Ship AIBattleship;
	Ship AICruiser;
	Ship AISubmarine;
	Ship AIDestroyer;

	static int numOfShipsSunk; // The number of ships the AI has sunk

	static std::vector<std::vector<gridsquare>> AIGGrid;
	static std::vector<std::vector<gridsquare>> AISGrid;

	void setGuessGrid();
	void setShipGrid();

	void displayGuessGrid();
	void displayShipGrid();

	void aGuess();
	
};

