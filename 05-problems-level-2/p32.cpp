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

void reverseArray(int* array, int* reverseArray, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		reverseArray[arraySize-1-i] = array[i];
	}
}

int main()
{
	srand((unsigned)time(NULL));

	int arraySize = readPositiveNumber("Enter the size of the array: ");
	int* array1 = new int[arraySize];
	int* array2 = new int[arraySize];
	fillArrayWithRandomNumbers(array1, arraySize,1,30);
	
	printArrayElements(array1, arraySize);
	reverseArray(array1, array2, arraySize);
	cout << "\n\n";
	printArrayElements(array2, arraySize);

	return 0;
}