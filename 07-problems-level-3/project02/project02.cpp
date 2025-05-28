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
    enTransactions = 6,
    enExit = 7
};

enum enTransactionMenu
{
    enDeposit = 1,
    enWithdraw = 2,
    enTotalBalance=3,
    enMainMenu=4
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

void printScreenHeader(const string& title) {
    system("cls");
    cout << "===============================================\n"
        << "\t\t" << title << " Screen\n"
        << "===============================================\n";
}

short findClientIndexByAccount(const vector<stClient>& vClients, const string& accountNumber)
{
    for (short i = 0; i < vClients.size(); ++i)
    {
        if (vClients[i].accountNumber == accountNumber && !vClients[i].markedForDeletion)
            return i;
    }
    return -1; // not found
}

short getValidClientIndex(const vector<stClient>& vClients) {
    string accountNumber;
    short idx;

    do {
        accountNumber = readString("\nEnter Account Number:\n");
        idx = findClientIndexByAccount(vClients, accountNumber);
        if (idx == -1)
            cout << "Client with account number "<< accountNumber << " was NOT found, Try again.\n";
    } while (idx == -1);

    return idx;
}

stClient readClientData(const vector<stClient>& vClients)
{
    string accountNumber = "";
    stClient client;

    while (true)
    {
        cout << "\nEnter Account Number:\n";
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

void addNewClient(vector<stClient>& vClients)
{
    printScreenHeader("Add Client");


    stClient client = readClientData(vClients);
    vClients.push_back(client);
    cout << "\nClient was Added Successfully!\n";
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

bool confirmClientUpdate()
{
    char answer;
    cout << "\nDo you want to update this client [y/n]: ";
    cin >> answer;
    return tolower(answer) == 'y';
}

void deleteClient(vector<stClient>& vClients)
{
    printScreenHeader("Delete Client");

    short index = getValidClientIndex(vClients);
    string accountNumber = vClients[index].accountNumber;

    printSingleClientRecord(vClients[index]);

    if (confirmClientDeletion())
    {
        markClientForDeletion(vClients[index]);

        cout << "\nClient was deleted successfully!\n";
    }
    else
    {
        cout << "\nDeletion canceled.\n";
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
    printScreenHeader("Update Client");

    
    short index = getValidClientIndex(vClients);
    string accountNumber = vClients[index].accountNumber;

    printSingleClientRecord(vClients[index]);
    cout << endl;

    if (confirmClientUpdate())
    {
        updateClientData(vClients[index]);

        cout << "\nClient was updated successfully!\n";
        cout << "\nUpdated Client Data:\n";
        printSingleClientRecord(vClients[index]);
    }
    else
    {
        cout << "\nUpdate canceled.\n";
    }
    
}

void findClient(const vector<stClient>& vClients)
{
    printScreenHeader("Find Client");

    short index = getValidClientIndex(vClients);
    string accountNumber = vClients[index].accountNumber;

    printSingleClientRecord(vClients[index]);
}

bool confirmTransaction()
{
    cout << "\nDo you want to perfom this transaction? [y/n] : ";
    char answer;

    cin >> answer;

    if (tolower(answer) == 'y')
    {
        return true;
    }

    return false;
}

void depositToClient(stClient& client, float amount)
{
    client.balance += amount;
}

void goBackToMainMenu(string msg = "\n\n\nPress any key to go back to Main Menu...")
{
    cout << msg;
    system("pause>0");
}

float getPositiveAmount(const string& prompt) {
    float amt;
    do {
        cout << prompt;
        cin >> amt;
    } while (amt <= 0);
    return amt;
}

bool isPositive(float amt)
{
    return amt>0;
}

bool isAmountLesserThanBalance(stClient& client, float amount)
{
    return client.balance >= amount;
}

float getProperWithdrawAmount(stClient& client)
{
    float amt;
    do
    {
        cout << "\nEnter amount to withdraw:\n";
        cin >> amt;
        if (!isAmountLesserThanBalance(client,amt))
            cout << "\nBalance is less than the withdraw amount!\n";
        if (!isPositive(amt))
            cout << "\nWithdraw amount must be greater than 0\n";

    } while (!isPositive(amt) || !isAmountLesserThanBalance(client,amt));

    return amt;
}

void depositMenu(vector<stClient>& vClients)
{
    printScreenHeader("Deposit");

    short index = getValidClientIndex(vClients);
    string accountNumber = vClients[index].accountNumber;

    float amount = getPositiveAmount("\nEnter Amount to Deposit:\n");

    if (confirmTransaction())
    {
        depositToClient(vClients[index], amount);
        cout << "An amount of " << amount << " was successfully deposited to the account number: " << accountNumber;
    }
    else
        cout << "\nTransaction canceled\n";
    
}

void withdrawFromClient(stClient& client, float amount)
{
    client.balance -= amount;
}

void withdrawMenu(vector<stClient>& vClients)
{
    printScreenHeader("Withdraw");

    short index = getValidClientIndex(vClients);
    string accountNumber = vClients[index].accountNumber;

    float amount = getProperWithdrawAmount(vClients[index]);

    if (confirmTransaction())
    {
        withdrawFromClient(vClients[index], amount);

        cout << "An amount of " << amount << " was successfully withdrawn from the account number: " << accountNumber;
    }
    else
        cout << "\nTransaction canceled\n";
}

void totalBalanceMenu(vector<stClient>& vClients)
{
    printScreenHeader("Total Balance");

    short index = getValidClientIndex(vClients);
    string accountNumber = vClients[index].accountNumber;

    cout << "\nThe Client with account number " << accountNumber << " has a total balance of " << vClients[index].balance << "\n";
}

short readOption(short from, short to)
{
    short choice = 0;
    do
    {
        cout << "\nChoose what do you want to do? [" << from << "-" << to << "]: ";
        cin >> choice;
    } while (choice < from - 1 || choice > to + 1);

    return choice;
}

void transactionMenu()
{
    system("cls");
    cout << "===============================================\n";
    cout << "\t\tTransactions Menu Screen\n";
    cout << "===============================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances\n";
    cout << "\t[4] Main Menu\n";
    cout << "===============================================\n";
}

void transactions(vector<stClient>& vClients)
{
   
    short option = 0;

    do
    {
        transactionMenu();
        option = readOption(1, 4);

        switch (option)
        {
        case enTransactionMenu::enDeposit:
            depositMenu(vClients);
            break;
        case enTransactionMenu::enWithdraw:
            withdrawMenu(vClients);
            break;
        case enTransactionMenu::enTotalBalance:
            totalBalanceMenu(vClients);
            break;
        }
        if (option != enTransactionMenu::enMainMenu)
        {
            goBackToMainMenu("\n\n\nPress any key to go back to Transactions Menu...");
        }
    } while ((enTransactionMenu)option != enTransactionMenu::enMainMenu);
}

void printMainMenu()
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
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "===============================================\n";
    cout << "Changes will NOT be saved unless you exit properly!\n";
}

void bank()
{
    vector<stClient> vClients = loadClientsDataFromFile();

    short choice = 0;
    do
    {
        printMainMenu();
        choice = readOption(1, 7);

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
        case enBankMenu::enTransactions:
            transactions(vClients);
        case enBankMenu::enExit:
            break;
        }
        if (choice != enBankMenu::enExit && choice != enBankMenu::enTransactions)
            goBackToMainMenu();


    } while ((enBankMenu)choice != enBankMenu::enExit);

    saveClientsToFile(vClients);
}

int main()
{
    bank();


    cout << endl;
    

    return 0;
}