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

bool isPerfect(int number)
{

	if (number <= 1) return false;

	int divisorsSum = 1;
	int limit = sqrt(number);


	for (int i = 2; i <= limit; i++)
	{
		if (number % i == 0)
		{
			divisorsSum += i;
			int pair = number / i;
			divisorsSum += (pair != 0) ? pair : 0;
		}
	}

	return number == divisorsSum;
}

void printPerfectNumbersFrom1ToN(int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (isPerfect(i))
			cout << i << " ";
	}
}

int main()
{
	printPerfectNumbersFrom1ToN(10000);
	return 0;
}