#include <iostream>
#include <iomanip>

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

int getRandomNumber(short fromNumber, short toNumber)
{
	return (rand() % (toNumber - fromNumber + 1) + fromNumber);
}

void printMatrix(int array[3][3], short arrayRows, short arrayColumns, string prompt="Matrix Elements:\n\n")
{
	cout << prompt;
	for (short i = 0; i < arrayRows; i++)
	{
		for (int j = 0; j < arrayColumns; j++)
		{
			cout << setw(3) << array[i][j] << "\t";
		}
		cout << endl;
	}
}

void fillMatrixWithRandomNumbers(int array[3][3],short arrayRows, short arrayColumns)
{
	for (short i = 0; i < arrayRows; i++)
	{
		for (int j = 0; j < arrayColumns; j++)
		{
			array[i][j] = getRandomNumber(1, 100);
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));
	
	int array[3][3];

	fillMatrixWithRandomNumbers(array, 3, 3);
	printMatrix(array, 3, 3);
}