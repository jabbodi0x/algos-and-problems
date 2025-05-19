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

void swapNumbers(int& num1, int& num2)
{
	int temp = num1;
	num1 = num2;
	num2 = temp;
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

void turnMatrixToTranspose(int matrix[3][3], short matrixRows, short matrixColumns)
{
	for (int i = 0; i < matrixRows; i++)
	{
		for (int j = i+1; j < matrixColumns; j++)
		{
			if (i == 0 && j == 0)
				continue;
			swapNumbers(matrix[i][j], matrix[j][i]);
		}
	}
}

void turnMatrixToTranspose(int matrix1[3][3], int matrix2[3][3], short matrixRows, short matrixColumns)
{
	for (int i = 0; i < matrixRows; i++)
	{
		for (int j = 0; j < matrixColumns; j++)
		{
			matrix2[i][j] = matrix1[j][i];
		}
	}
}

int main()
{
	srand((unsigned)time(NULL));
	
	int matrix1[3][3];
	int matrix2[3][3];

	fillMatrixWithOrderedNumbers(matrix1, 3, 3);
	printMatrix(matrix1, 3, 3);

	turnMatrixToTranspose(matrix1,matrix2, 3, 3);

	printMatrix(matrix2, 3, 3);

}