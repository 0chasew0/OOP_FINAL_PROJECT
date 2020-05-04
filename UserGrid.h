#pragma once

#include "Grid.h"

#include <fstream>
#include <vector>

class AIGrid;

class UserGrid :
	public Grid
{
private:
	
public:

	friend class AIGrid; // AIGrid and UserGrid are friends and must access each other's grids so we can update both

	/* The users ships */
	Ship userCarrier;
	Ship userBattleship;
	Ship userCruiser;
	Ship userSubmarine;
	Ship userDestroyer;

	static int numOfShipsSunk; // The number of ships the user has sunk

	std::string guess; // The user's guess

	/* The grids, 2D vectors of gridsquare type */
	static std::vector<std::vector<gridsquare>> userGGrid;
	static std::vector<std::vector<gridsquare>> userSGrid;


	/* This input function is specific to the UserGrid because the AI does not
	   use a .csv input file for the ships*/
	void inputShips(std::ifstream& f);

	bool areShipPositionsCorrect();

	void setGuessGrid();
	void setShipGrid();
	
	void displayGuessGrid();
	void displayShipGrid();
	
	void aGuess();

};

