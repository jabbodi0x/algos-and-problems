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

bool isMatrixPalindrome(int matrix[3][3], short matrixRows, short matrixColumns)
{
	for (short i = 0; i < matrixRows; i++)
	{
		for (short j = 0; j < matrixColumns/2; j++)
		{
			if (matrix[i][j] != matrix[i][matrixColumns - j - 1])
				return false;
		}
	}
	return true;
}




int main()
{
	srand((unsigned)time(NULL));


	int matrix1[3][3] = { {1,2,1},{3,5,4},{6,2,6} };
	printMatrix(matrix1, 3, 3, "Matrix 1 Elements:\n");

	if (isMatrixPalindrome(matrix1, 3, 3))
		cout << "\nMatrix is Palindrome.";
	else
		cout << "\nMatrix is NOT Palindrome.";

	cout << endl << endl;

}