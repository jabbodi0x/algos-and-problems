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

string reverseWords(const vector<string>& vWords, string delimiter=" ")
{
	size_t i = vWords.size(); 
	string s = vWords[--i];
	
	while (i > 0)
	{
		s += delimiter + vWords[--i];
	}

	return s;
}

// Koko's Method:
string reverseWords(string sWords, string delimiter = " ")
{
	vector<string> vWords = splitString(sWords, delimiter);

	string s = vWords[vWords.size()-1];

	vector<string>::iterator iter = vWords.end()-1;

	while (iter != vWords.begin())
	{
		--iter;

		s += delimiter + *iter;
	}

	return s;
}

int main()
{
	// ===========================================
	string s = "Hello! My name is Abdullah!";
	cout << reverseWords(s);

	cout << endl;
	// ===========================================
	cout << endl;
	system("pause>0");
}

