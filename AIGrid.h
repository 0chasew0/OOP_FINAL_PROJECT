#pragma once
#include "Grid.h"
class AIGrid :
	public Grid
{
public:

	/* The computer's ships */
	Ship AICarrier;
	Ship AIBattleship;
	Ship AICruiser;
	Ship AISubmarine;
	Ship AIDestroyer;

	void setGuessGrid();
	void setShipGrid();

	void displayGuessGrid();
	void displayShipGrid();

	void aGuess(std::string aGuess);

	bool isHit(std::string aGuess);
	bool isMiss(std::string aGues);
	bool shipIsSunk(std::string aGuess);

	friend class UserGrid;
};

