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

int getSumOfigits(int number)
{
	int remainder = 0;
	int sum = 0;
	while (number > 0)
	{
		remainder = number % 10;
		sum += remainder;
		number /= 10;
	}

	return sum;
}

int main()
{

	cout << getSumOfigits(113632);
	return 0;
}