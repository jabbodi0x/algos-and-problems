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

char inverCharCase(char c)
{
	return (c == toupper(c)) ? tolower(c) : toupper(c);
}


int main()
{
	cout << inverCharCase(readChar()) << endl;
}