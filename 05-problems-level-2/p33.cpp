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

void printArrayElements(int* array, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		cout << array[i] << " ";
	}
	cout << "\n";
}

int getRandomNumber(int fromNumber, int toNumber)
{
	return (rand() % (toNumber - fromNumber + 1) + fromNumber);
}

void fillArrayWithRandomNumbers(int* array, int arraySize,int fromNumber =1, int toNumber =100)
{
	for (int i = 0; i < arraySize; i++)
	{
		array[i] = getRandomNumber(fromNumber,toNumber);
	}
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

void printStringArrayElements(string* array, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		cout << "Array[" << i << "]: " << array[i] << endl;
	}
	cout << "\n";
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

void fillArrayWithGenerateKeys(string *array, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		array[i] = generateKey();
	}
}

int main()
{
	srand((unsigned)time(NULL));

	int arraySize = readPositiveNumber("Enter the size of the array: ");
	string* array1 = new string[arraySize];
	fillArrayWithGenerateKeys(array1, arraySize);

	printStringArrayElements(array1, arraySize);
	

	return 0;
}