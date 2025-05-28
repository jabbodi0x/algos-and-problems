#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

const string FILE_NAME = "clients.txt";
const string SEPERATOR = "#//#";

struct stClient
{
    string accountNumber, name, phone, pinCode;
    float balance;
};

vector<string> splitString(string s, string delimiter = " ")
{
    vector<string> vWords;
    size_t start = 0;
    size_t end = s.find(delimiter);

    while (end != string::npos)
    {
        if (end > start)
        {
            vWords.push_back(s.substr(start, end - start));
        }
        start = end + delimiter.length();
        end = s.find(delimiter, start);
    }

    // Add the last word
    if (start < s.length())
    {
        vWords.push_back(s.substr(start));
    }

    return vWords;
}


stClient convertLineToStructure(const string& recordLine)
{
    stClient client;
    vector<string> vWords = splitString(recordLine, SEPERATOR);

    client.accountNumber = vWords[0];
    client.pinCode = vWords[1];
    client.name = vWords[2];
    client.phone = vWords[3];
    client.balance = stof(vWords[4]);

    return client;

}

void printClientRecord(const stClient& client)
{
    cout << "| " << setw(15) << left << client.accountNumber ;
    cout << "| " << setw(10) << left << client.pinCode;
    cout << "| " << setw(40) << left << client.name;
    cout << "| " << setw(12) << left << client.phone;
    cout << "| " << setw(12) << left << client.balance;
}

void printSingleClientRecord(const stClient& client)
{
    cout << "\n-----------[ Client Data ]-----------\n";
    cout << setw(15) << left << "Account Number" << ": " << client.accountNumber << endl;
    cout << setw(15) << left << "Pin Code" << ": " << client.pinCode << endl;
    cout << setw(15) << left << "Name" << ": " << client.name << endl;
    cout << setw(15) << left << "Phone" << ": " << client.phone << endl;
    cout << setw(15) << left << "Balance" << ": " << client.balance << endl;
    cout << "-------------------------------------\n";
}

void printAllClientsData(const vector<stClient>& vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (const stClient& client : vClients)
    {
        printClientRecord(client);
        cout << endl;
    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

vector<stClient> loadClientsDataFromFile()
{
    vector <stClient> vClients;
    fstream myFile;
    myFile.open(FILE_NAME, ios::in);

    if (myFile.is_open())
    {
        string line = "";
        stClient client;

        while (getline(myFile, line))
        {
            client = convertLineToStructure(line);
            vClients.push_back(client);
        }

        myFile.close();
    }

    return vClients;
}

bool doesClientExists(const vector<stClient> vClients, string accountNumber, stClient& client)
{
    for (const stClient& tempClient : vClients)
    {
        if (tempClient.accountNumber == accountNumber)
        {
            client = tempClient;
            return true;
        }
    }
    return false;
}

void findClientByAccountNumber(const vector<stClient> &vClients)
{
    string accountNumber = "";
    stClient foundClient;

    cout << "\nEnter Account Number to Find: ";
    getline(cin, accountNumber);
    
    if (doesClientExists(vClients, accountNumber, foundClient))
    {
        cout << "\nAccount with account number: " << accountNumber << " has been found!:\n";
        printSingleClientRecord(foundClient);
    }
    else
    {
        cout << "\nAccount with account number: " << accountNumber << " has NOT been found!\n";

    }

}

int main()
{
    vector<stClient> vClients = loadClientsDataFromFile();

    findClientByAccountNumber(vClients);
    

    cout << endl;
    system("pause>0");

    return 0;
}