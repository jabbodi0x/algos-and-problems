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
		array[i] = getRandomNumber(1,20);
	}
}

void shuffleArray(int * array, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		int index1 = getRandomNumber(0, arraySize - 1);
		int index2 = getRandomNumber(0, arraySize - 1);

		array[index1] += array[index2];
		array[index2] = array[index1] - array[index2];
		array[index1] -= array[index2];
	}
}

int main()
{
	srand((unsigned)time(NULL));

	int arraySize = readPositiveNumber("Enter the size of the array: ");
	int* array1 = new int[arraySize];

	fillArrayWithRandomNumbers(array1, arraySize);

	printArrayElements(array1, arraySize);
	cout << "\n\n";

	shuffleArray(array1, arraySize);
	printArrayElements(array1, arraySize);
	return 0;

}