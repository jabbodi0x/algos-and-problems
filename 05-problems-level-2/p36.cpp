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

void addNumberToArray(int array[100], int& arrLength, int numberToAdd)
{
	array[arrLength] = numberToAdd;
	arrLength++;

}

void addUserNumberToArray(int array[100], int& arrLength)
{
	bool addMore = true;

	do
	{
		addNumberToArray(array, arrLength, readPositiveNumber("Enter a number to add: "));
		cout << "\nDo you want to add more? (0 for no, 1 for yes): ";
		cin >> addMore;
		cout << "\n\n";
	} while (addMore);
}

int main()
{

	int array[100], arraySize = 0;
	addUserNumberToArray(array, arraySize);
	printArrayElements(array, arraySize);
	return 0;
}