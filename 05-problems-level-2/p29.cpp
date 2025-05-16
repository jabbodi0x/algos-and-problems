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

void copyArray(int* originalArray, int* copyarray, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		copyarray[i] = originalArray[i];
	}
}

int main()
{
	srand((unsigned)time(NULL));

	int arraySize = readPositiveNumber("Enter array size: ");
	int* array = new int[arraySize];
	int* array2 = new int[arraySize];
	fillArrayWithRandomNumbers(array, arraySize);

	cout << "\nOriginal Array Elements:\n";
	printArrayElements(array, arraySize);

	
	copyArray(array, array2, arraySize);

	cout << "\nCopy Array Elements:\n";
	printArrayElements(array, arraySize);
	

	return 0;

}