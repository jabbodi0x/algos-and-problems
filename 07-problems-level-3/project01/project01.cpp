#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

const string FILE_NAME = "clients.txt";
const string SEPARATOR = "#//#";

struct stClient
{
    string accountNumber, name, phone, pinCode;
    float balance;
    bool markedForDeletion = false;
};

enum enBankMenu
{
    enShowAllClients = 1,
    enAddNewClient = 2,
    enDeleteClient = 3,
    enUpdateClient = 4,
    enFindClient = 5,
    enExit = 6
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
    vector<string> vWords = splitString(recordLine, SEPARATOR);

    client.accountNumber = vWords[0];
    client.pinCode = vWords[1];
    client.name = vWords[2];
    client.phone = vWords[3];
    client.balance = stof(vWords[4]);

    return client;

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
    cout << "| " << setw(15) << left << client.accountNumber;
    cout << "| " << setw(10) << left << client.pinCode;
    cout << "| " << setw(40) << left << client.name;
    cout << "| " << setw(12) << left << client.phone;
    cout << "| " << setw(12) << left << client.balance;
}

void printAllClientsData(const vector<stClient>& vClients)
{
    system("cls");

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

short findClientIndexByAccount(const vector<stClient>& vClients, const string& accountNumber)
{
    for (short i = 0; i < vClients.size(); ++i)
    {
        if (vClients[i].accountNumber == accountNumber)
            return i;
    }
    return -1; // not found
}

stClient readClientData(const vector<stClient>& vClients)
{
    string accountNumber = "";
    stClient client;

    while (true)
    {
        cout << "Enter Account Number:\n";
        cin >> accountNumber;
        if (findClientIndexByAccount(vClients, accountNumber) == -1)
        {
            client.accountNumber = accountNumber;
            break;
        }
        else
            cout << "\nAccount with account numbmer " << accountNumber << " already exists\n";
    }
    cout << endl;

    client.pinCode = readString("Enter Pin Code:\n");
    cout << endl;

    client.name = readString("Enter name:\n");
    cout << endl;

    client.phone = readString("Enter Phone Number:\n");
    cout << endl;

    cout << "Enter Account Balance:\n";
    cin >> client.balance;

    return client;

}

string convertClientRecordToData(const stClient& client)
{
    string recordLine = "";

    recordLine += client.accountNumber + SEPARATOR;
    recordLine += client.pinCode + SEPARATOR;
    recordLine += client.name + SEPARATOR;
    recordLine += client.phone + SEPARATOR;
    recordLine += to_string(client.balance);

    return recordLine;

}

void addRecordLineToFile(const string& recordLine)
{
    fstream myFile;
    myFile.open(FILE_NAME, ios::out | ios::app);

    if (myFile.is_open())
    {
        myFile << recordLine << endl;
    }
    myFile.close();
}

void addNewClient(vector<stClient>& vClients)
{
    system("cls");
    cout << "===============================================\n";
    cout << "\t\tAdd Client Screen\n";
    cout << "===============================================\n";


    stClient client = readClientData(vClients);
    vClients.push_back(client);
    addRecordLineToFile(convertClientRecordToData(client));

    cout << "\n\nClient was Added Successfully!";
}

void markClientForDeletion(stClient& client)
{
    client.markedForDeletion = true;
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

bool confirmClientDeletion()
{
    char answer;
    cout << "\nDo you want to remove this client [y/n]: ";
    cin >> answer;
    return tolower(answer) == 'y';
}

void deleteClient(vector<stClient>& vClients)
{
    system("cls");
    cout << "===============================================\n";
    cout << "\t\tDelete Client Screen\n";
    cout << "===============================================\n";

    string accountNumber = readString("\nEnter Account Number to delete:\n");
    short index = findClientIndexByAccount(vClients, accountNumber);

    if (index != -1)
    {
        printSingleClientRecord(vClients[index]);

        if (confirmClientDeletion())
        {
            markClientForDeletion(vClients[index]);
            saveClientsToFile(vClients);

            cout << "\nAccount was deleted successfully!\n";
        }
        else
        {
            cout << "\nDeletion canceled.\n";
        }
    }
    else
    {
        cout << "\nAccount with account number: " << accountNumber << " has NOT been found!\n";
    }
}

void updateClientData(stClient& client)
{
    client.pinCode = readString("Enter Pin Code:\n");
    cout << endl;

    client.name = readString("Enter name:\n");
    cout << endl;

    client.phone = readString("Enter Phone Number:\n");
    cout << endl;

    cout << "Enter Account Balance:\n";
    cin >> client.balance;
}

void updateClient(vector<stClient>& vClients)
{
    system("cls");
    cout << "===============================================\n";
    cout << "\t\tUpdate Client Screen\n";
    cout << "===============================================\n";

    string accountNumber = readString("\nEnter Account Number to Update:\n");
    short index = findClientIndexByAccount(vClients, accountNumber);

    if (index != -1)
    {
        printSingleClientRecord(vClients[index]);
        cout << endl;
        updateClientData(vClients[index]);

        cout << "\nClient was updated successfully!\n";
        saveClientsToFile(vClients);
        cout << "\nUpdated Client Data:\n";

        printSingleClientRecord(vClients[index]);
    }
    else
    {
        cout << "\nAccount with account number: " << accountNumber << " has NOT been found!\n";
    }
}

void findClient(const vector<stClient>& vClients)
{
    system("cls");
    cout << "===============================================\n";
    cout << "\t\tFind Client Screen\n";
    cout << "===============================================\n";

    string accountNumber = readString("\nEnter Account Number to Find:\n");
    short index = findClientIndexByAccount(vClients, accountNumber);

    if (index != -1)
    {
        cout << "\nAccount with account number: " << accountNumber << " has been found!\n";
        printSingleClientRecord(vClients[index]);
    }
    else
    {
        cout << "\nAccount with account number: " << accountNumber << " has NOT been found!\n";
    }
}

void showMainMenue()
{
    system("cls");
    cout << "===============================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===============================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";
    cout << "===============================================\n";
}

short readOption()
{
    short choice = 0;
    do
    {
        cout << "\nWhat do you want to do? [1-6]: ";
        cin >> choice;
    } while (choice < 0 || choice > 6);

    return choice;
}

void goBackToMainMenu()
{
    cout << "\n\n\nPress any key to go back to Main Menu...";
    system("pause>0");
}

void bank()
{
    vector<stClient> vClients = loadClientsDataFromFile();

    short choice = 0;
    do
    {
        showMainMenue();
        choice = readOption();

        switch (choice)
        {
        case enBankMenu::enShowAllClients:
            printAllClientsData(vClients);
            break;
        case enBankMenu::enAddNewClient:
            addNewClient(vClients);
            break;
        case enBankMenu::enDeleteClient:
            deleteClient(vClients);
            break;
        case enBankMenu::enUpdateClient:
            updateClient(vClients);
            break;
        case enBankMenu::enFindClient:
            findClient(vClients);
            break;
        }
        if (choice != enBankMenu::enExit)
            goBackToMainMenu();


    } while ((enBankMenu)choice != enBankMenu::enExit);
}

int main()
{
    bank();


    cout << endl;
    system("pause>0");

    return 0;
}