#include "UserGrid.h"
#include "AIGrid.h"
#include "Grid.h"

#include <iostream>

/* Initializing static members */
std::vector<std::vector<Grid::gridsquare>> UserGrid::userGGrid;
std::vector<std::vector<Grid::gridsquare>> UserGrid::userSGrid;

int UserGrid::numOfShipsSunk;

bool UserGrid::areShipPositionsCorrect()
{
	/* Checks if the ship positions are equal, returns false if they are since this is not allowed */
	if (userCarrier.shipPosition == userBattleship.shipPosition || userCarrier.shipPosition == userCruiser.shipPosition || userCarrier.shipPosition == userSubmarine.shipPosition || userCarrier.shipPosition == userDestroyer.shipPosition) {
		return true;
	}

	else if (userBattleship.shipPosition == userCruiser.shipPosition || userBattleship.shipPosition == userSubmarine.shipPosition || userBattleship.shipPosition == userDestroyer.shipPosition) {
		return true;
	}

	else if (userCruiser.shipPosition == userSubmarine.shipPosition || userCruiser.shipPosition == userDestroyer.shipPosition) {
		return true;
	}

	else if (userSubmarine.shipPosition == userDestroyer.shipPosition) {
		return true;
	}
	
	else {
		return false;
	}
	
}

void UserGrid::inputShips(std::ifstream& f)
{
	
	/* Gets the user's ship data from the .csv file */

	std::getline(f, userCarrier.shipType, ',');
	std::getline(f, userCarrier.shipPosition, ',');
	std::getline(f, userCarrier.shipOrientation, '\n');

	std::getline(f, userBattleship.shipType, ',');
	std::getline(f, userBattleship.shipPosition, ',');
	std::getline(f, userBattleship.shipOrientation, '\n');

	std::getline(f, userCruiser.shipType, ',');
	std::getline(f, userCruiser.shipPosition, ',');
	std::getline(f, userCruiser.shipOrientation, '\n');

	std::getline(f, userSubmarine.shipType, ',');
	std::getline(f, userSubmarine.shipPosition, ',');
	std::getline(f, userSubmarine.shipOrientation, '\n');

	std::getline(f, userDestroyer.shipType, ',');
	std::getline(f, userDestroyer.shipPosition, ',');
	std::getline(f, userDestroyer.shipOrientation, '\n');

	f.close(); // Close the file when we are done reading from it


	try {

		/* If the user doesn't enter the ship names correctly */
		if (userCarrier.shipType.compare("Carrier") != 0) {
				throw std::invalid_argument("Ship 'Carrier' should be included in the first row of .csv ship file");
		}

		if (userBattleship.shipType.compare("Battleship") != 0) {
			throw std::invalid_argument("Ship 'Battleship' should be included in the second row of .csv ship file");
		}

		if (userCruiser.shipType.compare("Cruiser") != 0) {
			throw std::invalid_argument("Ship 'Cruiser' should be included in the third row of .csv ship file");
		}

		if (userSubmarine.shipType.compare("Submarine") != 0) {
			throw std::invalid_argument("Ship 'Submarine' should be included in the fourth row of .csv ship file");
		}

		if (userDestroyer.shipType.compare("Destroyer") != 0) {
			throw std::invalid_argument("Ship 'Destroyer' should be included in the fifth row of .csv ship file");
		}

		/* If ship positions are equal, throw invalid argument*/
		if (areShipPositionsCorrect()) {
			throw std::invalid_argument("One or more ship positions are not correct");
		}

		/* If ship orientations are not vertical or hoizontal */
		if ((userCarrier.shipOrientation.compare("V") != 0) && (userCarrier.shipOrientation.compare("H") != 0)) {
			throw std::invalid_argument("Orientation of Carrier incorrect (must be V or H)");
		}

		if ((userBattleship.shipOrientation.compare("V") != 0) && (userBattleship.shipOrientation.compare("H") != 0)) {
			throw std::invalid_argument("Orientation of Battleship incorrect (must be V or H)");
		}

		if ((userCruiser.shipOrientation.compare("V") != 0) && (userCruiser.shipOrientation.compare("H") != 0)) {
			throw std::invalid_argument("Orientation of Cruiser incorrect (must be V or H)");
		}

		if ((userSubmarine.shipOrientation.compare("V") != 0) && (userSubmarine.shipOrientation.compare("H") != 0)) {
			throw std::invalid_argument("Orientation of Submarine incorrect (must be V or H)");
		}

		if ((userDestroyer.shipOrientation.compare("V") != 0) && (userDestroyer.shipOrientation.compare("H") != 0)) {
			throw std::invalid_argument("Orientation of Destroyer incorrect (must be V or H)");
		}

	}
	
	/* Catch the error and exit program, as program cannot continue without correct values of ships */
	catch (const std::invalid_argument& e) {
		std::cout << "ERROR: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}

void UserGrid::setGuessGrid()
{

	auto xCoord = 'A';
	auto yCoord = 1;
	
	/* Resizes the vector to hold a size of ten. At this step, the vector is only 1D. */
	userGGrid.resize(ROW);

	/* An object of the gridsquare struct for use in resizing the vector with a struct of starting values */
	gridsquare g = { 'A', 1, false, false, false };

	/* Adds the columns to the vector, making it a 2D vector of 'gridsquare' struct type */
	for (size_t i = 0; i < ROW; i++) {
		userGGrid[i].resize(COL, g);
	}

	/* Sets each square in the vector to default values for a guessing grid. Includes exact coordinates of the squares. */
	for (int i = 0; i < 10; i++) {
		yCoord = 1;

		for (int j = 0; j < 10; j++) {
			userGGrid[i][j].isHit = false;
			userGGrid[i][j].isMiss = false;
			userGGrid[i][j].shipOnSquare = false;

			userGGrid[i][j].xCoord = xCoord;

			userGGrid[i][j].yCoord = yCoord;
			yCoord++;
		}
		xCoord += 1;

	}

}

void UserGrid::setShipGrid()
{

	auto xCoord = 'A';
	auto yCoord = 1;

	/* Resizes the vector to hold a size of ten. At this step, the vector is only 1D. */
	userSGrid.resize(ROW);

	/* An object of the gridsquare struct for use in resizing the vector with a struct of starting values */
	gridsquare g = { 'A', 1, false, false, false };

	/* Adds the columns to the vector, making it a 2D vector of 'gridsquare' struct type */
	for (size_t i = 0; i < ROW; i++) {
		userSGrid[i].resize(COL, g);
	}

	/* Sets each square in the vector to default values for a guessing grid. Includes exact coordinates of the squares. */
	for (int i = 0; i < 10; i++) {
		yCoord = 1;

		for (int j = 0; j < 10; j++) {
			userSGrid[i][j].isHit = false;
			userSGrid[i][j].isMiss = false;
			userSGrid[i][j].shipOnSquare = false;

			userSGrid[i][j].xCoord = xCoord;

			userSGrid[i][j].yCoord = yCoord;
			yCoord++;
		}
		xCoord += 1;

	}

	/* Converts the first part of the coordinate since it is letter*/
	int carrierPosX = convertLetterToNumber(userCarrier.shipPosition[0]);
	int carrierPosY = userCarrier.shipPosition[1] - '0'; /* We are converting a char to an int here by means of subtracting the char by the '0' character, which has the ASCII value of 48. This only works for single-digit numbers */

	/* If the guess is a 10 a.k.a a double digit number we must add 9 or else it will be 1 instead of 10. */
	if (userCarrier.shipPosition[2] == '0') {
		carrierPosY += 9;
	}

	carrierPosY--; 

	userSGrid[carrierPosY][carrierPosX].shipOnSquare = true;
	userSGrid[carrierPosY][carrierPosX].carrier.shipOnSquare = true;

	/* Puts the rest of the carrier on the ship grid depending on the orientation. */
	if (userCarrier.shipOrientation == "H") {
		for (int i = 1; i < 5; i++) {
			userSGrid[carrierPosY][carrierPosX + i].shipOnSquare = true;
			userSGrid[carrierPosY][carrierPosX + i].carrier.shipOnSquare = true;
		}
	}
	
	else if (userCarrier.shipOrientation == "V") {
		for (int i = 1; i < 5; i++) {
			userSGrid[carrierPosY - i][carrierPosX].shipOnSquare = true;
			userSGrid[carrierPosY - i][carrierPosX].carrier.shipOnSquare = true;
		}
	}


	/* Puts the starting position of the battleship on the grid. */
	int battleshipPosX = convertLetterToNumber(userBattleship.shipPosition[0]);
	int battleshipPosY = userBattleship.shipPosition[1] - '0';

	if (userBattleship.shipPosition[2] == '0') {
		battleshipPosY += 9;
	}

	battleshipPosY--;

	userSGrid[battleshipPosY][battleshipPosX].shipOnSquare = true;
	userSGrid[battleshipPosY][battleshipPosX].battleship.shipOnSquare = true;

	/* Puts the rest of the battleship on the ship grid depending on the orientation. */
	if (userBattleship.shipOrientation == "H") {
		for (int i = 1; i < 4; i++) {
			userSGrid[battleshipPosY][battleshipPosX + i].shipOnSquare = true;
			userSGrid[battleshipPosY][battleshipPosX + i].battleship.shipOnSquare = true;
		}
	}

	else if (userBattleship.shipOrientation == "V") {
		for (int i = 1; i < 4; i++) {
			userSGrid[battleshipPosY - i][battleshipPosX].shipOnSquare = true;
			userSGrid[battleshipPosY - i][battleshipPosX].battleship.shipOnSquare = true;
		}
	}


	/* Puts the starting position of the cruiser on the grid. */
	int cruiserPosX = convertLetterToNumber(userCruiser.shipPosition[0]);
	int cruiserPosY = userCruiser.shipPosition[1] - '0';

	if (userCruiser.shipPosition[2] == '0') {
		cruiserPosY += 9;
	}

	cruiserPosY--;

	userSGrid[cruiserPosY][cruiserPosX].shipOnSquare = true;
	userSGrid[cruiserPosY][cruiserPosX].cruiser.shipOnSquare = true;

	/* Puts the rest of the cruiser on the ship grid depending on the orientation. */
	if (userCruiser.shipOrientation == "H") {
		for (int i = 1; i < 3; i++) {
			userSGrid[cruiserPosY][cruiserPosX + i].shipOnSquare = true;
			userSGrid[cruiserPosY][cruiserPosX + i].cruiser.shipOnSquare = true;
		}
	}

	else if (userCruiser.shipOrientation == "V") {
		for (int i = 1; i < 3; i++) {
			userSGrid[cruiserPosY - i][cruiserPosX].shipOnSquare = true;
			userSGrid[cruiserPosY - i][cruiserPosX].cruiser.shipOnSquare = true;
		}
	}


	/* Puts the starting position of the submarine on the grid. */
	int submarinePosX = convertLetterToNumber(userSubmarine.shipPosition[0]);
	int submarinePosY = userSubmarine.shipPosition[1] - '0';

	if (userSubmarine.shipPosition[2] == '0') {
		submarinePosY += 9;
	}

	submarinePosY--;

	userSGrid[submarinePosY][submarinePosX].shipOnSquare = true;
	userSGrid[submarinePosY][submarinePosX].submarine.shipOnSquare = true;

	/* Puts the rest of the submarine on the ship grid depending on the orientation. */
	if (userSubmarine.shipOrientation == "H") {
		for (int i = 1; i < 3; i++) {
			userSGrid[submarinePosY][submarinePosX + i].shipOnSquare = true;
			userSGrid[submarinePosY][submarinePosX + i].submarine.shipOnSquare = true;
		}
	}

	else if (userSubmarine.shipOrientation == "V") {
		for (int i = 1; i < 3; i++) {
			userSGrid[submarinePosY - i][submarinePosX].shipOnSquare = true;
			userSGrid[submarinePosY - i][submarinePosX].submarine.shipOnSquare = true;
		}
	}


	/* Puts the starting position of the destroyer on the grid. */
	int destroyerPosX = convertLetterToNumber(userDestroyer.shipPosition[0]);
	int destroyerPosY = userDestroyer.shipPosition[1] - '0';

	if (userDestroyer.shipPosition[2] == '0') {
		destroyerPosY += 9;
	}

	destroyerPosY--;

	userSGrid[destroyerPosY][destroyerPosX].shipOnSquare = true;
	userSGrid[destroyerPosY][destroyerPosX].destroyer.shipOnSquare = true;

	/* Puts the rest of the destroyer on the ship grid depending on the orientation. */
	if (userDestroyer.shipOrientation == "H") {
		for (int i = 1; i < 2; i++) {
			userSGrid[destroyerPosY][destroyerPosX + i].shipOnSquare = true;
			userSGrid[destroyerPosY][destroyerPosX + i].destroyer.shipOnSquare = true;
		}
	}

	else if (userDestroyer.shipOrientation == "V") {
		for (int i = 1; i < 2; i++) {
			userSGrid[destroyerPosY - i][destroyerPosX].shipOnSquare = true;
			userSGrid[destroyerPosY - i][destroyerPosX].destroyer.shipOnSquare = true;
		}
	}
}

void UserGrid::displayGuessGrid()
{
	char xAxis = 'A';
	int yAxis = 1;

	/* legend so user knows what characters mean what */
	std::cout << "\tHit: X   " << "Miss: O   " << "Ship: S    " << "Sunk: *\n";

	std::cout << "\t\t    GUESS GRID\n";

	std::cout << "    ";
	
	/* prints the board, and depending on the state of the grid square, will display a certain character (hit, miss, sunk, none) */
	for (int i = 0; i < 10; i++) {
		std::cout << xAxis << "    ";
		xAxis++;
	}
	std::cout << std::endl;
	
	for (int i = 0; i < userGGrid.size(); i++) {
		std::cout << yAxis;
		if (yAxis < 10) {
			std::cout << " ";
		}
		
		for (int j = 0; j < userGGrid[i].size(); j++) {
			std::cout << "[ ";
			if (userGGrid[i][j].isHit) {
				std::cout << "X";
			}
			
			else if (userGGrid[i][j].isMiss) {
				std::cout << "O";
			}

			else if (userGGrid[i][j].shipSunk) {
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

void UserGrid::displayShipGrid()
{
	char xAxis = 'A';
	int yAxis = 1;

	std::cout << "\t\t     SHIP GRID\n";

	std::cout << "    ";

	/* Also print the board, but since this is the ship board we are replacing hits with Sunk (since this is one hit kill mode) */
	for (int i = 0; i < 10; i++) {
		std::cout << xAxis << "    ";
		xAxis++;
	}
	std::cout << std::endl;

	for (int i = 0; i < userSGrid.size(); i++) {
		std::cout << yAxis;
		if (yAxis < 10) {
			std::cout << " ";
		}

		for (int j = 0; j < userSGrid[i].size(); j++) {
			std::cout << "[ ";

			if (userSGrid[i][j].shipSunk) {
				std::cout << "*";
			}

			else if (userSGrid[i][j].isMiss) {
				std::cout << "O";
			}

			else if (userSGrid[i][j].shipOnSquare) {
				std::cout << "S";
			}

			else if (userSGrid[i][j].shipSunk) {
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

	std::cout << "\n";
}

void UserGrid::aGuess()
{

	AIGrid AI;

	std::cout << "Enter your guess: \n";

	std::cin >> guess;

	int letter = convertLetterToNumber(guess[0]);
	int number = guess[1] - '0';

	number--;

	/* If the user wants to exit, leave function */
	if (guess == "Q" || guess == "q") {
		return;
	}

	/* If the guess is 3 characters long (e.g. A10) */
	if (guess.length() > 2) {
		number += 9;
	}
	
	/* Loop until the user inputs correct form of a guess */
	while (letter > 9 || letter < 0 || number > 9 || number < 0) {
		std::cout << "Wrong input. Must be in the form B4, A5, C7, etc. Try again.\n";
		std::cin >> guess;
		letter = convertLetterToNumber(guess[0]);
		number = guess[1] - '0';

		number--;

		if (guess == "Q" || guess == "q") {
			return;
		}

		if (guess.length() > 2) {
			number += 9;
		}
	}
	

	/* If guess hits, sink the entire ship */
	if ((!AIGrid::AISGrid[number][letter].isHit || !AIGrid::AISGrid[number][letter].isMiss) && AIGrid::AISGrid[number][letter].shipOnSquare && !AIGrid::AISGrid[number][letter].shipSunk) {

		/* These search through the grid for the certain ship and if one part of the ship was sunk, the rest of the ship must be sunk as well, since this is one hit 
			kill mode*/

		/* These are really inefficient time-complexity wise but I couldn't think of an alternative :( */
		if (AIGrid::AISGrid[number][letter].carrier.shipOnSquare) {
			for (int i = 0; i < userSGrid.size(); i++) {
				for (int j = 0; j < userSGrid[i].size(); j++) {
					if (AIGrid::AISGrid[i][j].carrier.shipOnSquare) {
						AIGrid::AISGrid[i][j].shipSunk = true;
						userGGrid[i][j].isHit = true;
						AIGrid::AISGrid[i][j].isHit = true;
					}
				}
			}
		}

		if (AIGrid::AISGrid[number][letter].battleship.shipOnSquare) {
			for (int i = 0; i < userSGrid.size(); i++) {
				for (int j = 0; j < userSGrid[i].size(); j++) {
					if (AIGrid::AISGrid[i][j].battleship.shipOnSquare) {
						AIGrid::AISGrid[i][j].shipSunk = true;
						userGGrid[i][j].isHit = true;
						AIGrid::AISGrid[i][j].isHit = true;
					}
				}
			}
		}

		if (AIGrid::AISGrid[number][letter].cruiser.shipOnSquare) {
			for (int i = 0; i < userSGrid.size(); i++) {
				for (int j = 0; j < userSGrid[i].size(); j++) {
					if (AIGrid::AISGrid[i][j].cruiser.shipOnSquare) {
						AIGrid::AISGrid[i][j].shipSunk = true;
						userGGrid[i][j].isHit = true;
						AIGrid::AISGrid[i][j].isHit = true;
					}
				}
			}
		}

		if (AIGrid::AISGrid[number][letter].submarine.shipOnSquare) {
			for (int i = 0; i < userSGrid.size(); i++) {
				for (int j = 0; j < userSGrid[i].size(); j++) {
					if (AIGrid::AISGrid[i][j].submarine.shipOnSquare) {
						AIGrid::AISGrid[i][j].shipSunk = true;
						userGGrid[i][j].isHit = true;
						AIGrid::AISGrid[i][j].isHit = true;
					}
				}
			}
		}

		if (AIGrid::AISGrid[number][letter].destroyer.shipOnSquare) {
			for (int i = 0; i < userSGrid.size(); i++) {
				for (int j = 0; j < userSGrid[i].size(); j++) {
					if (AIGrid::AISGrid[i][j].destroyer.shipOnSquare) {
						AIGrid::AISGrid[i][j].shipSunk = true;
						userGGrid[i][j].isHit = true;
						AIGrid::AISGrid[i][j].isHit = true;
					}
				}
			}
		}

		std::cout << "\n\nYou Hit! Ship sunk!\n";
		
		numOfShipsSunk++;
	}

	/* If guess misses */
	else if ((!AIGrid::AISGrid[number][letter].isHit || !AIGrid::AISGrid[number][letter].isMiss) && !AIGrid::AISGrid[number][letter].shipOnSquare) {

		userGGrid[number][letter].isMiss = true;
		AIGrid::AISGrid[number][letter].isMiss = true;

		std::cout << "\n\nYou Missed!\n";
	}

	else {
		std::cout << "\n\nYou already guessed this spot.\n";
	}


}
