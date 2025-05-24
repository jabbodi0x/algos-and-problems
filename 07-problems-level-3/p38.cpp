#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

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

string trimStringLeft(string s)
{
	size_t length = s.length();
	for (size_t  i = 0; i < length; i++)
	{
		if (s[i] != ' ')
		{
			return s.substr(i);
		}
	}

	return "";
}

string trimStringRight(string s)
{
	size_t i = s.length();
	while (i > 0)
	{
		i--;
		if (s[i] != ' ')
		{
			return s.substr(0, i + 1);
		}
	}

	return "";
}

string trimString(string s)
{
	return trimStringRight(trimStringLeft(s));
}

int main()
{
	// ===========================================
	string s = "        Hello! My name is Abdullah           ";
	cout << setw(15) << left <<  "Trim Left" << ": [END]" << trimStringLeft(s) << "[END]" << endl;
	cout << setw(15) << left << "Trim Right" << ": [END]" << trimStringRight(s) << "[END]" << endl;
	cout << setw(15) << left << "Trim" << ": [END]" << trimString(s) << "[END]" << endl;

	// ===========================================
	cout << endl;
	system("pause>0");
}

