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

void printAllWordsInString(string s)
{
	short pos = 0;
	string word = "";
	string delimiter = " ";
	while ((pos = s.find(delimiter)) != string::npos)
	{
		word = s.substr(0, pos);

		if (word != "")
		{
			cout << word << endl;
		}
		s.erase(0, pos + delimiter.length());
	}
	if (s != "")
		cout << s << endl;

}

int main()
{
	string s = "Hello! My name is Abdullah";
	cout << "\nYour String Words are:\n";
	printAllWordsInString(s);

}