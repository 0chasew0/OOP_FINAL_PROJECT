#include "Grid.h"

int Grid::convertLetterToNumber(char c)
{
	int letter = 0;

	switch (c) {
	case 'A':
	case 'a':
		letter = 0;
		break;

	case 'B':
	case 'b':
		letter = 1;
		break;

	case 'C':
	case 'c':
		letter = 2;
		break;

	case 'D':
	case 'd':
		letter = 3;
		break;

	case 'E':
	case 'e':
		letter = 4;
		break;

	case 'F':
	case 'f':
		letter = 5;
		break;

	case 'G':
	case 'g':
		letter = 6;
		break;

	case 'H':
	case 'h':
		letter = 7;
		break;

	case 'I':
	case 'i':
		letter = 8;
		break;

	case 'J':
	case 'j':
		letter = 9;
		break;
	}

	return letter;
}
