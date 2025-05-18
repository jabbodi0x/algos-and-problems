#include <iostream>

using namespace std;

int readPositiveNumber(string message = "Enter a Positive number: ")
{
	int number;

	do
	{
		cout << message;
		cin >> number;
	} while (number < 0);

	return number;
}

float mySqrt(float Number)
{
	return pow(Number, 0.5);
}

int main()
{
	

 	return 0;
}