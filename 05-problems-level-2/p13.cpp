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

void printPattern(int number)
{
	for (int i = 1; i <= number; i++)
	{
		for (int j = 1; j <= i; j++)
		{
			cout << i;
		}
		cout << "\n";
	}
}


int main()
{
	printPattern(readPositiveNumber());
}