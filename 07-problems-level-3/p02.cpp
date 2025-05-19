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
			cout << setw(3) << matrix[i][j] << "\t";
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
			matrix[i][j] = getRandomNumber(1, 100);
		}
	}
}

int getRowSumOfMatrix(int matrix[3][3], short matrixRow, short matrixColumns)
{
	int sum = 0;

	for (short i = 0; i < matrixColumns; i++)
	{
		
		sum += matrix[matrixRow][i];
	}

	return sum;
}

void printEachRowSumInMatrix(int matrix[3][3], short matrixRows, short matrixColumns)
{
	for (short i = 0; i < matrixRows; i++)
	{
		cout << "\nRow " << i + 1 << " Sum =\t" << getRowSumOfMatrix(matrix, i, matrixColumns);
	}
}

int main()
{
	srand((unsigned)time(NULL));
	
	int matrix[3][3];

	fillMatrixWithRandomNumbers(matrix, 3, 3);
	printMatrix(matrix, 3, 3);

	cout << "\nThe sum of each row in the matrix is: \n";
	printEachRowSumInMatrix(matrix, 3, 3);
}