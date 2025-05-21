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

int main()
{
	srand((unsigned)time(NULL));


	int matrix1[3][3];
	fillMatrixWithRandomNumbers(matrix1, 3, 3, 1, 100);
	printMatrix(matrix1, 3, 3, "Matrix 1 Elements:\n");

	int numberToFind = readPositiveNumber("\nEnter number to find in the matrix: ");
	
	if (isNumberInMatrix(matrix1, 3, 3, numberToFind))
		cout << "\nYES, Number exists in the matrix!\n\n";
	else
		cout << "\nNO, Number does NOT exist in the matrix!\n\n";


}