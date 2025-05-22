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

char readChar(string prompt = "Enter Char:\n")
{
	cout << prompt;
	char c;

	cin >> c;

	return c;
}

char invertCharCase(char c)
{
	return (c == toupper(c)) ? tolower(c) : toupper(c);
}

string inverAllCharCaseInString(string s)
{
	for (char& c : s)
	{
		c = invertCharCase(c);
	}

	return s;
}


int main()
{
	string s = readString();
	cout << endl;

	cout << inverAllCharCaseInString(s);
	cout << endl;

}