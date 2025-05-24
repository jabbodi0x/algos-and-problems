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

short getCountOfCharInString(string& s, char charToCount,bool matchCase=true)
{
	short count = 0;

	if (matchCase)
	{
		for (char c : s)
		{
			if (c == charToCount)
				count++;
		}
	}

	else if (!matchCase)
	{
		for (char c : s)
		{
			if (tolower(c)==tolower(charToCount))
				count++;
		}
	}

	return count;

}

int main()
{
	string s = readString();
	char c = readChar("Enter char to count in the string: ");

	printf("\nLetter \'%c\' Count =  %d\n", c, getCountOfCharInString(s, c,1));
	printf("\nLetter \'%c\' Count (ignore-case) =  %d\n", c, getCountOfCharInString(s, c,0));
}