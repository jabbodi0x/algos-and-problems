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

int getFreqOfNumber(int number,int digit)
{
	int remainder = 0;
	int freq = 0;
	while (number > 0)
	{
		remainder = number % 10;
		number /= 10;
		if (remainder == digit)
			freq++;
	}

	return freq;
}

int main()
{
	int number = readPositiveNumber();
	int digit = readPositiveNumber("Enter a number to check its frequency: ");
	cout << "\nThe frequency of " << digit << " in the number " << number << " is " << getFreqOfNumber(number, digit) << "\n";
 	return 0;
}