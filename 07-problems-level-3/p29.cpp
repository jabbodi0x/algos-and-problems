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

short countLowerCaseLetters(const string &s)
{
	short count = 0;

	for (char c : s)
	{
		if (c == tolower(c) && c != ' ')
			count++;
	}

	return count;
}

short countUpperCaseLetters(const string& s)
{
	short count = 0;

	for (char c : s)
	{
		if (c == toupper(c) && c!=' ')
			count++;
	}

	return count;
}


int main()
{
	string s = readString();

	cout << "\nLower case letters: " << countLowerCaseLetters(s);
	cout << "\nUpper case letters: " << countUpperCaseLetters(s);
}