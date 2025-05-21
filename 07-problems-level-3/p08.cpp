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
	cout << prompt;
	for (short i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixColumns; j++)
		{
			printf("%0*d ", 2,matrix[i][j]);  // Always 3-digit format
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


void multiplyMatrices(int matrix1[3][3], int matrix2[3][3], int resultMatrix[3][3], short matrixRows, short matrixColumns)
{
	for (short i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixColumns; j++)
		{
			resultMatrix[i][j] = matrix1[i][j] * matrix2[i][j];
		}
	}
}


int main()
{
	srand((unsigned)time(NULL));
	
	int matrix1[3][3];
	int matrix2[3][3];
	int resultMatrix[3][3];

	fillMatrixWithRandomNumbers(matrix1, 3, 3);
	fillMatrixWithRandomNumbers(matrix2, 3, 3);

	multiplyMatrices(matrix1, matrix2, resultMatrix, 3, 3);

	printMatrix(matrix1, 3, 3, "Matrix 1 Elements:\n");
	cout << endl;
	printMatrix(matrix2, 3, 3, "Matrix 2 Elements:\n");
	cout << endl;

	printMatrix(resultMatrix, 3, 3, "Result Matrix Elements:\n");
	cout << endl;

}