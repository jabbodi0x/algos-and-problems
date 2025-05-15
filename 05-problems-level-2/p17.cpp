#include <iostream>
using namespace std;

//int readPositiveNumber(string message = "Enter a positive number: ")
//{
//	int number;
//
//	do
//	{
//		cout << message;
//		cin >> number;
//	} while (number < 0);
//
//	return number;
//}

string readString(string message = "Enter a string: ")
{
	string myString = "";
	cout << message;
	cin >> myString;

	return myString;
}

int getTrialsCount(string password)
{
	int trials = 1;
	string guessedPassword = "";
	for (int i = 65; i <= 90; i++)
	{
		for (int j = 65; j <= 90; j++)
		{
			for (int k = 65; k <= 90; k++)
			{
				guessedPassword = string(1, char(i)) + char(j) + char(k);

				if (guessedPassword == password)
					return trials;
				trials++;
			}
		}
	}
	return 0;
}

void guessPassword()
{
	string password = readString("Enter three letter capital password to guess: ");
	unsigned short trials = getTrialsCount(password);

	cout << "\nPassword is: " << password;

	if (trials > 0)
	{
		cout << "\nFound after " << trials << " Trial(s)!\n";
	}
	else
		cout << "\nSomehow, we didn't guess your password!\n";
}

int main()
{
	guessPassword();
}