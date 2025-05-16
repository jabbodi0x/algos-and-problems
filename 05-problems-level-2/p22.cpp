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

void readArray(int* array, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		cout << "Element [" << i + 1 << "] : ";
		cin >> array[i];
	}
}

int getOccurrence(int* array, int arraySize,int numberToCheck)
{
	unsigned short occurrence = 0;
	for (int i = 0; i < arraySize; i++)
	{
		if (array[i] == numberToCheck)
			occurrence++;
	}

	return occurrence;
}

void printArrayElements(int* array, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		cout << array[i] << " ";
	}
	cout << "\n";
}

int main()
{
	int arraySize = readPositiveNumber("Enter array size: ");
	int* array = new int[arraySize];
	readArray(array, arraySize);
	int numberToCheck = readPositiveNumber("\nEnter number to check: ");

	cout << "\nOriginal Array:\t";
	printArrayElements(array, arraySize);
	cout << numberToCheck << " is repeated " << getOccurrence(array, arraySize, numberToCheck) << " time(s)\n";

}