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

int reverseNumber(int number)
{
	int remainder = 0;
	int newNumber = 0;

	while (number > 0)
	{
		remainder = number % 10;
		number /= 10;
		newNumber = newNumber * 10 + remainder;
	}

	return newNumber;
}

int main()
{
	cout << reverseNumber(readPositiveNumber("Enter a number to reverse: "));
	return 0;
}