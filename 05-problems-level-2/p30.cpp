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

void sumOf2Arrays(int* array1, int* array2, int* mergedArray, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		mergedArray[i] = array1[i] + array2[i];
	}
}

int main()
{
	srand((unsigned)time(NULL));

	int arraySize = readPositiveNumber("Enter the size of the array: ");
	int* array1 = new int[arraySize];
	int* array2 = new int[arraySize];
	int* sumArray = new int[arraySize];

	fillArrayWithRandomNumbers(array1, arraySize);
	fillArrayWithRandomNumbers(array2, arraySize);
	sumOf2Arrays(array1, array2, sumArray, arraySize);

	cout << "\nArray 1: \n";
	printArrayElements(array1, arraySize);
	cout << "\n\nArray 2: \n";
	printArrayElements(array2, arraySize);
	cout << "\n\nMerged Array: \n";
	printArrayElements(sumArray, arraySize);


	return 0;

}