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

int myFloor(float number)
{
	if (number > 0)
		return number;
	else
		return --number;
	
	return number;
}

int main()
{
	cout << "C++ round Function:\n";
	cout << floor(10.6) << endl;
	cout << floor(10.4) << endl;
	cout << floor(-10.9) << endl;
	cout << floor(-10.4) << endl;

	cout << "\n\nmyRound Function:\n";
	cout << myFloor(10.6) << endl;
	cout << myFloor(10.4) << endl;
	cout << myFloor(-10.9) << endl;
	cout << myFloor(-10.4) << endl;


 	return 0;
}