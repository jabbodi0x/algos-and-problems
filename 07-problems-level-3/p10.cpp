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
			printf("%0*d\t", 2, matrix[i][j]);
			//cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
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


int main()
{
	srand((unsigned)time(NULL));
	
	int matrix1[3][3];
	
	fillMatrixWithRandomNumbers(matrix1, 3, 3);

	
	printMatrix(matrix1, 3, 3, "Matrix 1 Elements:\n\n");
	cout << "\n\nSum of the matrix is: " << getSumOfMatrix(matrix1, 3, 3) << endl << endl;

}