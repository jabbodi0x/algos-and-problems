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

void fillArrayWithRandomNumbers(int* array, int arraySize,int fromNumber =1, int toNumber =100)
{
	for (int i = 0; i < arraySize; i++)
	{
		array[i] = getRandomNumber(fromNumber,toNumber);
	}
}

int getIndexOfNumber(int* array, int arraySize, int numberToLook)
{
	for (int i = 0; i < arraySize; i++)
	{
		if (array[i] == numberToLook)
			return i;
	}
	return -1;
}

void printResultOfFindingIndexOfNumber(int* array, int arraySize, int numberToLook)
{
	cout << "\nNumber you are looking for: " << numberToLook;
	int index = getIndexOfNumber(array, arraySize, numberToLook);

	if (index != -1)
		cout << "\nThe number found at index: " << index;
	else
		cout << "\nThe number is not found :-(";


}

int main()
{
	srand((unsigned)time(NULL));

	int arraySize = readPositiveNumber("Enter the size of the array: ");
	int* array1 = new int[arraySize];
	
	fillArrayWithRandomNumbers(array1, arraySize, 1, 100);

	
	printResultOfFindingIndexOfNumber(array1, arraySize, readPositiveNumber("\nEnter number to look for: "));

	cout << "\n\nArray Elements:\n";
	printArrayElements(array1, arraySize);
	

	return 0;
}