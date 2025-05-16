#include <iostream>

using namespace std;

enum enCharacters
{
	smallLetter = 1,
	capitalLetter = 2,
	digit = 3,
	specialCharacter = 4 // Changed value to avoid duplication with 'digit'
};

int getRandomNumber(int fromNumber, int toNumber)
{
	return (rand() % (toNumber - fromNumber + 1) + fromNumber);
}

char getRandomCharacter(enCharacters characterType)
{
	switch (characterType)
	{
	case enCharacters::smallLetter:
		return char(getRandomNumber(97, 122));
		break;
	case enCharacters::capitalLetter:
		return char(getRandomNumber(65, 90));
		break;
	case enCharacters::digit:
		return char(getRandomNumber(48, 57));
		break;
	case enCharacters::specialCharacter:
		return char(getRandomNumber(33, 47));
		break;
	default:
		return '\0';
	}
}

int main()
{
	srand((unsigned)time(NULL));

	cout << getRandomCharacter(enCharacters::smallLetter) << endl;
	cout << getRandomCharacter(enCharacters::capitalLetter) << endl;
	cout << getRandomCharacter(enCharacters::digit) << endl;
	cout << getRandomCharacter(enCharacters::specialCharacter) << endl;

}