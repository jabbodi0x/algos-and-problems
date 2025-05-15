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

void printInvertedLettersPattern(int number)
{
	int times = number;
	for (int i = 65 + number - 1; i >= 65; i--)
	{
		for (int j = 1; j <= times; j++)
		{
			cout << char(i);
		}
		cout << "\n";
		times--;
	}
}


int main()
{
	printInvertedLettersPattern(readPositiveNumber());
}