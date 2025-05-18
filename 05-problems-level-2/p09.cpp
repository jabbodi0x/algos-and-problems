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
	cout << "Number:\t" << number << endl;

	for (int i = 1;i <= 9; i++)
	{
		int freq = getFreqOfNumber(number, i);

		if (freq != 0)
		{
			cout << "\nDigit " << i << " frequency is " << getFreqOfNumber(number, i);
		}
	}

	cout << endl;
 	return 0;
}