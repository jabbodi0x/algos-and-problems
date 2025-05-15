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

int reverseNumber(int number)
{
	int remainder = 0, reversed = 0;

	while (number > 0)
	{
		remainder = number % 10;
		number /= 10;
		reversed = reversed * 10 + remainder;
	}

	return reversed;

}

bool isPalindrome(int number)
{
	return number == reverseNumber(number);
}


int main()
{
	cout << (isPalindrome(1331)? "is palindrome" : "is not a palindrome" );

}