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

int countAllWordsInString(string s,string delimiter = " ")
{
	short pos = 0, count = 0;
	string word = "";
	

	while ((pos = s.find(delimiter)) != string::npos)
	{
		word = s.substr(0, pos);

		if (word != "")
		{
			count++;
		}
		s.erase(0, pos + delimiter.length());
	}
	if (s != "")
		count++;

	return count;
}

int main()
{
	string s = "Hello! My name is Abdullah";
	cout << "The String:\n" << s << endl;

	cout << "Words Count: " << countAllWordsInString(s);
	cout << endl << endl;
}

