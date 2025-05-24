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

string joinWords(string arrWords[100], size_t arrayLength, const string& delimiter = " ") {
	if (arrayLength==0) return "";

	string s = arrWords[0];

	for (size_t i = 1; i < arrayLength; ++i) {
		s += delimiter + arrWords[i];
	}

	return s;
}

int main()
{
	// ===========================================
	string s = "Hello! My name is Abdullah!";
	vector<string> vWords = splitString(s);
	string arrWords[100] = { "Hello","My","Name","is","Abdullah!" };

	cout << joinWords(vWords);
	cout << endl;
	cout << joinWords(arrWords, 5);
	// ===========================================
	cout << endl;
	system("pause>0");
}

