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

void printMatrix(int matrix[3][3], short matrixRows, short matrixColumns, string prompt = "Matrix Elements:\n\n")
{
	cout << "______________________" << endl;
	cout << prompt;
	for (short i = 0; i < matrixRows; i++)
	{
		for (short j = 0; j < matrixColumns; j++)
		{
			printf("%0*d\t", 2, matrix[i][j]);
			//cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << "______________________" << endl;
}

void fillMatrixWithRandomNumbers(int matrix[3][3], short matrixRows, short matrixColumns, short from = 1, short to = 100)
{
	for (short i = 0; i < matrixRows; i++)
	{
		for (short j = 0; j < matrixColumns; j++)
		{
			matrix[i][j] = getRandomNumber(from, to);
		}
	}
}

int getMinNumberInMatrix(int matrix[3][3], short matrixRows, short matrixColumns)
{
	int minNumber = matrix[0][0];

	for (short i = 0; i < matrixRows; i++)
	{
		for (short j = 0; j < matrixColumns; j++)
		{
			if (matrix[i][j] < minNumber)
				minNumber = matrix[i][j];
		}
	}

	return minNumber;
}

int getMaxNumberInMatrix(int matrix[3][3], short matrixRows, short matrixColumns)
{
	int maxNumber = matrix[0][0];

	for (short i = 0; i < matrixRows; i++)
	{
		for (short j = 0; j < matrixColumns; j++)
		{
			if (matrix[i][j] > maxNumber)
				maxNumber = matrix[i][j];
		}
	}

	return maxNumber;
}

int main()
{
	srand((unsigned)time(NULL));


	int matrix1[3][3];
	fillMatrixWithRandomNumbers(matrix1, 3, 3, 1, 100);
	printMatrix(matrix1, 3, 3, "Matrix 1 Elements:\n");

	cout << "\nMin Number in Matrix:\t" << getMinNumberInMatrix(matrix1, 3, 3);
	cout << "\nMax Number in Matrix:\t" << getMaxNumberInMatrix(matrix1, 3, 3);

	cout << endl << endl;

}