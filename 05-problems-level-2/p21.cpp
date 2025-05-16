#include <iostream>

using namespace std;

enum enCharacters
{
	smallLetter = 1,
	capitalLetter = 2,
	digit = 3,
	specialCharacter = 4
};

int readPositiveNumber(string message = "Enter a positive number: ")
{
	int number;

	do
	{
		cout << message;
		cin >> number;
	} while (number < 0);

	return number;
}

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

string generateKey()
{
	string key = "";

	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			key += getRandomCharacter(enCharacters::capitalLetter);
		}
		if (i != 4)
		{
			key += "-";
		}
	}

	return key;
}

void printGeneratedKeys(int numberOfKeys)
{
	for (int i = 1; i <= numberOfKeys; i++)
	{
		cout << "Key [" << i << "] : " << generateKey() << "\n";
	}
}

int main()
{
	srand((unsigned)time(NULL));

	printGeneratedKeys(5);

}