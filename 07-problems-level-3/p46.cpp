#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct stClient
{
    string accountNumber, name, phone, pinCode;
    float balance;
};

int readPositiveNumber(string message = "Enter a positive number: ")
{
    int number;

    do
    {
        cout << message;
        cin >> number;
    } while (number < 0);

    return number;
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

stClient readClientData()
{
    stClient client;

    client.accountNumber = readString("Enter Account Number:\n");
    cout << endl;

    client.pinCode = readString("Enter Pin Code:\n");
    cout << endl;

    client.name = readString("Enter name:\n");
    cout << endl;

    client.phone = readString("Enter Phone Number:\n");
    cout << endl;

    cout << "Enter Account Balance:\n";
    float balance = 0;
    cin >> balance;
    client.balance = balance;

    return client;
    
}

string convertClientRecordToData(const stClient& client, string seperator= "#//#")
{
    string recordLine = "";

    recordLine += client.accountNumber + seperator;
    recordLine += client.pinCode + seperator;
    recordLine += client.name + seperator;
    recordLine += client.phone + seperator;
    recordLine += to_string(client.balance);

    return recordLine;

}

stClient convertLineToStructure(const string& recordLine, string seperator = "#//#")
{
    stClient client;
    vector<string> vWords = splitString(recordLine, seperator);

    client.accountNumber = vWords[0];
    client.pinCode = vWords[1];
    client.name = vWords[2];
    client.phone = vWords[3];
    client.balance = stof(vWords[4]);

    return client;
    
}

void printClientReord(const stClient& client)
{
    cout << "\n-----------[ Client Data ]-----------\n";
    cout << setw(15) << left << "Account Number" << ": " << client.accountNumber << endl;
    cout << setw(15) << left << "Pin Code" << ": " << client.pinCode << endl;
    cout << setw(15) << left << "Name" << ": " << client.name << endl;
    cout << setw(15) << left << "Phone" << ": " << client.phone << endl;
    cout << setw(15) << left << "Balance" << ": " << client.balance << endl;
    cout << "-------------------------------------\n";
}

int main()
{
    stClient client = readClientData();
    string recordLine = convertClientRecordToData(client);

    cout << endl;

    cout << "\nRecord Line:\n" << recordLine;
    cout << endl;

    printClientReord(convertLineToStructure(recordLine));


    cout << endl;
    system("pause>0");

    return 0;
}