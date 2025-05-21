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

void printFibonacciSequence(short toNumber)
{
	long n1 = 0;
	long n2 = 1;

	for (int i = n2; i <= toNumber; i++)
	{
		cout << n2 << "  ";
		long temp = n2;
		n2 += n1;
		n1 = temp;
	}
}

int main()
{
	int number = readPositiveNumber("Enter the amount of fibonacci sequence numbers you want: ");
	cout << "\n\nThe fibonacci sequence is:\n\n";
	printFibonacciSequence(number);
}