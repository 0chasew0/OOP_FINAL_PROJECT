#pragma once
#include "Grid.h"
#include <fstream>

class UserGrid :
	public Grid
{
public:

	/* The users ships */
	Ship userCarrier;
	Ship userBattleship;
	Ship userCruiser;
	Ship userSubmarine;
	Ship userDestroyer;

	/* This input function is specific to the UserGrid because the AI does not
	   use a .csv input file for the ships*/
	void inputShips(std::ifstream& f);
	/*void setGuessGrid();
	void setShipGrid(Ship carrier, Ship battleship, Ship cruiser, Ship submarine, Ship destroyer);

	void displayGuessGrid();
	void displayShipGrid();

	void aGuess(std::string aGuess);

	bool isHit(std::string aGuess);
	bool isMiss(std::string aGues);
	bool shipIsSunk(std::string aGuess);*/
	
	friend class AIGrid;
};

