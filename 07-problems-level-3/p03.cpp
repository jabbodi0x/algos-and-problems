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

int getSumOfArray(int array[3])
{
	int sum = 0;
	for (short i = 0; i < 3; i++)
	{
		sum += array[i];
	}
	return sum;
}


void matrixRowToArray(int matrix[3][3], int array[3], short matrixRow,short matrixColumns)
{
	for (int i = 0; i < matrixColumns; i++)
	{
		array[i]=matrix[matrixRow][i];
	}
}

int main()
{
	srand((unsigned)time(NULL));
	
	int matrix[3][3];

	int array1[3], array2[3], array3[3];

	fillMatrixWithRandomNumbers(matrix, 3, 3);
	printMatrix(matrix, 3, 3);

	cout << "\nThe sum of each row in the matrix is: \n";
	matrixRowToArray(matrix, array1,0,3);
	cout << "\nRow 1: " << getSumOfArray(array1);
	matrixRowToArray(matrix, array2,1,3);
	cout << "\nRow 2: " << getSumOfArray(array2);
	matrixRowToArray(matrix, array3,2,3);
	cout << "\nRow 3: " << getSumOfArray(array3);

}