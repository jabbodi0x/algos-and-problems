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

bool isVowel(char c)
{
	c = tolower(c);

	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

short getCountOfVowelsInString(string s)
{
	short count = 0;

	for (char c : s)
	{
		if (isVowel(c))
			count++;
	}

	return count;
}

int main()
{
	string s = readString();
	cout << "Count of Vowels is: " << getCountOfVowelsInString(s) << endl;
}