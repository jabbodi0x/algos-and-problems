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

int myABS(int number)
{
	if (number > 0)
		return number;
	if (number <0)
		return number*-1;
	return 0;
}

int main()
{
	cout << "C++ abs Function:\n";
	cout << abs(10) << endl;
	cout << abs(0) << endl;
	cout << abs(-10) << endl;

	cout << "\n\nmyABS Function:\n";
	cout << myABS(10) << endl;
	cout << myABS(0) << endl;
	cout << myABS(-10) << endl;


 	return 0;
}