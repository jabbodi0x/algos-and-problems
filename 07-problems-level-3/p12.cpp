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
		for (int j = 0; j < matrixColumns; j++)
		{
			printf("%0*d\t", 2, matrix[i][j]);
			//cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << "______________________" << endl;
}

void fillMatrixWithRandomNumbers(int matrix[3][3],short matrixRows, short matrixColumns)
{
	for (short i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixColumns; j++)
		{
			matrix[i][j] = getRandomNumber(1, 5);
		}
	}
}

int getSumOfMatrix(int matrix[3][3], short matrixRows, short matrixColumns)
{
	int sum = 0;

	for (short i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixColumns; j++)
		{
			sum += matrix[i][j];
		}
	}

	return sum;
}

bool isMatricesTypical(int matrix1[3][3], int matrix2[3][3] ,short matrixRows, short matrixColumns)
{
	for (short i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixColumns; j++)
		{
			if (matrix1[i][j] != matrix2[i][j])
				return false;
		}
	}

	return true;
}

int main()
{
	srand((unsigned)time(NULL));
	
	
	int matrix1[3][3] = { {1,2,3},{4,5,6},{7,8,9} };
	int matrix2[3][3] = { {1,2,3},{4,5,6},{7,8,9} };

	printMatrix(matrix1, 3, 3, "Matrix 1 Elements:\n");
	printMatrix(matrix2, 3, 3, "Matrix 2 Elements:\n");

	if (isMatricesTypical(matrix1, matrix2, 3, 3))
		cout << "\nYES, Matrices are typical\n\n";
	else
		cout << "\nNO, Matrices are NOT typical\n\n";


}