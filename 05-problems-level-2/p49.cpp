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

int myCeil(float number)
{
	if (number > 0)
		return ++number;
	else
		return number;
}

int main()
{
	cout << "C++ round Function:\n";
	cout << ceil(10.6) << endl;
	cout << ceil(10.4) << endl;
	cout << ceil(-10.9) << endl;
	cout << ceil(-10.4) << endl;


	cout << "\n\nmyRound Function:\n";
	cout << myCeil(10.6) << endl;
	cout << myCeil(10.4) << endl;
	cout << myCeil(-10.9) << endl;
	cout << myCeil(-10.4) << endl;


 	return 0;
}