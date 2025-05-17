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

bool isNumberFoundInArray(int* array, int arraySize, int numberToLook)
{
	for (int i = 0; i < arraySize; i++)
	{
		if (array[i] == numberToLook)
			return true;
	}
	return false;
}

void findIndexOfNumberInArray(int* array, unsigned short arraySize)
{

	unsigned short numberToLook = readPositiveNumber("\nEnter number to look for: ");

	cout << "\nNumber you are looking for: " << numberToLook;
	
	cout << ((isNumberFoundInArray(array, arraySize, numberToLook)) ? "\nYes, the number is found" : "\nNo, the number is NOT found :-(");


}

int main()
{
	srand((unsigned)time(NULL));

	int arraySize = readPositiveNumber("Enter the size of the array: ");
	int* array1 = new int[arraySize];
	
	fillArrayWithRandomNumbers(array1, arraySize, 1, 100);

	
	findIndexOfNumberInArray(array1, arraySize);

	cout << "\n\nArray Elements:\n";
	printArrayElements(array1, arraySize);
	

	return 0;
}