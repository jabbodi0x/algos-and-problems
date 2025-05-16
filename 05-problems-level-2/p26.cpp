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

int getSumOfArray(int* array, int arraySize)
{
	int sum = 0;

	for (int i = 0; i < arraySize; i++)
	{
		sum += array[i];
	}

	return sum;
}

int main()
{
	srand((unsigned)time(NULL));

	int* array = new int[100];

	fillArrayWithRandomNumbers(array, 100);

	cout << "\nArray Elements:\n";
	printArrayElements(array, 100);

	cout << "\nSum of Array is: " << getSumOfArray(array, 100);

	return 0;

}