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

void printMatrix(int matrix[4][4], short matrixRows, short matrixColumns, string prompt = "Matrix Elements:\n\n")
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

void fillMatrixWithRandomNumbers(int matrix[4][4], short matrixRows, short matrixColumns, short from = 1, short to = 100)
{
	for (short i = 0; i < matrixRows; i++)
	{
		for (short j = 0; j < matrixColumns; j++)
		{
			matrix[i][j] = getRandomNumber(from, to);
		}
	}
}

bool isMatrixPalindrome(int matrix[4][4], short matrixRows, short matrixColumns)
{
	for (short i = 0; i < matrixRows; i++)
	{
		for (short j = 0; j < matrixColumns; j++)
		{
			if (matrix[i][j] != matrix[matrixRows - i - 1][matrixColumns - j - 1])
				return false;
			if ((i == ((matrixRows - 1) / 2) + 1) && (j == ((matrixColumns - 1) / 2) + 1))
				return true;
		}
	}
	return true;
}
/*
This is ChatGPT's version
bool isMatrixPalindrome(int matrix[3][3], short matrixRows, short matrixColumns)
{
	for (short i = 0; i < matrixRows; i++)
	{
		for (short j = 0; j < matrixColumns; j++)
		{
			if (i > matrixRows - i - 1 || (i == matrixRows - i - 1 && j > matrixColumns - j - 1))
				return true;

			if (matrix[i][j] != matrix[matrixRows - i - 1][matrixColumns - j - 1])
				return false;
		}
	}
	return true;
}
*/



int main()
{
	srand((unsigned)time(NULL));


	int matrix1[4][4] = { {1,2,3,4},{5,6,7,8},{8,7,6,5},{4,3,2,1} };
	printMatrix(matrix1, 4, 4, "Matrix 1 Elements:\n");

	if (isMatrixPalindrome(matrix1, 4, 4))
		cout << "\nMatrix is Palindrome.";
	else
		cout << "\nMatrix is NOT Palindrome.";

	cout << endl << endl;

}