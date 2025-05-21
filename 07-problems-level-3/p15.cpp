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

void fillMatrixWithRandomNumbers(int matrix[3][3],short matrixRows, short matrixColumns,short from=1,short to=100)
{
	for (short i = 0; i < matrixRows; i++)
	{
		for (short j = 0; j < matrixColumns; j++)
		{
			matrix[i][j] = getRandomNumber(from, to);
		}
	}
}

short getFrequencyOfNumberInMatrix(int matrix[3][3], short matrixRows, short matrixColumns, short numberToCheck)
{
	short freq = 0;

	for (short i = 0; i < matrixRows; i++)
	{
		for (short j = 0; j < matrixColumns; j++)
		{
			if (numberToCheck == matrix[i][j])
				freq++;
		}
	}

	return freq;
}

int main()
{
	srand((unsigned)time(NULL));
	
	
	int matrix1[3][3];
	fillMatrixWithRandomNumbers(matrix1, 3, 3, 1, 5);

	printMatrix(matrix1, 3, 3, "Matrix 1 Elements:\n");

	short numberToCheck = readPositiveNumber("Enter Number to check its frequency in the matrix: ");

	printf("The frequency of %d is %d", numberToCheck, getFrequencyOfNumberInMatrix(matrix1, 3, 3, numberToCheck));


	return 0;
}