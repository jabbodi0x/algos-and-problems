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

int getMaxOfArray(int* array, int arraySize)
{
	int max = array[0];

	for (int i = 0; i < arraySize; i++)
	{
		if (array[i] > max)
		{
			max = array[i];
		}
	}
	return max;
}

int main()
{
	srand((unsigned)time(NULL));

	int* array = new int[100];

	fillArrayWithRandomNumbers(array, 100);

	cout << "\nArray Elements:\n";
	printArrayElements(array, 100);

	cout << "\nMax of Array is:\n" << getMaxOfArray(array, 100);
}