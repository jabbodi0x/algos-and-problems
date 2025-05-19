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
			matrix[i][j] = getRandomNumber(1, 20);
		}
	}
}

int getColumnSumOfMatrix(int matrix[3][3], short matrixRows, short matrixColumn)
{
	int sum = 0;

	for (short i = 0; i < matrixRows; i++)
	{

		sum += matrix[i][matrixColumn];
	}

	return sum;
}

void printEachRowSumInMatrix(int matrix[3][3], short matrixRows, short matrixColumns)
{
	for (short i = 0; i < matrixRows; i++)
	{
		cout << "\nColumn " << i + 1 << " Sum =\t" << getColumnSumOfMatrix(matrix, matrixRows, i);
	}
}

int main()
{
	srand((unsigned)time(NULL));
	
	int matrix[3][3];

	int array1[3], array2[3], array3[3];

	fillMatrixWithRandomNumbers(matrix, 3, 3);
	printMatrix(matrix, 3, 3);

	printEachRowSumInMatrix(matrix, 3, 3);

}