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

string changeFirstCharacterOfWordToUpper(string s)
{
	bool isFirstLetter = true;

	for (short i = 0; i < s.length(); i++)
	{
		if (s[i] != ' ' && isFirstLetter)
			s[i] = tolower(s[i]);

		isFirstLetter = (s[i] == ' ') ? true : false;
	}
	return s;
}


int main()
{
	cout << changeFirstCharacterOfWordToUpper(readString());
}