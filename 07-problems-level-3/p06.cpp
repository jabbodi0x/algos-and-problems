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

void printMatrix(int matrix[3][3], short matrixRows, short matrixColumns, string prompt="Matrix Elements:\n\n")
{
	cout << prompt;
	for (short i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixColumns; j++)
		{
			cout << left << setw(3) << matrix[i][j] << "  ";
		}
		cout << endl;
	}
}

void fillMatrixWithRandomNumbers(int matrix[3][3],short matrixRows, short matrixColumns)
{
	for (short i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixColumns; j++)
		{
			matrix[i][j] = getRandomNumber(1, 20);
		}
	}
}

void fillMatrixWithOrderedNumbers(int matrix[3][3], short matrixRows, short matrixColumns)
{
	short number = 0;
	for (int i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixColumns; j++)
		{
			matrix[i][j] = ++number;
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));
	
	int matrix[3][3];
	fillMatrixWithOrderedNumbers(matrix, 3, 3);
	printMatrix(matrix, 3, 3);

	

}