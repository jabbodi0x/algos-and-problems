#include <iostream>
#include <string>
#include <cctype> // For ispunct
using namespace std;

string readString(string prompt = "Enter String:\n")
{
    string s = "";
    do
    {
        cout << prompt;
        cin >> ws; // Clear leading whitespace
        getline(cin, s);
    } while (s == "");

    return s;
}

string removePunctuation(string s)
{
    string s2="";

    for (size_t i =0;i<s.length();i++)
    {
        if (!ispunct(s[i]))
        {
           s2 += s[i];
        }
    }
    
    return s2;
}

int main()
{
    string s = "";
    s = readString("Enter a string to remove punctuation:\n");
    cout << "Original string: " << s << endl;

    s = removePunctuation(s);
    
    cout << "String without punctuation: " << s << endl;

    return 0;
}