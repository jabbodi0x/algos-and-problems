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

void printLettersPattern(int number)
{
	for (int i = 'A'; i <= 'A' + number-1; i++)
	{
		for (int j = 1; j <= i-'A' + 1; j++)
		{
			cout << char(i);
		}
		cout << endl;
	}
}


int main()
{
	printLettersPattern(6);
}