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
			if (pair != i)
				divisorsSum += pair;
		}
	}

	return number == divisorsSum;
}



int main()
{
	cout << isPerfect(28);
	cout << endl;
	cout << isPerfect(12);
	return 0;
}