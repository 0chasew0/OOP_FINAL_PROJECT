#include "UserGrid.h"

#include <iostream>

void UserGrid::inputShips(std::ifstream& f)
{
	f.open("ship_placement.csv"); // Open the file so that we may read from it

	/* Gets the user's ship data from the .csv file */
	while (f.good()) {
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
	}

	f.close(); // Close the file when we are done reading from it

	/* If the user doesn't enter the ship 'Carrier' correctly */
	try {
		if (userCarrier.shipType != "Carrier" || userCarrier.shipType != "carrier") {
			throw ("Ship 'Carrier' should be included in the first row of .csv ship file");
		}
	}
	catch (const char* exp) {
		std::cout << "Error: " << exp << std::endl;
	}
	

}
