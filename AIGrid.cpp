#include "AIGrid.h"
#include <random>
#include <iostream>

/* Initialize static members */
std::vector<std::vector<Grid::gridsquare>> AIGrid::AIGGrid;
std::vector<std::vector<Grid::gridsquare>> AIGrid::AISGrid;

int AIGrid::numOfShipsSunk;

void AIGrid::setGuessGrid()
{
	auto xCoord = 'A';
	auto yCoord = 1;

	/* Resizes the vector to hold a size of ten. At this step, the vector is only 1D. */
	AIGGrid.resize(ROW);

	/* An object of the gridsquare struct for use in resizing the vector with a struct of starting values */
	gridsquare g = { 'A', 1, false, false, false };

	/* Adds the columns to the vector, making it a 2D vector of 'gridsquare' struct type */
	for (size_t i = 0; i < ROW; i++) {
		AIGGrid[i].resize(COL, g);
	}

	/* Sets each square in the vector to default values for a guessing grid. Includes exact coordinates of the squares. */
	for (int i = 0; i < 10; i++) {
		yCoord = 1;

		for (int j = 0; j < 10; j++) {
			AIGGrid[i][j].isHit = false;
			AIGGrid[i][j].isMiss = false;
			AIGGrid[i][j].shipOnSquare = false;

			AIGGrid[i][j].xCoord = xCoord;

			AIGGrid[i][j].yCoord = yCoord;
			yCoord++;
		}
		xCoord += 1;

	}
}

void AIGrid::setShipGrid()
{
	const auto MAX = 10;
	auto xCoord = 'A';
	auto yCoord = 1;

	/* Resizes the vector to hold a size of ten. At this step, the vector is only 1D. */
	AISGrid.resize(ROW);

	/* An object of the gridsquare struct for use in resizing the vector with a struct of starting values */
	gridsquare g = { 'A', 1, false, false, false };

	/* Adds the columns to the vector, making it a 2D vector of 'gridsquare' struct type */
	for (size_t i = 0; i < ROW; i++) {
		AISGrid[i].resize(COL, g);
	}

	for (int i = 0; i < 10; i++) {
		yCoord = 1;

		for (int j = 0; j < 10; j++) {
			AISGrid[i][j].isHit = false;
			AISGrid[i][j].isMiss = false;
			AISGrid[i][j].shipOnSquare = false;

			AISGrid[i][j].xCoord = xCoord;

			AISGrid[i][j].yCoord = yCoord;
			yCoord++;
		}
		xCoord += 1;

	}


	/* Our alphabet for possible battleship positions */
	char alphabet[MAX] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

	/* Naming the ship types appropiately */
	AICarrier.shipType = "Carrier";
	AIBattleship.shipType = "Battleship";
	AICruiser.shipType = "Cruiser";
	AISubmarine.shipType = "Submarine";
	AIDestroyer.shipType = "Destroyer";

	/* Y values are randomly generated within certain range to avoid issues with ships going off the board. Every value is subtracted by 1 to account for indicies */
	auto carrierPosX = (rand() % 2) - 1;
	auto battleshipPosX = (rand() % 3 + 1) - 1;
	auto cruiserPosX = ((rand() % (8 + 1 - 7)) + 7) - 1;
	auto submarinePosX = ((rand() % (8 + 1 - 7)) + 7) - 1;
	auto destroyerPosX = ((rand() % (9 + 1 - 7)) + 7) - 1;

	/* X values are also generated within are certain range to again avoid issues with ships going off the board. */
	auto carrierPos = alphabet[rand() % 2];
	auto battleshipPos = alphabet[6];
	auto cruiserPos = alphabet[rand() % 2];
	auto submarinePos = alphabet[rand() % 1 + 4];
	auto destroyerPos = alphabet[8];

	/* Sets the position of each ship by adding the two strings using std::to_string for the Y values. */
	AICarrier.shipPosition = carrierPos + (std::to_string(carrierPosX));
	AIBattleship.shipPosition = battleshipPos + (std::to_string(battleshipPosX));
	AICruiser.shipPosition = cruiserPos + (std::to_string(cruiserPosX));
	AISubmarine.shipPosition = submarinePos + (std::to_string(submarinePosX));
	AIDestroyer.shipPosition = destroyerPos + (std::to_string(destroyerPosX));

	/* Ship orientation is random, either vertical or horizontal. */
	auto carrierShipOrientation = rand() % 2;
	auto battleshipShipOrientation = rand() % 2;
	auto cruiserShipOrientation = rand() % 2;
	auto submarineShipOrientation = rand() % 2;
	auto destroyerShipOrientation = rand() % 2;

	int carrierPosY = convertLetterToNumber(AICarrier.shipPosition[0]);
	int battleshipPosY = convertLetterToNumber(AIBattleship.shipPosition[0]);
	int cruiserPosY = convertLetterToNumber(AICruiser.shipPosition[0]);
	int submarinePosY = convertLetterToNumber(AISubmarine.shipPosition[0]);
	int destroyerPosY = convertLetterToNumber(AIDestroyer.shipPosition[0]);
	
	/* All the if statements here place the ships on the board depending on their orientation */
	AISGrid[carrierPosX][carrierPosY].shipOnSquare = true;
	AISGrid[carrierPosX][carrierPosY].carrier.shipOnSquare = true;

	if (carrierShipOrientation == 0) {
		AICarrier.shipOrientation = 'H';
		for (int i = 1; i < 5; i++) {
			AISGrid[carrierPosX][carrierPosY + i].shipOnSquare = true;
			AISGrid[carrierPosX][carrierPosY + i].carrier.shipOnSquare = true;
		}
	}

	if (carrierShipOrientation == 1) {
		AICarrier.shipOrientation = 'V';
		for (int i = 1; i < 5; i++) {
			AISGrid[carrierPosX + i][carrierPosY].shipOnSquare = true;
			AISGrid[carrierPosX + i][carrierPosY].carrier.shipOnSquare = true;
		}
	}

	AISGrid[battleshipPosX][battleshipPosY].shipOnSquare = true;
	AISGrid[battleshipPosX][battleshipPosY].battleship.shipOnSquare = true;

	if (battleshipShipOrientation == 0) {
		AIBattleship.shipOrientation = 'H';
		for (int i = 1; i < 4; i++) {
			AISGrid[battleshipPosX + i][battleshipPosY].shipOnSquare = true;
			AISGrid[battleshipPosX + i][battleshipPosY].battleship.shipOnSquare = true;
		}
	}
	if (battleshipShipOrientation == 1) {
		AIBattleship.shipOrientation = 'V';
		for (int i = 1; i < 4; i++) {
			AISGrid[battleshipPosX + i][battleshipPosY].shipOnSquare = true;
			AISGrid[battleshipPosX + i][battleshipPosY].battleship.shipOnSquare = true;
		}
	}

	AISGrid[cruiserPosX][cruiserPosY].cruiser.shipOnSquare = true;

	if (cruiserShipOrientation == 0) {
		AICruiser.shipOrientation = 'H';
		for (int i = 1; i < 3; i++) {
			AISGrid[cruiserPosX][cruiserPosY + i].shipOnSquare = true;
			AISGrid[cruiserPosX][cruiserPosY + i].cruiser.shipOnSquare = true;
		}
	}
	if (cruiserShipOrientation == 1) {
		AICruiser.shipOrientation = 'V';
		for (int i = 1; i < 3; i++) {
			AISGrid[cruiserPosX + i][cruiserPosY].shipOnSquare = true;
			AISGrid[cruiserPosX + i][cruiserPosY].cruiser.shipOnSquare = true;
		}
	}

	AISGrid[submarinePosX][submarinePosY].shipOnSquare = true;
	AISGrid[submarinePosX][submarinePosY].submarine.shipOnSquare = true;


	if (submarineShipOrientation == 0) {
		AISubmarine.shipOrientation = 'H';
		for (int i = 1; i < 3; i++) {
			AISGrid[submarinePosX][submarinePosY + i].shipOnSquare = true;
			AISGrid[submarinePosX][submarinePosY + i].submarine.shipOnSquare = true;
		}
	}
	if (submarineShipOrientation == 1) {
		AISubmarine.shipOrientation = 'V';
		for (int i = 1; i < 3; i++) {
			AISGrid[submarinePosX + i][submarinePosY].shipOnSquare = true;
			AISGrid[submarinePosX + i][submarinePosY].submarine.shipOnSquare = true;
		}
	}

	AISGrid[destroyerPosX][destroyerPosY].shipOnSquare = true;
	AISGrid[destroyerPosX][destroyerPosY].destroyer.shipOnSquare = true;

	if (destroyerShipOrientation == 0) {
		AIDestroyer.shipOrientation = 'H';
		for (int i = 1; i < 2; i++) {
			AISGrid[destroyerPosX][destroyerPosY + i].shipOnSquare = true;
			AISGrid[destroyerPosX][destroyerPosY + i].destroyer.shipOnSquare = true;
		}
	}
	if (destroyerShipOrientation == 1) {
		AIDestroyer.shipOrientation = 'V';
		for (int i = 1; i < 2; i++) {
			AISGrid[destroyerPosX + i][destroyerPosY].shipOnSquare = true;
			AISGrid[destroyerPosX + i][destroyerPosY].destroyer.shipOnSquare = true;
		}
	}
}

void AIGrid::displayGuessGrid()
{
	char xAxis = 'A';
	int yAxis = 1;

	std::cout << "\t\t   AI GUESS GRID\n";

	std::cout << "    ";

	/* displays AI guess grid, exactly like user guess grid */
	for (int i = 0; i < 10; i++) {
		std::cout << xAxis << "    ";
		xAxis++;
	}
	std::cout << std::endl;

	for (int i = 0; i < AIGGrid.size(); i++) {
		std::cout << yAxis;
		if (yAxis < 10) {
			std::cout << " ";
		}

		for (int j = 0; j < AIGGrid[i].size(); j++) {
			std::cout << "[ ";
			if (AIGGrid[i][j].isHit) {
				std::cout << "X";
			}

			else if (AIGGrid[i][j].isMiss) {
				std::cout << "O";
			}

			else if (AIGGrid[i][j].shipSunk) {
				std::cout << "*";
			}

			else {
				std::cout << " ";
			}
			std::cout << " ]";
		}
		std::cout << std::endl;
		yAxis++;
	}

	std::cout << std::endl;
}

void AIGrid::displayShipGrid()
{
	char xAxis = 'A';
	int yAxis = 1;

	std::cout << "\t\t    AI SHIP GRID\n";

	std::cout << "    ";

	/* Displays AI ship grid, exactly like user's ship grid */
	for (int i = 0; i < 10; i++) {
		std::cout << xAxis << "    ";
		xAxis++;
	}
	std::cout << std::endl;

	for (int i = 0; i < AISGrid.size(); i++) {
		std::cout << yAxis;
		if (yAxis < 10) {
			std::cout << " ";
		}

		for (int j = 0; j < AISGrid[i].size(); j++) {
			std::cout << "[ ";
			
			if (AISGrid[i][j].shipSunk) {
				std::cout << "*";
			}

			else if (AISGrid[i][j].isMiss) {
				std::cout << "O";
			}

			else if (AISGrid[i][j].shipOnSquare) {
				std::cout << "S";
			}

			else if (AISGrid[i][j].shipSunk) {
				std::cout << "*";
			}

			else {
				std::cout << " ";
			}
			std::cout << " ]";
		}
		std::cout << std::endl;
		yAxis++;
	}
}

void AIGrid::aGuess()
{

	/* AI chooses random spot to hit on the board*/
	int number = rand() % 10 + 1;
	int letter = rand() % 10 + 1;

	number--;
	letter--;

	/* If guess hits/sinks */
	if ((!UserGrid::userSGrid[number][letter].isHit || !UserGrid::userSGrid[number][letter].isMiss) && UserGrid::userSGrid[number][letter].shipOnSquare && !UserGrid::userSGrid[number][letter].shipSunk) {

		/* Explanation of this is found in UserGrid.cpp, they work the same way */
		/* These are really inefficient time-complexity wise but I couldn't think of an alternative :( */
		if (UserGrid::userSGrid[number][letter].carrier.shipOnSquare) {
			for (int i = 0; i < AISGrid.size(); i++) {
				for (int j = 0; j < AISGrid[i].size(); j++) {
					if (UserGrid::userSGrid[i][j].carrier.shipOnSquare) {
						UserGrid::userSGrid[i][j].shipSunk = true;
						UserGrid::userSGrid[i][j].isHit = true;
						AIGrid::AIGGrid[i][j].isHit = true;
					}
				}
			}
		}

		if (UserGrid::userSGrid[number][letter].battleship.shipOnSquare) {
			for (int i = 0; i < AISGrid.size(); i++) {
				for (int j = 0; j < AISGrid[i].size(); j++) {
					if (UserGrid::userSGrid[i][j].battleship.shipOnSquare) {
						UserGrid::userSGrid[i][j].shipSunk = true;
						UserGrid::userSGrid[i][j].isHit = true;
						AIGrid::AIGGrid[i][j].isHit = true;
					}
				}
			}
		}

		if (UserGrid::userSGrid[number][letter].cruiser.shipOnSquare) {
			for (int i = 0; i < AISGrid.size(); i++) {
				for (int j = 0; j < AISGrid[i].size(); j++) {
					if (UserGrid::userSGrid[i][j].cruiser.shipOnSquare) {
						UserGrid::userSGrid[i][j].shipSunk = true;
						UserGrid::userSGrid[i][j].isHit = true;
						AIGrid::AIGGrid[i][j].isHit = true;
					}
				}
			}
		}

		if (UserGrid::userSGrid[number][letter].submarine.shipOnSquare) {
			for (int i = 0; i < AISGrid.size(); i++) {
				for (int j = 0; j < AISGrid[i].size(); j++) {
					if (UserGrid::userSGrid[i][j].submarine.shipOnSquare) {
						UserGrid::userSGrid[i][j].shipSunk = true;
						UserGrid::userSGrid[i][j].isHit = true;
						AIGrid::AIGGrid[i][j].isHit = true;
					}
				}
			}
		}

		if (UserGrid::userSGrid[number][letter].destroyer.shipOnSquare) {
			for (int i = 0; i < AISGrid.size(); i++) {
				for (int j = 0; j < AISGrid[i].size(); j++) {
					if (UserGrid::userSGrid[i][j].destroyer.shipOnSquare) {
						UserGrid::userSGrid[i][j].shipSunk = true;
						UserGrid::userSGrid[i][j].isHit = true;
						AIGrid::AIGGrid[i][j].isHit = true;
					}
				}
			}
		}


		std::cout << "\n\n--Computer Hit! Ship sunk!\n\n";

		numOfShipsSunk++;

	}

	/* If guess misses */
	else if ((!UserGrid::userSGrid[number][letter].isHit || !UserGrid::userSGrid[number][letter].isMiss) && !UserGrid::userSGrid[number][letter].shipOnSquare) {

		AIGrid::AIGGrid[number][letter].isMiss = true;
		UserGrid::userSGrid[number][letter].isMiss = true;

		std::cout << "\n\n--Computer Miss!\n\n";
	}

	else {
		std::cout << "\n\n--Computer already guessed spot. \n\n";
	}

}