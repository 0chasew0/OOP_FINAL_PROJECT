#pragma once
#include <string>
class Ship
{
public:
	std::string shipType; // Carrier, battleship, etc.
	std::string shipPosition; // Starting position
	std::string shipOrientation; // Vertical or horizontal from starting position
	bool shipOnSquare; // If the ship itself is on a square
	bool isHit;
	
};

