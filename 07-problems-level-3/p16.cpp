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

void fillMatrixWithRandomNumbers(int matrix[3][3], short matrixRows, short matrixColumns)
{
	for (short i = 0; i < matrixRows; i++)
	{
		for (short j = 0; j < matrixColumns; j++)
		{
			matrix[i][j] = getRandomNumber(1, 5);
		}
	}
}

bool isSparseMatrix(int matrix[3][3], short matrixRows, short matrixColumns)
{
	short totalElements = matrixRows * matrixColumns, zeroCount = 0;

	for (short i = 0; i < matrixRows; i++)
	{
		for (short j = 0; j < matrixColumns; j++)
		{
			if (matrix[i][j] == 0)
				zeroCount++;
		}
	}

	return (zeroCount > (totalElements - zeroCount));
}

int main()
{
	srand((unsigned)time(NULL));


	int matrix1[3][3] = { {5,5,0},{0,5,0},{5,0,5} };

	printMatrix(matrix1, 3, 3, "Matrix 1 Elements:\n");

	if (isSparseMatrix(matrix1, 3, 3))
		cout << "\nYES, Matrix is Sparse matrix\n\n";
	else
		cout << "\nNO, Matrix is NOT Sparse matrix\n\n";


}