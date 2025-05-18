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

float getFraction(float number)
{
	return number - (int)number;
}

int myRound(float number)
{
	if (number > 0)
	{
		if (getFraction(number) >= 0.5) return ++number;
	}
	if (number < 0)
	{
		if (abs(getFraction(number)) >= 0.5) return --number;
	}
	
	return number;
}

int main()
{
	cout << "C++ round Function:\n";
	cout << round(10.6) << endl;
	cout << round(10.4) << endl;
	cout << round(-10.9) << endl;
	cout << round(-10.4) << endl;

	cout << "\n\nmyRound Function:\n";
	cout << myRound(10.6) << endl;
	cout << myRound(10.4) << endl;
	cout << myRound(-10.9) << endl;
	cout << myRound(-10.4) << endl;


 	return 0;
}