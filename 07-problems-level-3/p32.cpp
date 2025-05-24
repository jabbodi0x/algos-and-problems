#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

char readChar(string prompt = "Enter Char:\n")
{
	cout << prompt;
	char c;

	cin >> c;

	return c;
}

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



int main()
{
	char c = readChar();
	
	if (isVowel(c))
	{
		cout << "is vowel";
	}
	else 
		cout << "not a vowel";
	
}