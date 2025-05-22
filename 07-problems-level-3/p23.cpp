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

void printEachLetterOfEachWord(string s)
{
	bool isFirstLetter = true;

	cout << "The first letter of each word in the string\n" << s << "\n\tare:\n";

	for (short i = 0; i < s.length(); i++)
	{
		if (s[i] != ' ' && isFirstLetter)
			cout << s[i] << " ";

		isFirstLetter = (s[i] == ' ') ? true : false;
	}

}


int main()
{
	printEachLetterOfEachWord(readString());
}