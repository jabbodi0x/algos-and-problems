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

int main()
{
	srand((unsigned)time(NULL));

	int* array = new int[100];

	fillArrayWithRandomNumbers(array, 100);

	cout << "\nArray Elements:\n";
	printArrayElements(array, 100);

}