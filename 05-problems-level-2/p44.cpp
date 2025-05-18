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

void printPositiveArrayElements(int* array, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		if (array[i]>0)
			cout << array[i] << " ";
	}
	cout << "\n";
}

int getRandomNumber(int fromNumber, int toNumber)
{
	return (rand() % (toNumber - fromNumber + 1) + fromNumber);
}

void fillArrayWithRandomNumbers(int* array, int arraySize, int fromNumber = 1, int toNumber = 100)
{
	for (int i = 0; i < arraySize; i++)
	{
		array[i] = getRandomNumber(fromNumber, toNumber);
	}
}

int getPositiveNumbersCountInArray(int* array, int arraySize)
{
	int count = 0;
	for (int i = 0; i < arraySize; i++)
	{
		if (array[i] >0)
			count++;
	}

	return count;
}

int main()
{
	int arraySize = 50;
	int* array = new int[arraySize];

	fillArrayWithRandomNumbers(array, arraySize, -50, 10);

	cout << "\n\nArray Elements:\n";
	printArrayElements(array, arraySize);

	cout << "\n\nArray Positive Elements Count: " << getPositiveNumbersCountInArray(array, arraySize);
	
	cout << "\n\nArray Positive Elements:\n";
	printPositiveArrayElements(array, arraySize);



	delete[] array;
 	return 0;
}