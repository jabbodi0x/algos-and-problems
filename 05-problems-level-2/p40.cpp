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

void fillArrayWithRandomNumbers(int* array, int arraySize, int fromNumber = 1, int toNumber = 100)
{
	for (int i = 0; i < arraySize; i++)
	{
		array[i] = getRandomNumber(fromNumber, toNumber);
	}
}

void addNumberToArray(int* array, int& arraySize, int numberToAdd)
{
	array[arraySize] = numberToAdd;
	arraySize++;

}

int getNumberFrequencyInArray(int* array, int arraySize, int number)
{
	int freq = 0;

	for (int i = 0; i < arraySize; i++)
	{
		if (number == array[i])
			freq++;
	}

	return freq;
}

bool isNumberUniqueInArray(int* array, int arraySize,int number)
{
	if (getNumberFrequencyInArray(array, arraySize, number) == 1)
		return true;

	return false;
}

bool FASTERisNumberUniqueInArray(int* array, int arraySize, int number)
{
	int freq = 0;

	for (int i = 0; i < arraySize; i++)
	{
		if (number == array[i])
			freq++;

		if (freq > 1)
			return false;
	}

	return true;
}

void copyUniqueNumbersInArrayToAnotherArray(int* array1, int* array2, int array1Size, int& array2Size)
{
	for (int i = 0; i < array1Size; i++)
	{
		if (FASTERisNumberUniqueInArray(array1, array1Size, array1[i]))
		{
			addNumberToArray(array2, array2Size, array1[i]);
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));

	int arraySize = readPositiveNumber("Enter the size of the array: ");
	int* array1 = new int[arraySize];
	int* array2 = new int[arraySize];

	int array2Size = 0;

	fillArrayWithRandomNumbers(array1, arraySize,1,100);

	cout << "\nArray Elements (Raw):\n";
	printArrayElements(array1, arraySize);

	copyUniqueNumbersInArrayToAnotherArray(array1, array2, arraySize, array2Size);

	cout << endl;

	cout << "\nArray Elements (Unique):\n";
	printArrayElements(array2, array2Size);

	delete[] array1;
	delete[] array2;


 	return 0;
}