#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <windows.h>

using namespace std;


const string CLIENTS_FILE_NAME = "clients.txt";
const string SEPARATOR = "#//#";

struct stClient
{
    string accountNumber;
    string pinCode;
    string fullName;
    string phoneNumber;
    float balance = 0.0f;
    bool markedForDeletion = false;

};

enum enMainMenu
{
    enQuickWithdraw=1,
    enNormalWithdraw,
    enDeposit,
    enCheckBalance,
    enLogout
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

string readString(const string& prompt = "Enter String:\n")
{
    string s;
    do
    {
        cout << prompt;
        getline(cin >> ws, s);
    } while (s.empty());
    return s;
}

vector<string> splitString(const string& s, const string delimiter = SEPARATOR)
{
    vector<string> tokens;

    size_t start = 0, end = s.find(delimiter);

    while (end != string::npos)
    {
        if (end > start)
        {
            tokens.push_back(s.substr(start, end - start));
        }
        start = end + delimiter.length();
        end = s.find(delimiter,start);
    }
    if (start < s.length())
        tokens.push_back(s.substr(start));

    return tokens;
}


string stringToLower(string s)
{
    for (char& c : s) c = tolower(c);
    return s;
}

string convertClientStructureToRecordLine(const stClient& client)
{
    return client.accountNumber + SEPARATOR + client.pinCode + SEPARATOR + client.fullName + SEPARATOR + client.phoneNumber + SEPARATOR + to_string(client.balance);
}

stClient convertClientRecordLineToStructure(const string& recordLine)
{
    stClient client;

    vector<string> vWords = splitString(recordLine);

    client.accountNumber = vWords[0];
    client.pinCode = vWords[1];
    client.fullName = vWords[2];
    client.phoneNumber = vWords[3];
    client.balance = stof(vWords[4]);

    return client;
}

vector<stClient> loadClientsFromFile()
{
    vector<stClient> vClients;

    fstream myFile(CLIENTS_FILE_NAME, ios::in);

    if (myFile.is_open())
    {
        string line = "";
        while (getline(myFile, line))
        {
            vClients.push_back(convertClientRecordLineToStructure(line));
        }
        myFile.close();
    }

    return vClients;
}

void saveClientsToFile(const vector<stClient>& vClients)
{
    fstream myFile(CLIENTS_FILE_NAME, ios::out);

    if (myFile.is_open())
    {
        for (const stClient& client: vClients)
        {
            if (!client.markedForDeletion)
                myFile << convertClientStructureToRecordLine(client) << endl;
        }
        myFile.close();
    }
    else
    {
        cout << "\nError: Unable to open " << CLIENTS_FILE_NAME << " for writing.\n";
    }
}

void printScreenHeader(const string& title)
{
    const int totalWidth = 50;
    string    fullTitle = title + " Screen";

    system("cls");
    int leftPadding = (totalWidth - static_cast<int>(fullTitle.length())) / 2;
    if (leftPadding < 0) leftPadding = 0;

    cout << string(totalWidth, '=') << "\n";
    cout << string(leftPadding, ' ') << fullTitle << "\n";
    cout << string(totalWidth, '=') << "\n";
}

int readOption(int from, int to)
{
    int choice = 0;
    do
    {
        cout << "\nChoose an option [" << from << "-" << to << "]: ";
        cin >> choice;
    } while (choice < from || choice > to);
    return choice;
}

bool confirmAction(const string& prompt)
{
    char answer;
    cout << "\n\n" << prompt << " [y/n]: ";
    cin >> answer;
    return tolower(answer) == 'y';
}

void goBackToMenu(const string& msg = "continue")
{
    cout << "\n\n\nPress any key to " << msg << "...";
    system("pause>0");
}

string formatMoney(float amount)
{
    // Round to 2 decimal places
    amount = round(amount * 100) / 100;

    int intPart = (int)amount;
    int fracPart = (int)((amount - intPart) * 100);

    // Convert integer part to string with commas
    string intStr = to_string(intPart);
    string formattedInt = "";

    int counter = 0;
    for (int i = intStr.length() - 1; i >= 0; --i)
    {
        formattedInt = intStr[i] + formattedInt;
        counter++;
        if (counter % 3 == 0 && i != 0)
        {
            formattedInt = "," + formattedInt;
        }
    }

    // Format decimal part
    string fracStr = (fracPart < 10) ? "0" + to_string(fracPart) : to_string(fracPart);

    return formattedInt + "." + fracStr;
}

void displayCurrentBalance(float amount)
{
    cout << "\nYour current account balance is " << formatMoney(amount) << "\n";
}
void printQuickWithdrawMenu()
{
    printScreenHeader("Quick Withdraw");
    cout << setw(10) << left << " [1] 50" << "\t[2] 100\n";
    cout << setw(10) << left << " [3] 200" << "\t[4] 500\n";
    cout << setw(10) << left << " [5] 1,000" << "\t[6] 2,000\n";
    cout << setw(10) << left << " [7] 5,000" << "\t[8] 10,000\n";
    cout << "\n [9] Main Menu\n";
    cout << string(50, '=') << "\n";
}

bool isValidWithdraw(stClient& client, int amount, string& errorMsg, bool quickDraw = true)
{
    if (amount <= 0)
    {
        errorMsg = "\nERROR! Amount must be positive. Try again.\n";
        return false;
    }

    else if (amount > client.balance)
    {
        errorMsg = "\nERROR! Not enough balance to withdraw. Try again.\n";
        return false;
    }
    else if (!quickDraw && amount % 5 != 0)
    {
        errorMsg = "\nERROR! Amount must be multiple of 5. Try again.\n";
        return false;
    }
    return true;
}

void quickWithdrawMenu(stClient& client)
{
    
    do
    {
        int amounts[] = { 0,50, 100, 200, 500, 1000, 2000, 5000, 10000 };
        int option;
        string errorMsg = "";
        

        do
        {
            printQuickWithdrawMenu();
            displayCurrentBalance(client.balance);
            cout << errorMsg;

            option = readOption(1, 9);

            if (option == 9)
                break;

        } while (!isValidWithdraw(client, amounts[option], errorMsg, true) && option != 9);

        if (option != 9 && confirmAction("Do you want to withdraw " + formatMoney(amounts[option]) + " from your account?"))
        {
            client.balance -= amounts[option];
            cout << "\nAn amount of " << amounts[option] << " was successfully withdrawn.\n";
            displayCurrentBalance(client.balance);
        }
        else
            break;

    } while (confirmAction("Do you want to quick withdraw again?"));
}

void normalWithdrawMenu(stClient& client)
{
    do
    {
        string errorMsg = "";
        int amount;
        do
        {
            printScreenHeader("Normal Withdraw");
            displayCurrentBalance(client.balance);

            cout << errorMsg;

            cout << "\nEnter an amount to withdraw (Multiple of 5):\n";
            cin >> amount;
        } while (!isValidWithdraw(client, amount, errorMsg, false));

        if (confirmAction("Do you want to withdraw " + formatMoney(amount) + " from your account?"))
        {
            client.balance -= amount;
            cout << "\nAn amount of " << amount << " was successfully withdrawn.\n";

            displayCurrentBalance(client.balance);
        }
        


    } while (confirmAction("Do you want to normal withdraw again?"));
}

bool isValidDeposit(int amount, string &errorMsg)
{
    if (amount > 0)
    {
        return true;
    }

    if (amount <= 0)
    {
        errorMsg= "\nERROR! Deposit amount must be positive. Try again.\n";
        return false;
    }
}

void depositMenu(stClient& client)
{
    do
    {
        int amount;
        string errorMsg = "";
        do
        {
            printScreenHeader("Deposit");
            displayCurrentBalance(client.balance);

            cout << errorMsg;

            cout << "\nEnter amount to deposit:\n";
            cin >> amount;
        } while (!isValidDeposit(amount,errorMsg));

        if (confirmAction("Do you want to deposit an amount of " + formatMoney(amount) + " to your account?"))
        {
            client.balance += amount;
            cout << "\nAn amount of " << amount << " was successfully deposited to your account!\n";
            displayCurrentBalance(client.balance);
        }

    } while (confirmAction("Do you want to deposit more?"));
}

void checkBalanceMenu(stClient& client)
{
    printScreenHeader("Check Balance");
    displayCurrentBalance(client.balance);
    cout << string(50, '=') << "\n";
}

void logoutDialog() {
    system("cls");
    cout << "\nSuccessfully logged out!\n\n"
        << "Returning to login screen...\n";

    Sleep(2000);
}

void printMainMenu()
{
    printScreenHeader("ATM Main Menu");
    cout
        << "\t[1] Quick Withdraw.\n"
        << "\t[2] Normal Withdraw.\n"
        << "\t[3] Deposit\n"
        << "\t[4] Check Balance\n"
        << "\t[5] Logout\n"
        << string(50, '=') 
        << "\n";
}

bool isLoginValid(const vector<stClient>& vClients, const string& accountNumber, const string& pinCode, short& idx)
{
    for (size_t i = 0; i < vClients.size(); ++i)
    {
        if ((stringToLower(vClients[i].accountNumber) == stringToLower(accountNumber)) && vClients[i].pinCode == pinCode)
        {
            idx = (short)i;
            return true;
        }
    }
    return false;
}

void showLoginAttempts(short remaining)
{
    cout << "\nInvalid Credentials! Attempts Remaining: (" << remaining << ")\n";
}

short loginUser(const vector<stClient> &vClients, bool& validLogin, short &idx)
{
    bool firstAttempt = true;
    int attempts = 3;

    while (attempts > 0)
    {
        printScreenHeader("Login");

        if (!firstAttempt)
            showLoginAttempts(attempts);

        string accountNumber = readString("\nEnter Account Number:\n");
        string pinCode = readString("\nEnter PIN Code:\n");

        if (isLoginValid(vClients, accountNumber, pinCode, idx))
        {
            return idx;
        }
        else
        {
            --attempts;
            firstAttempt = false;
        }
    }

    validLogin = false;
    return -1;
}

void ATM_SYSTEM()
{
    
    bool validLogin = true;
    short option = 0;
    short idx = 0;
    while (true)
    {
        vector<stClient> vClients = loadClientsFromFile();
        short index = loginUser(vClients, validLogin,idx);
        if (!validLogin)
        {
            system("cls");
            cout << "\n\t\t3 Attempts were made! Shutting off!\n\n";
            Sleep(2000);
            break;
        }

        while (true)
        {
            option = 0;
            printMainMenu();
            option = readOption(1, 5);

            switch (option)
            {
            case enMainMenu::enQuickWithdraw:
                quickWithdrawMenu(vClients[index]);
                break;
            case enMainMenu::enNormalWithdraw:
                normalWithdrawMenu(vClients[index]);
                break;
            case enMainMenu::enDeposit:
                depositMenu(vClients[index]);
                break;
            case enMainMenu::enCheckBalance:
                checkBalanceMenu(vClients[index]);
                break;
            case enMainMenu::enLogout:
                logoutDialog();
                saveClientsToFile(vClients);
                break;
            }
            if (option != enMainMenu::enLogout && option!= enMainMenu::enQuickWithdraw)
                goBackToMenu("go back to ATM Main Menu");
            if (option == enMainMenu::enLogout)
                break;
        }
    }
}

int main()
{
    ATM_SYSTEM();


    return 0;
}