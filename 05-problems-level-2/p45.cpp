#include <iostream>

using namespace std;

int readNegativeNumber(string message = "Enter a Negative number: ")
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

void printNegativeArrayElements(int* array, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		if (array[i]<0)
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

int getNegativeNumbersCountInArray(int* array, int arraySize)
{
	int count = 0;
	for (int i = 0; i < arraySize; i++)
	{
		if (array[i] <0)
			count++;
	}

	return count;
}

int main()
{

	srand((unsigned)time(NULL));

	int arraySize = 50;
	int* array = new int[arraySize];

	fillArrayWithRandomNumbers(array, arraySize, -20, 40);

	cout << "\n\nArray Elements:\n";
	printArrayElements(array, arraySize);

	cout << "\n\nArray Negative Elements Count: " << getNegativeNumbersCountInArray(array, arraySize);
	
	cout << "\n\nArray Negative Elements:\n";
	printNegativeArrayElements(array, arraySize);



	delete[] array;
 	return 0;
}