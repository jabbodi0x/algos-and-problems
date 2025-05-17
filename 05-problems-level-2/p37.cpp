#include <iostream>

using namespace std;

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

void fillArrayWithRandomNumbers(int* array, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		array[i] = getRandomNumber(1, 100);
	}
}

void addNumberToArray(int array[100], int& arrLength, int numberToAdd)
{
	array[arrLength] = numberToAdd;
	arrLength++;

}

void copyArrayToAnotherArray(int* originalArray, int* copyArray, int arraySize,int &copyArraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		addNumberToArray(copyArray, copyArraySize, originalArray[i]);
	}
}


int main()
{
	srand((unsigned)time(NULL));

	int array[100], copyArray[100], copyArraySize = 0;
	fillArrayWithRandomNumbers(array, 100);

	cout << "Array 1 Elements:\n";
	printArrayElements(array, 100);
	
	copyArrayToAnotherArray(array, copyArray, 100, copyArraySize);

	cout << "\n\nArray 2 Elements:\n";
	printArrayElements(copyArray, 100);
	return 0;
}