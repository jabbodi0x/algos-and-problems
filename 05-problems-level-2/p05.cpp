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

void printDigitsInReverseOrder(int number)
{
	int remainder = 0;

	while (number > 0)
	{
		remainder = number % 10;
		cout << remainder;
		number /= 10;
	}
}

int main()
{

	printDigitsInReverseOrder(readPositiveNumber("Enter a number to print its reverse: "));
	return 0;
}