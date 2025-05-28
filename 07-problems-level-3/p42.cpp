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

vector<string> splitString(string s, string delimiter = " ")
{
	vector<string> vWords;
	short pos = 0;

	string word = "";

	while ((pos = s.find(delimiter)) != string::npos)
	{
		word = s.substr(0, pos);

		if (word != "")
		{
			vWords.push_back(word);
		}
		s.erase(0, pos + delimiter.length());
	}
	if (s != "")
		vWords.push_back(s);

	return vWords;
}

string replaceWords(string s, string wordToReplace, string replaceWord)
{
	short pos = s.find(wordToReplace);

	while (pos != string::npos)
	{
		s = s.replace(pos, wordToReplace.length(), replaceWord);
		pos = s.find(wordToReplace);
	}

	return s;
}

int main()
{
	// ===========================================
	string s = "Hello! My name is Abdullah!";
	cout << replaceWords(s, "Abdullah", "Mohammad");
	cout << endl;
	// ===========================================
	cout << endl;
	system("pause>0");
}

