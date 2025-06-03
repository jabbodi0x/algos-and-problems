#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdlib>

using namespace std;

const string CLIENTS_FILE_NAME = "clients.txt";
const string USERS_FILE_NAME = "users.txt";
const string SEPARATOR = "#//#";

struct stClient
{
    string accountNumber;
    string pinCode;
    string name;
    string phone;
    float  balance;
    bool   markedForDeletion = false;
};

struct stUser
{
    string userName;
    string passWord;      // TODO: Consider storing a hashed password instead of plain text
    int permissions;   // bit‐flags for allowed operations
    bool markedForDeletion = false;
};

enum enPermissions
{
    permShowClients = 1 << 0,  // 0000 0001 = 1
    permAddClient = 1 << 1,  // 0000 0010 = 2
    permDeleteClient = 1 << 2,  // 0000 0100 = 4
    permUpdateClient = 1 << 3,  // 0000 1000 = 8
    permFindClient = 1 << 4,  // 0001 0000 = 16
    permTransactions = 1 << 5,  // 0010 0000 = 32
    permManageUsers = 1 << 6   // 0100 0000 = 64
};

enum enBankMenu
{
    enShowAllClients = 1,
    enAddNewClient,
    enDeleteClient,
    enUpdateClient,
    enFindClient,
    enTransactions,
    enManageUsers,
    enLogout
};

enum enTransactionMenu
{
    enDeposit = 1,
    enWithdraw,
    enTotalBalance,
    enMainMenu
};

enum enUsersMenu
{
    enListUsers = 1,
    enAddUser,
    enDeleteUser,
    enUpdateUser,
    enFindUser,
    enMainMenuUsers
};

#pragma region UtilityFunctions

// Read a non-empty line of text from the user
string readString(const string& prompt = "Enter String:\n")
{
    string s;
    do
    {
        cout << prompt;
        cin >> ws;
        getline(cin, s);
    } while (s.empty());
    return s;
}

// Convert a string to all lowercase
string stringToLower(string s)
{
    for (char& c : s) c = tolower(c);
    return s;
}

// Read an integer option within [from, to], inclusive
short readOption(short from, short to)
{
    short choice = 0;
    do
    {
        cout << "\nChoose an option [" << from << "-" << to << "]: ";
        cin >> choice;
    } while (choice < from || choice > to);
    return choice;
}

// Split a string by a given delimiter into tokens
vector<string> splitString(const string& s, const string& delimiter = SEPARATOR)
{
    vector<string> tokens;
    size_t start = 0, end = s.find(delimiter);
    while (end != string::npos)
    {
        if (end > start)
            tokens.push_back(s.substr(start, end - start));
        start = end + delimiter.length();
        end = s.find(delimiter, start);
    }
    if (start < s.length())
        tokens.push_back(s.substr(start));
    return tokens;
}

// Print a header with a title, clearing the screen first
void printScreenHeader(const string& title)
{
    const int totalWidth = 50;
    string    fullTitle = title + " Screen";

    // TODO: Replace system("cls") with a cross‐platform clear, or simply rely on user pressing Enter
    system("cls");
    int leftPadding = (totalWidth - static_cast<int>(fullTitle.length())) / 2;
    if (leftPadding < 0) leftPadding = 0;

    cout << string(totalWidth, '=') << "\n";
    cout << string(leftPadding, ' ') << fullTitle << "\n";
    cout << string(totalWidth, '=') << "\n";
}

// Pause until the user presses a key, with a custom message
void goBackToMenu(const string& msg = "continue")
{
    cout << "\n\n\nPress any key to " << msg << "...";
    // TODO: For cross-platform compatibility, consider using cin.get() loop instead of system("pause>0")
    system("pause>0");
}

// Read a positive float from user, with validation and exception handling
float readPositiveFloat(const string& prompt)
{
    float value = 0.0f;
    string input;

    while (true)
    {
        cout << prompt;
        cin >> input;
        try
        {
            value = stof(input);
            if (value > 0.0f)
                return value;
            else
                cout << "  >> Amount must be greater than 0.\n";
        }
        catch (const invalid_argument&)
        {
            cout << "  >> Invalid number. Please enter a valid amount.\n";
        }
        catch (const out_of_range&)
        {
            cout << "  >> Number is out of range. Try again.\n";
        }
    }
}

#pragma endregion

#pragma region ClientFileIO

// Convert a line from the clients file into an stClient struct
stClient convertClientLineToStructure(const string& clientRecordLine)
{
    stClient client;
    vector<string> fields = splitString(clientRecordLine, SEPARATOR);
    
    client.accountNumber = fields[0];
    client.pinCode = fields[1];
    client.name = fields[2];
    client.phone = fields[3];
    client.balance = stof(fields[4]);

    return client;
}

// Convert an stClient struct into a single string line for file storage
string convertClientRecordToData(const stClient& client)
{

    return client.accountNumber + SEPARATOR
        + client.pinCode + SEPARATOR
        + client.name + SEPARATOR
        + client.phone + SEPARATOR
        + to_string(client.balance);
}

// Load all clients from the file into a vector
vector<stClient> loadClientsDataFromFile()
{
    vector<stClient> vClients;
    fstream myFile(CLIENTS_FILE_NAME, ios::in);
    if (myFile.is_open())
    {
        string   line;
        while (getline(myFile, line))
        {
            stClient client = convertClientLineToStructure(line);
            vClients.push_back(client);
        }
        myFile.close();
    }
    return vClients;
}

// Save all clients (except those marked for deletion) back to the file
void saveClientsToFile(const vector<stClient>& vClients)
{
    fstream myFile(CLIENTS_FILE_NAME, ios::out);
    if (myFile.is_open())
    {
        for (const stClient& client : vClients)
        {
            if (!client.markedForDeletion)
                myFile << convertClientRecordToData(client) << "\n";
        }
        myFile.close();
    }
    else
    {
        cout << "Error: Unable to open " << CLIENTS_FILE_NAME << " for writing.\n";
    }
}

#pragma endregion

#pragma region UserFileIO

// Convert a line from the users file into an stUser struct
stUser convertUserLineToStructure(const string& userRecordLine)
{
    stUser user;
    vector<string> fields = splitString(userRecordLine);
    if (fields.size() >= 3)
    {
        user.userName = fields[0];
        user.passWord = fields[1];
        user.permissions = stoi(fields[2]);
    }
    return user;
}

// Convert an stUser struct into a single string line for file storage
string convertUserRecordToData(const stUser& user)
{
    return user.userName + SEPARATOR
        + user.passWord + SEPARATOR
        + to_string(user.permissions);
}

// Load all users from the file into a vector
vector<stUser> loadUsersDataFromFile()
{
    vector<stUser> vUsers;
    fstream         myFile(USERS_FILE_NAME, ios::in);
    if (myFile.is_open())
    {
        string line;
        while (getline(myFile, line))
        {
            stUser user = convertUserLineToStructure(line);
            vUsers.push_back(user);
        }
        myFile.close();
    }

    return vUsers;
}

// Save all users (except those marked for deletion) back to the file
void saveUsersToFile(const vector<stUser>& vUsers)
{
    fstream myFile(USERS_FILE_NAME, ios::out);
    if (myFile.is_open())
    {
        for (const stUser& user : vUsers)
        {
            if (!user.markedForDeletion)
                myFile << convertUserRecordToData(user) << "\n";
        }
        myFile.close();
    }
    else
    {
        cout << "Error: Unable to open " << USERS_FILE_NAME << " for writing.\n";
    }
}

#pragma endregion

#pragma region PrintingClients

// Print one client's details in a formatted block
void printSingleClientRecord(const stClient& client)
{
    cout << "\n-----------[ Client Data ]-----------\n";
    cout << setw(15) << left << "Account Number" << ": " << client.accountNumber << "\n";
    cout << setw(15) << left << "Pin Code" << ": " << client.pinCode << "\n";
    cout << setw(15) << left << "Name" << ": " << client.name << "\n";
    cout << setw(15) << left << "Phone" << ": " << client.phone << "\n";
    cout << setw(15) << left << "Balance" << ": " << fixed << setprecision(2) << client.balance << "\n";
    cout << "-------------------------------------\n";
}

// Print one row in the clients table
void printClientRow(const stClient& client)
{
    cout << "| " << setw(15) << left << client.accountNumber
        << "| " << setw(10) << left << client.pinCode
        << "| " << setw(25) << left << client.name
        << "| " << setw(12) << left << client.phone
        << "| " << setw(12) << left << fixed << setprecision(2) << client.balance
        << " |" << "\n";
}

// Print all clients in a table format
void printAllClientsData(const vector<stClient>& vClients)
{
    const int tableWidth = 86;  // 2 + 15 + 2 + 10 + 2 + 25 + 2 + 12 + 2 + 12 + 2 = 86

    // Clear the screen before printing
    system("cls");

    cout << string(tableWidth, '=') << "\n";

    {
        string countLine = "(" + to_string(vClients.size()) + ") Client(s)";
        int    padLeft = (tableWidth - static_cast<int>(countLine.size())) / 2;
        if (padLeft < 0) padLeft = 0;
        cout << string(padLeft, ' ') << countLine << "\n";
    }

    cout << string(tableWidth, '=') << "\n";
    cout << "| " << left << setw(15) << "Account Number"
        << "| " << left << setw(10) << "Pin Code"
        << "| " << left << setw(25) << "Client Name"
        << "| " << left << setw(12) << "Phone"
        << "| " << left << setw(12) << "Balance"
        << " |" << "\n";
    cout << string(tableWidth, '=') << "\n";

    for (const stClient& client : vClients)
    {
        if (!client.markedForDeletion)
            printClientRow(client);
    }

    cout << string(tableWidth, '=') << "\n";
}

#pragma endregion

#pragma region ClientOperations

// Find index of a client by account number (returns -1 if not found)
short getClientIndexByAccountNumber(const vector<stClient>& vClients, const string& accountNumber)
{
    for (size_t i = 0; i < vClients.size(); i++)
    {
        if (vClients[i].accountNumber == accountNumber && !vClients[i].markedForDeletion)
            return (short)i;
    }
    return -1;
}

// Prompt repeatedly until a valid existing account number is entered
short getValidClientIndex(const vector<stClient>& vClients)
{
    string accountNumber;
    short  idx;
    do
    {
        accountNumber = readString("\nEnter Account Number:\n");
        idx = getClientIndexByAccountNumber(vClients, accountNumber);
        if (idx == -1)
            cout << "\nClient with account number " << accountNumber << " was NOT found. Try again.\n";
    } while (idx == -1);
    return idx;
}

// Prompt for new client data; ensures unique account number
stClient readClientData(const vector<stClient>& vClients)
{
    stClient client;
    while (true)
    {
        client.accountNumber = readString("\nEnter Account Number:\n");
        if (getClientIndexByAccountNumber(vClients, client.accountNumber) == -1)
            break;
        else
            cout << "\nAn account with number " << client.accountNumber << " already exists.\n";
    }

    client.pinCode = readString("\nEnter Pin Code:\n");
    client.name = readString("\nEnter Name:\n");
    client.phone = readString("\nEnter Phone Number:\n");
    client.balance = readPositiveFloat("\nEnter Account Balance:\n");  // Uses safer input

    return client;
}

// Ask for a yes/no confirmation; returns true if 'y' or 'Y'
bool confirmAction(const string& prompt)
{
    char answer;
    cout << "\n\n" << prompt << " [y/n]: ";
    cin >> answer;
    return tolower(answer) == 'y';
}

// Add one or more new clients to the vector
void addNewClient(vector<stClient>& vClients)
{
    do
    {
        printScreenHeader("Add Client");
        stClient client = readClientData(vClients);
        cout << "\nYou entered:\n";
        printSingleClientRecord(client);

        if (confirmAction("\nDo you want to add this client?"))
        {
            vClients.push_back(client);
            cout << "\nClient was added successfully!\n";
        }
        else
        {
            cout << "\nAdding client canceled.\n";
        }
    } while (confirmAction("Do you want to add another new client?"));
}

// Mark a client for deletion (soft delete) after confirmation
void deleteClient(vector<stClient>& vClients)
{
    do
    {
        printScreenHeader("Delete Client");
        short idx = getValidClientIndex(vClients);
        printSingleClientRecord(vClients[idx]);

        if (confirmAction("Do you want to remove this client?"))
        {
            vClients[idx].markedForDeletion = true;
            cout << "\nClient was deleted successfully!\n";
        }
        else
        {
            cout << "\nDeletion canceled.\n";
        }
    } while (confirmAction("Do you want to delete another client?"));
}

// Prompt for updated data fields (except account number)
void updateClientData(stClient& client)
{
    client.pinCode = readString("\nEnter new Pin Code:\n");
    client.name = readString("\nEnter new Name:\n");
    client.phone = readString("\nEnter new Phone Number:\n");
    client.balance = readPositiveFloat("\nEnter Account Balance:\n");  // Uses safer input
}

// Update an existing client after confirmation
void updateClient(vector<stClient>& vClients)
{
    do
    {
        printScreenHeader("Update Client");
        short idx = getValidClientIndex(vClients);
        printSingleClientRecord(vClients[idx]);

        if (confirmAction("Do you want to update this client?"))
        {
            updateClientData(vClients[idx]);
            cout << "\nClient was updated successfully!\n";
            cout << "\nUpdated data:\n";
            printSingleClientRecord(vClients[idx]);
        }
        else
        {
            cout << "\nUpdate canceled.\n";
        }
    } while (confirmAction("Do you want to update another client?"));
}

// Find and display a client by account number
void findClient(const vector<stClient>& vClients)
{
    do
    {
        printScreenHeader("Find Client");
        short idx = getValidClientIndex(vClients);
        cout << "\n\nAccount Found!\n\n";
        printSingleClientRecord(vClients[idx]);
    } while (confirmAction("Do you want to find another client?"));
}

// Prompt for a valid withdraw amount (cannot exceed balance)
float getProperWithdrawAmount(const stClient& client)
{
    float amt;
    do
    {
        cout << "\nEnter amount to withdraw:\n";
        cin >> amt;
        if (amt <= 0)
            cout << "\nWithdraw amount must be greater than 0.\n";
        else if (amt > client.balance)
            cout << "\nBalance is less than the withdraw amount!\n";
    } while (amt <= 0 || amt > client.balance);
    return amt;
}

// Add funds to a client's balance
void depositToClient(stClient& client, float amount)
{
    client.balance += amount;
    // Suggestion: You could append a transaction log here (e.g., write to a transactions.txt file)
}

// Subtract funds from a client's balance
void withdrawFromClient(stClient& client, float amount)
{
    client.balance -= amount;
    // Suggestion: You could append a transaction log here as well
}

// Handle the deposit workflow for one or more clients
void depositMenu(vector<stClient>& vClients)
{
    do
    {
        printScreenHeader("Deposit");
        short idx = getValidClientIndex(vClients);

        do
        {
            float amount = readPositiveFloat("\nEnter Amount to Deposit:\n");  // Uses safer input
            if (confirmAction("Perform this transaction?"))
            {
                depositToClient(vClients[idx], amount);
                cout << "\nAmount of " << fixed << setprecision(2) << amount << " was successfully deposited to account: " << vClients[idx].accountNumber << "\n";
            }
            else
            {
                cout << "\nTransaction canceled.\n";
            }
        } while (confirmAction("Do you want to deposit more to this client's account?"));
    } while (confirmAction("Do you want to deposit to another client's account?"));
}

// Handle the withdrawal workflow for one or more clients
void withdrawMenu(vector<stClient>& vClients)
{
    do
    {
        printScreenHeader("Withdraw");
        short idx = getValidClientIndex(vClients);

        do
        {
            float amount = getProperWithdrawAmount(vClients[idx]);
            if (confirmAction("Perform this transaction?"))
            {
                withdrawFromClient(vClients[idx], amount);
                cout << "Amount of " << fixed << setprecision(2) << amount << " was successfully withdrawn from account: " << vClients[idx].accountNumber << "\n";
            }
            else
            {
                cout << "\nTransaction canceled.\n";
            }
        } while (confirmAction("Do you want to withdraw more from this client's account?"));
    } while (confirmAction("Do you want to withdraw from another client's account?"));
}

// Display the total balance for a selected client
void totalBalanceMenu(const vector<stClient>& vClients)
{
    do
    {
        printScreenHeader("Total Balance");
        short idx = getValidClientIndex(vClients);
        cout << "\nClient with account number " << vClients[idx].accountNumber << " has a total balance of " << fixed << setprecision(2) << vClients[idx].balance << "\n";
    } while (confirmAction("Would you like to see another client's total balance?"));
}

// Show the transactions sub-menu options
void transactionMenu()
{
    cout << "\t[1] Deposit\n";
    cout << "\t[2] Withdraw\n";
    cout << "\t[3] Total Balance\n";
    cout << "\t[4] Main Menu\n";
    cout << "===============================================\n";
}

// Main transactions loop (deposit, withdraw, check balance)
void transactions(vector<stClient>& vClients)
{
    short option = 0;
    do
    {
        printScreenHeader("Transactions Menu");
        transactionMenu();
        option = readOption(1, 4);

        switch (option)
        {
        case enDeposit:
            depositMenu(vClients);
            break;
        case enWithdraw:
            withdrawMenu(vClients);
            break;
        case enTotalBalance:
            totalBalanceMenu(vClients);
            break;
        case enMainMenu:
            break;
        }
        if (option != enMainMenu)
            goBackToMenu("go back to Transactions Menu");
    } while (option != enMainMenu);
}

#pragma endregion

#pragma region PrintingUsers

// Print one user’s details in a formatted block
void printSingleUserRecord(const stUser& user)
{
    cout << "\n-----------[ User Data ]-----------\n";
    cout << setw(15) << left << "Username" << ": " << user.userName << "\n";
    cout << setw(15) << left << "Password" << ": " << user.passWord << "\n";
    // TODO: In production, never print the plain password to the screen.
    cout << setw(15) << left << "Permissions" << ": " << user.permissions << "\n";
    cout << "-------------------------------------\n";
}

// Print one row in the users table
void printUserRow(const stUser& user)
{
    cout << "| " << setw(15) << left << user.userName
        << "| " << setw(25) << left << user.passWord
        << "| " << setw(5) << left << user.permissions
        << " |" << "\n";
}

// Print all users in a table format
void printAllUsersData(const vector<stUser>& vUsers)
{
    const int tableWidth = 53;  // 2 + 15 + 2 + 25 + 2 + 5 + 2 = 53

    system("cls");

    cout << string(tableWidth, '=') << "\n";

    {
        string countLine = "(" + to_string(vUsers.size()) + ") User(s)";
        int    padLeft = (tableWidth - static_cast<int>(countLine.size())) / 2;
        if (padLeft < 0) padLeft = 0;
        cout << string(padLeft, ' ') << countLine << "\n";
    }

    cout << string(tableWidth, '=') << "\n";
    cout << "| " << left << setw(15) << "Username"
        << "| " << left << setw(25) << "Password"
        << "| " << left << setw(5) << "Perms"
        << " |" << "\n";
    cout << string(tableWidth, '=') << "\n";

    for (const stUser& user : vUsers)
    {
        if (!user.markedForDeletion)
            printUserRow(user);
    }

    cout << string(tableWidth, '=') << "\n";
}

#pragma endregion

#pragma region UserManagementStubs

// Find index of a user by username (case-insensitive); returns -1 if not found
short getuUserIndexByUsername(const vector<stUser>& vUsers, const string& username)
{
    for (size_t i = 0; i < vUsers.size(); ++i)
    {
        if (stringToLower(vUsers[i].userName) == stringToLower(username) && !vUsers[i].markedForDeletion)
        {
            return (short)i;
        }
    }
    return -1;
}

// Prompt repeatedly until a valid existing username is entered
short getValidUserIndex(const vector<stUser>& vUsers)
{
    string username;
    short  idx;
    do
    {
        username = readString("\nEnter Username:\n");
        idx = getuUserIndexByUsername(vUsers, username);
        if (idx == -1)
            cout << "\nUser with username '" << username << "' was NOT found. Try again.\n";
    } while (idx == -1);
    return idx;
}

// Read new user data, ensuring unique username and setting permissions
stUser readUserData(const vector<stUser>& vUsers)
{
    stUser user;
    string username;

    // 1) Username must be unique
    while (true)
    {
        username = readString("\nEnter Username:\n");
        if (getuUserIndexByUsername(vUsers, username) == -1)
        {
            user.userName = username;
            break;
        }
        else
            cout << "\nA user with username '" << username << "' already exists. Try again.\n";
    }

    // 2) Read password
    user.passWord = readString("\nEnter Password:\n");
    // TODO: In production, enforce stronger password rules (e.g., minimum length, complexity)

    // 3) Set permissions using the enum masks
    user.permissions = 0;
    cout << "\nSet Permissions:\n";
    if (confirmAction(" 1- Show Clients List"))   user.permissions |= permShowClients;
    if (confirmAction(" 2- Add New Clients"))     user.permissions |= permAddClient;
    if (confirmAction(" 3- Delete Clients"))      user.permissions |= permDeleteClient;
    if (confirmAction(" 4- Update Clients"))      user.permissions |= permUpdateClient;
    if (confirmAction(" 5- Find Clients"))        user.permissions |= permFindClient;
    if (confirmAction(" 6- Transactions"))        user.permissions |= permTransactions;
    if (confirmAction(" 7- Manage Users"))        user.permissions |= permManageUsers;

    return user;
}

// Display all users
void listUsers(const vector<stUser>& vUsers)
{
    printAllUsersData(vUsers);
}

// Add one or more new users
void addUser(vector<stUser>& vUsers)
{
    do
    {
        printScreenHeader("Add User");
        stUser user = readUserData(vUsers);

        cout << "\nYou entered:\n";
        printSingleUserRecord(user);

        if (confirmAction("\nDo you want to add this user?"))
        {
            vUsers.push_back(user);
            cout << "\nUser was added successfully!\n";
        }
        else
        {
            cout << "\nAdding user canceled.\n";
        }
    } while (confirmAction("\nDo you want to add another new user?"));
}

// Mark a user for deletion
void deleteUser(vector<stUser>& vUsers)
{
    do
    {
        printScreenHeader("Delete User");
        short idx = getValidUserIndex(vUsers);
        printSingleUserRecord(vUsers[idx]);

        if (confirmAction("\nDo you want to remove this user?"))
        {
            vUsers[idx].markedForDeletion = true;
            cout << "\nUser was deleted successfully!\n";
        }
        else
        {
            cout << "\nDeletion canceled.\n";
        }
    } while (confirmAction("\nDo you want to delete another user?"));
}

// Prompt for updated password and permissions for an existing user
void updateUserData(stUser& user)
{
    user.passWord = readString("Enter new Password:\n");
    // TODO: Enforce password policy here as well
    user.permissions = 0;

    cout << "\nSet New Permissions:\n";
    if (confirmAction(" 1- Show Clients List"))   user.permissions |= permShowClients;
    if (confirmAction(" 2- Add New Clients"))     user.permissions |= permAddClient;
    if (confirmAction(" 3- Delete Clients"))      user.permissions |= permDeleteClient;
    if (confirmAction(" 4- Update Clients"))      user.permissions |= permUpdateClient;
    if (confirmAction(" 5- Find Clients"))        user.permissions |= permFindClient;
    if (confirmAction(" 6- Transactions"))        user.permissions |= permTransactions;
    if (confirmAction(" 7- Manage Users"))        user.permissions |= permManageUsers;
}

// Update one or more existing users
void updateUser(vector<stUser>& vUsers)
{
    do
    {
        printScreenHeader("Update User");
        short idx = getValidUserIndex(vUsers);
        printSingleUserRecord(vUsers[idx]);

        if (confirmAction("\nDo you want to update this user?"))
        {
            updateUserData(vUsers[idx]);
            cout << "\nUser was updated successfully!\n";
            cout << "\nUpdated data:\n";
            printSingleUserRecord(vUsers[idx]);
        }
        else
        {
            cout << "\nUpdate canceled.\n";
        }
    } while (confirmAction("\nDo you want to update another user?"));
}

// Find and display one user by username
void findUser(const vector<stUser>& vUsers)
{
    do
    {
        printScreenHeader("Find User");
        short idx = getValidUserIndex(vUsers);
        cout << "\n\nUser Found!\n\n";
        printSingleUserRecord(vUsers[idx]);
    } while (confirmAction("\nDo you want to find another user?"));
}

// Print the Manage Users menu options
void printManageUsersMenu()
{
    printScreenHeader("Manage Users");
    cout << "\t[1] List Users\n";
    cout << "\t[2] Add User\n";
    cout << "\t[3] Delete User\n";
    cout << "\t[4] Update User\n";
    cout << "\t[5] Find User\n";
    cout << "\t[6] Main Menu\n";
    cout << "===============================================\n";
}

// Main loop for managing users (list, add, delete, update, find)
void manageUsers(vector<stUser>& vUsers)
{
    short option = 0;
    do
    {
        printManageUsersMenu();
        option = readOption(1, 6);

        switch (option)
        {
        case enListUsers:
            listUsers(vUsers);
            break;
        case enAddUser:
            addUser(vUsers);
            break;
        case enDeleteUser:
            deleteUser(vUsers);
            break;
        case enUpdateUser:
            updateUser(vUsers);
            break;
        case enFindUser:
            findUser(vUsers);
            break;
        case enMainMenuUsers:
            break;
        }
        if (option != enMainMenuUsers)
            goBackToMenu("go back to Manage Users menu");
    } while (option != enMainMenuUsers);
}

#pragma endregion

#pragma region AuthenticationAndPermissions

// Check if the user has a specific permission bit
bool hasPermission(const stUser& user, enPermissions perm)
{
    return ((user.permissions & perm) != 0);
}

// Validate username/password and return the index of the matching user
bool isLoginValid(const vector<stUser>& vUsers, const string& username, const string& password, short& idx)
{
    for (size_t i = 0; i < vUsers.size(); ++i)
    {
        if ((stringToLower(vUsers[i].userName) == stringToLower(username)) &&
            vUsers[i].passWord == password)
        {
            idx = (short)i;
            return true;
        }
    }
    return false;
}

// Repeatedly prompt for username/password until valid login occurs
stUser loginUser(const vector<stUser>& vUsers)
{
    short idx = 0;
    bool  firstAttempt = true;
    while (true)
    {
        system("cls");
        printScreenHeader("Login");

        if (!firstAttempt)
            cout << "\nInvalid Username OR Password! Try Again.\n\n";

        string username = readString("Username:\n");
        string password = readString("Password:\n");
        if (isLoginValid(vUsers, username, password, idx))
            return vUsers[idx];
        else
            firstAttempt = false;
    }
}

#pragma endregion

#pragma region MainMenu

// Print the main bank menu options
void printMainMenu()
{
    printScreenHeader("Main Menu");
    cout << "\t[1] Show Client List\n";
    cout << "\t[2] Add New Client\n";
    cout << "\t[3] Delete Client\n";
    cout << "\t[4] Update Client Info\n";
    cout << "\t[5] Find Client\n";
    cout << "\t[6] Transactions\n";
    cout << "\t[7] Manage Users\n";
    cout << "\t[8] Logout\n";
    cout << "===============================================\n";
}

// Main application loop: login, show menu, handle choices, save data on logout
void bank()
{
    vector<stClient> vClients = loadClientsDataFromFile();
    vector<stUser> vUsers = loadUsersDataFromFile();

    while (true)
    {
        stUser currentUser = loginUser(vUsers);

        short option = 0;
        do
        {
            printMainMenu();
            option = readOption(1, 8);

            bool skipOuterPause = false;

            switch (option)
            {
            case enShowAllClients:
                if (hasPermission(currentUser, permShowClients))
                {
                    printAllClientsData(vClients);
                    skipOuterPause = false;
                }
                else
                {
                    cout << "\nPermission Denied: Cannot view clients.\n";
                    goBackToMenu("return to Main Menu");
                    skipOuterPause = true;
                }
                break;

            case enAddNewClient:
                if (hasPermission(currentUser, permAddClient))
                {
                    addNewClient(vClients);
                    skipOuterPause = false;
                }
                else
                {
                    cout << "\nPermission Denied: Cannot add new client.\n";
                    goBackToMenu("return to Main Menu");
                    skipOuterPause = true;
                }
                break;

            case enDeleteClient:
                if (hasPermission(currentUser, permDeleteClient))
                {
                    deleteClient(vClients);
                    skipOuterPause = false;
                }
                else
                {
                    cout << "\nPermission Denied: Cannot delete client.\n";
                    goBackToMenu("return to Main Menu");
                    skipOuterPause = true;
                }
                break;

            case enUpdateClient:
                if (hasPermission(currentUser, permUpdateClient))
                {
                    updateClient(vClients);
                    skipOuterPause = false;
                }
                else
                {
                    cout << "\nPermission Denied: Cannot update client.\n";
                    goBackToMenu("return to Main Menu");
                    skipOuterPause = true;
                }
                break;

            case enFindClient:
                if (hasPermission(currentUser, permFindClient))
                {
                    findClient(vClients);
                    skipOuterPause = false;
                }
                else
                {
                    cout << "\nPermission Denied: Cannot find client.\n";
                    goBackToMenu("return to Main Menu");
                    skipOuterPause = true;
                }
                break;

            case enTransactions:
                skipOuterPause = true;
                if (hasPermission(currentUser, permTransactions))
                {
                    transactions(vClients);
                }
                else
                {
                    cout << "\nPermission Denied: Cannot perform transactions.\n";
                    goBackToMenu("return to Main Menu");
                }
                break;

            case enManageUsers:
                skipOuterPause = true;
                if (hasPermission(currentUser, permManageUsers))
                {
                    manageUsers(vUsers);
                }
                else
                {
                    cout << "\nPermission Denied: Cannot manage users.\n";
                    goBackToMenu("return to Main Menu");
                }
                break;

            case enLogout:
                saveClientsToFile(vClients);
                saveUsersToFile(vUsers);
                break;
            }

            if (!skipOuterPause && option != enLogout)
                goBackToMenu("return to Main Menu");

        } while (option != enLogout);
    }
}

#pragma endregion

int main()
{
    bank();
    cout << "\n\nThank you for using the Bank Management System!\nGoodbye!\n";
    return 0;
}