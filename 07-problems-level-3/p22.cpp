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

void printFibonacciSequence(short countNumbers, int n1 = 0, int n2 = 1)
{
	if (countNumbers > 0)
	{
		cout << n2 << " ";
		printFibonacciSequence(countNumbers - 1, n2, n1 + n2);
	}

	
}




int main()
{
	short number = readPositiveNumber("Enter the amount of fibonacci sequence numbers you want: ");
	cout << "\n\nThe fibonacci sequence is:\n\n";
	printFibonacciSequence(number);
}