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

string joinWords(const vector<string>& vWords, const string& delimiter = " ") {
	if (vWords.empty()) return "";

	string s = vWords[0];

	for (size_t i = 1; i < vWords.size(); ++i) {
		s += delimiter + vWords[i];
	}

	return s;
}

string stringToLower(string s)
{

	string sWord = "";

	for (size_t i = 0; i < s.length(); i++)
	{
		sWord += tolower(s[i]);
	}

	return sWord;
}

string customReplaceWords(string s, string wordToReplace, string replaceWord, bool matchCase=true)
{
	vector <string> vWords = splitString(s);

	if (matchCase)
	{
		for (string& sWord : vWords)
		{
			if (sWord == wordToReplace)
			{
				sWord = replaceWord;
			}
		}
	}

	if (!matchCase)
	{
		for (string& sWord : vWords)
		{
			if (stringToLower(sWord) == stringToLower(wordToReplace))
			{
				sWord = replaceWord;
			}
		}
	}


	return joinWords(vWords);
}

int main()
{
	// ===========================================
	string s = "Hello! My name is Abdullah";
	cout << customReplaceWords(s, "abDullah", "Mohammad",1);

	// ===========================================
	cout << endl;
	system("pause>0");
}

