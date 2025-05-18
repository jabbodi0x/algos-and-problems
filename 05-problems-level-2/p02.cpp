#include <iostream>

using namespace std;

enum isPrime
{
	en_Prime = 1,
	en_NotPrime=2
};

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

isPrime checkNumberForPrime(int number)
{
	if (number == 1)
	{
		return isPrime::en_NotPrime;
	}

	for (int i = 2; i <= sqrt(number); i++)
	{
		if (number % i == 0)
		{
			return isPrime::en_NotPrime;
		}
	}
	return isPrime::en_Prime;
}

void printAllPrimesFrom1ToN(int number)
{
	cout << "\nAll Prime Numbers From 1 to " << number << " are:\n\n";
	for (int i = 1; i <= number; i++)
	{
		if (checkNumberForPrime(i) == isPrime::en_Prime)
			cout << i << "  ";
	}
}

int main()
{
	printAllPrimesFrom1ToN(readPositiveNumber("Enter a number to check from 1 to that number all prime numbers: "));

	return 0;
}