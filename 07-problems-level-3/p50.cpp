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
    bool markedForDeletion = false;
};

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

void printClientRecord(const stClient& client)
{
    cout << "| " << setw(15) << left << client.accountNumber ;
    cout << "| " << setw(10) << left << client.pinCode;
    cout << "| " << setw(40) << left << client.name;
    cout << "| " << setw(12) << left << client.phone;
    cout << "| " << setw(12) << left << client.balance;
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

bool getClientExists(const vector<stClient> &vClients, string &accountNumber, short &index)
{
    for (const stClient& client : vClients)
    {
        if (client.accountNumber == accountNumber)
        {
            return true;
        }
        index++;
    }
    return false;
}

void markClientForDeletion(stClient &client)
{
    client.markedForDeletion = true;
}

void addRecordLineToFile(string recordLine)
{
    fstream myFile;
    myFile.open(FILE_NAME, ios::out | ios::app);

    if (myFile.is_open())
    {
        myFile << recordLine << endl;
    }
    myFile.close();
}

string convertClientRecordToData(const stClient& client)
{
    string recordLine = "";

    recordLine += client.accountNumber + SEPERATOR;
    recordLine += client.pinCode + SEPERATOR;
    recordLine += client.name + SEPERATOR;
    recordLine += client.phone + SEPERATOR;
    recordLine += to_string(client.balance);

    return recordLine;

}


void saveClientsToFile(vector<stClient>& vClients)
{
    fstream myFile;
    myFile.open(FILE_NAME, ios::out);
    if (myFile.is_open())
    {
        for (const stClient& client : vClients)
        {
            if (!client.markedForDeletion)
            {
                myFile << convertClientRecordToData(client) << endl;
            }
        }
    }
    myFile.close();
}

void deleteClient(vector<stClient> &vClients)
{
    string accountNumber = readString("Enter Account Number:\n");
    short index = 0;
    
    if (getClientExists(vClients, accountNumber, index))
    {
        printSingleClientRecord(vClients[index]);
        
        char answer;
        cout << "Do you want to remove this client [y/n]: ";
        cin >> answer;

        if (tolower(answer) == 'y')
        {
            markClientForDeletion(vClients[index]);
            saveClientsToFile(vClients);

            cout << "\n\nAccount was deleted successfully!\n";
        }
    }
    else
    {
        cout << "\nAccount with account number: " << accountNumber << " has NOT been found!\n";
    }
}

int main()
{
    vector<stClient> vClients = loadClientsDataFromFile();

    deleteClient(vClients);

    cout << endl;
    system("pause>0");

    return 0;
}