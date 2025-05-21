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

bool isNumberInMatrix(int matrix[3][3], short matrixRows, short matrixColumns,int numberToFind)
{
	short totalElements = matrixRows * matrixColumns, zeroCount = 0;

	for (short i = 0; i < matrixRows; i++)
	{
		for (short j = 0; j < matrixColumns; j++)
		{
			if (matrix[i][j] == numberToFind)
				return true;
		}
	}

	return false;
}

void printIntersectedNumbersInMatrices(int matrix1[3][3], int matrix2[3][3], short matrixRows, short matrixColumns)
{
	for (short i = 0; i < matrixRows; i++)
	{
		for (short j = 0; j < matrixColumns; j++)
		{
			if (isNumberInMatrix(matrix2,3,3,matrix1[i][j]))
				printf("%0*d\t", 2, matrix1[i][j]);
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));


	int matrix1[3][3];
	int matrix2[3][3];

	fillMatrixWithRandomNumbers(matrix1, 3, 3, 1, 10);
	fillMatrixWithRandomNumbers(matrix2, 3, 3, 1, 10);

	printMatrix(matrix1, 3, 3, "Matrix 1 Elements:\n");
	printMatrix(matrix2, 3, 3, "Matrix 2 Elements:\n");

	
	
	cout << "\n\nThe intersected numbers in both matrices are:\n";
	printIntersectedNumbersInMatrices(matrix1, matrix2, 3, 3);

}