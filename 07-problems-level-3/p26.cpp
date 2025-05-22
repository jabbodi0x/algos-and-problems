#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

string readString(string prompt = "Enter String:\n")
{
	string s = "";
	do
	{
		cout << prompt;
		cin >> ws;
		getline(cin, s);
	} while (s == "");

	return s;
}

string stringToUpper(string s)
{
	for (char& c : s)
	{
		c = toupper(c);
	}

	return s;
}

string stringToLower(string s)
{
	for (char& c : s)
	{
		c = tolower(c);
	}

	return s;
}

int main()
{
	string s = "Hello World!";
	cout << stringToLower(s) << endl << stringToUpper(s) << endl;
}