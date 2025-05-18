#include <iostream>

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

void printArrayElements(int* array, int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{
		cout << array[i] << " ";
	}
	cout << "\n";
}

bool isArrayPalindrome(int array[8], int arraySize)
{
	for (int i = 0; i < arraySize / 2; i++)
	{
		if (array[i] != array[arraySize - 1 - i])
			return false;
	}

	return true;
}

int main()
{
	int array1[] = { 1,2,3,4,3,2,1 };
	int array2[] = { 1,2,3,4,4,3,2,1 };
	int array3[] = { 1,2,3,4,5,4,3,2,1 };
	int array4[] = { 1,2,3,4,5,3,2,1 };

	if (isArrayPalindrome(array4, 8))
	{
		cout << "\nArray is Palindrome\n";
	}
	else
		cout << "\nArray is NOT Palindrome\n";
	printArrayElements(array4, 8);

 	return 0;
}