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

bool isPrime(int number)
{
	if (number == 1)
		return false;
	
	for (int i = 2; i <= sqrt(number); i++)
	{
		if (number % i == 0)
			return false;
	}

	return true;
}

void copyArrayOnlyPrimes(int array1[100], int array2[100], int arraySize, int& copyArraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		if (isPrime(array1[i]))
		{
			array2[copyArraySize] = array1[i];
			copyArraySize++;
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));

	int array[100], copyArray[100], copyArraySize = 0;

	fillArrayWithRandomNumbers(array, 100);

	cout << "Array Elements:\n";
	printArrayElements(array, 100);

	cout << "\n\nCopy Array Elements(Only Primes:\n";
	copyArrayOnlyPrimes(array, copyArray, 100, copyArraySize);
	printArrayElements(copyArray, copyArraySize);
	
	return 0;
}