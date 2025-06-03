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
    string accountNumber, name, phone, pinCode;
    float  balance;
    bool   markedForDeletion = false;
};

struct stUser
{
    string userName;
    string passWord;
    int    permissions;    // bit‐flags for allowed operations
    bool   markedForDeletion = false;
};

// Permission bits (use powers of two)
enum enPermissions
{
    permShowClients = 1 << 0,  // 0000 0001
    permAddClient = 1 << 1,  // 0000 0010
    permDeleteClient = 1 << 2,  // 0000 0100
    permUpdateClient = 1 << 3,  // 0000 1000
    permFindClient = 1 << 4,  // 0001 0000
    permTransactions = 1 << 5,  // 0010 0000
    permManageUsers = 1 << 6   // 0100 0000
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

string stringToLower(string s)
{
    for (char& c : s)
    {
        c = tolower(c);
    }

    return s;
}

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

vector<string> splitString(const string& s, const string& delimiter = SEPARATOR)
{
    vector<string> tokens;
    size_t start = 0;
    size_t end = s.find(delimiter);

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

void printScreenHeader(const string& title)
{
    const int totalWidth = 50;
    string fullTitle = title + " Screen";

    system("cls");
    int leftPadding = (totalWidth - fullTitle.length()) / 2;
    if (leftPadding < 0) leftPadding = 0;

    cout << string(totalWidth, '=') << "\n";
    cout << string(leftPadding, ' ') << fullTitle << "\n";
    cout << string(totalWidth, '=') << "\n";
}

void goBackToMenu(const string& msg = "continue")
{
    cout << "\n\n\n" << "Press any key to " << msg << "...";
    system("pause>0");
}

#pragma endregion

#pragma region ClientFileIO

stClient convertClientLineToStructure(const string& clientRecordLine)
{
    stClient       client;
    vector<string> fields = splitString(clientRecordLine, SEPARATOR);

    // Expecting: accountNumber #//# pinCode #//# name #//# phone #//# balance
    if (fields.size() == 5)
    {
        client.accountNumber = fields[0];
        client.pinCode = fields[1];
        client.name = fields[2];
        client.phone = fields[3];
        client.balance = stof(fields[4]);
    }
    return client;
}

string convertClientRecordToData(const stClient& client)
{
    // accountNumber #//# pinCode #//# name #//# phone #//# balance
    return client.accountNumber + SEPARATOR
        + client.pinCode + SEPARATOR
        + client.name + SEPARATOR
        + client.phone + SEPARATOR
        + to_string(client.balance);
}

vector<stClient> loadClientsDataFromFile()
{
    vector<stClient> vClients;
    fstream          myFile(CLIENTS_FILE_NAME, ios::in);

    if (myFile.is_open())
    {
        string   line;
        stClient client;
        while (getline(myFile, line))
        {
            client = convertClientLineToStructure(line);
            vClients.push_back(client);
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
        for (const stClient& client : vClients)
        {
            if (!client.markedForDeletion)
                myFile << convertClientRecordToData(client) << "\n";
        }
        myFile.close();
    }
}

#pragma endregion

#pragma region UserFileIO

stUser convertUserLineToStructure(const string& userRecordLine)
{
    stUser user;
    vector<string> fields = splitString(userRecordLine);

    user.userName = fields[0];
    user.passWord = fields[1];
    user.permissions = stoi(fields[2]);

    return user;
}

string convertUserRecordToData(const stUser& user)
{
    // userName #//# passWord #//# permissions
    return user.userName + SEPARATOR
        + user.passWord + SEPARATOR
        + to_string(user.permissions);
}

vector<stUser> loadUsersDataFromFile()
{
    vector<stUser> vUsers;
    fstream myFile(USERS_FILE_NAME, ios::in);

    if (myFile.is_open())
    {
        string line;
        stUser user;
        while (getline(myFile, line))
        {
            user = convertUserLineToStructure(line);
            vUsers.push_back(user);
        }
        myFile.close();
    }
    return vUsers;
}

void saveUsersToFile(const vector<stUser>& vUsers)
{
    fstream myFile(USERS_FILE_NAME, ios::out);
    if (myFile.is_open())
    {
        for (const stUser& user : vUsers)
            if (!user.markedForDeletion)
                myFile << convertUserRecordToData(user) << "\n";
        myFile.close();
    }
}

#pragma endregion

#pragma region PrintingClients

void printSingleClientRecord(const stClient& client)
{
    cout << "\n-----------[ Client Data ]-----------\n";
    cout << setw(15) << left << "Account Number" << ": " << client.accountNumber << "\n";
    cout << setw(15) << left << "Pin Code" << ": " << client.pinCode << "\n";
    cout << setw(15) << left << "Name" << ": " << client.name << "\n";
    cout << setw(15) << left << "Phone" << ": " << client.phone << "\n";
    cout << setw(15) << left << "Balance" << ": " << client.balance << "\n";
    cout << "-------------------------------------\n";
}

void printClientRow(const stClient& client)
{
    cout << "| " << setw(15) << left << client.accountNumber
        << "| " << setw(10) << left << client.pinCode
        << "| " << setw(40) << left << client.name
        << "| " << setw(12) << left << client.phone
        << "| " << setw(12) << left << client.balance
        << "\n";
}

void printAllClientsData(const vector<stClient>& vClients)
{
    system("cls");
    cout << "================================================================================================\n";
    cout << "\n\t\t\t(" << vClients.size() << ") Client(s)\n";
    cout << "================================================================================================\n";
    cout << "| " << left << setw(15) << "Account Number"
        << "| " << left << setw(10) << "Pin Code"
        << "| " << left << setw(40) << "Client Name"
        << "| " << left << setw(12) << "Phone"
        << "| " << left << setw(12) << "Balance"
        << "\n";
    cout << "================================================================================================\n";

    for (const stClient& client : vClients)
        if (!client.markedForDeletion)
            printClientRow(client);

    cout << "================================================================================================\n";
}

#pragma endregion

#pragma region ClientOperations

short getClientIndexByAccountNumber(const vector<stClient>& vClients, const string& accountNumber)
{
    for (size_t i = 0; i < vClients.size(); i++)
    {
        if (vClients[i].accountNumber == accountNumber && !vClients[i].markedForDeletion)
        {
            return i;
        }
    }
    return -1;
}

short getValidClientIndex(const vector<stClient>& vClients)
{
    string accountNumber;
    short  idx;
    do
    {
        accountNumber = readString("\nEnter Account Number:\n");
        idx = getClientIndexByAccountNumber(vClients, accountNumber);
        if (idx == -1)
            cout << "Client with account number " << accountNumber << " was NOT found. Try again.\n";
    } while (idx == -1);
    return idx;
}

stClient readClientData(const vector<stClient>& vClients)
{
    stClient client;
    string accountNumber;

    while (true)
    {
        accountNumber = readString("Enter Account Number:\n");
        if (getClientIndexByAccountNumber(vClients, accountNumber) == -1)
        {
            client.accountNumber = accountNumber;
            break;
        }
        else
            cout << "An account with number " << accountNumber << " already exists.\n";
    }

    client.pinCode = readString("Enter Pin Code:\n");
    client.name = readString("Enter Name:\n");
    client.phone = readString("Enter Phone Number:\n");
    client.balance = stof(readString("Enter Account Balance:\n"));

    return client;
}

bool confirmAction(const string& prompt)
{
    char answer;
    cout << "\n" << prompt << " [y/n]: ";
    cin >> answer;
    return tolower(answer) == 'y';
}

void addNewClient(vector<stClient>& vClients)
{
    do
    {
        printScreenHeader("Add Client");
        stClient client = readClientData(vClients);

        cout << "\nYou entered:\n";
        printSingleClientRecord(client);

        if (confirmAction("Do you want to add this client?"))
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

void updateClientData(stClient& client)
{
    client.pinCode = readString("Enter new Pin Code:\n");
    client.name = readString("Enter new Name:\n");
    client.phone = readString("Enter new Phone Number:\n");
    client.balance = stof(readString("Enter Account Balance:\n"));
}

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

float getPositiveAmount(const string& prompt)
{
    float amt;
    do
    {
        cout << prompt;
        cin >> amt;
    } while (amt <= 0);
    return amt;
}

float getProperWithdrawAmount(const stClient& client)
{
    float amt;
    do
    {
        cout << "\nEnter amount to withdraw:\n";
        cin >> amt;
        if (amt <= 0)
            cout << "Withdraw amount must be greater than 0.\n";
        else if (amt > client.balance)
            cout << "Balance is less than the withdraw amount!\n";
    } while (amt <= 0 || amt > client.balance);
    return amt;
}

void depositToClient(stClient& client, float amount)
{
    client.balance += amount;
}

void withdrawFromClient(stClient& client, float amount)
{
    client.balance -= amount;
}

void depositMenu(vector<stClient>& vClients)
{
    do
    {
        printScreenHeader("Deposit");
        short idx = getValidClientIndex(vClients);

        do
        {
            float amount = getPositiveAmount("\nEnter Amount to Deposit:\n");
            if (confirmAction("Perform this transaction?"))
            {
                depositToClient(vClients[idx], amount);
                cout << "Amount of " << amount << " was successfully deposited to account: " << vClients[idx].accountNumber << "\n";
            }
            else
            {
                cout << "\nTransaction canceled.\n";
            }
        } while (confirmAction("Do you want to deposit more to this client's account?"));
    } while (confirmAction("Do you want to deposit to another client's account?"));
    
}

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
                cout << "Amount of " << amount << " was successfully withdrawn from account: " << vClients[idx].accountNumber << "\n";
            }
            else
            {
                cout << "\nTransaction canceled.\n";
            }
        } while (confirmAction("Do you want to withdraw more from this client's account?"));
    } while (confirmAction("Do you want to withdraw from another client's account?"));
    
}

void totalBalanceMenu(const vector<stClient>& vClients)
{
    do
    {
        printScreenHeader("Total Balance");
        short idx = getValidClientIndex(vClients);
        cout << "\nClient with account number " << vClients[idx].accountNumber << " has a total balance of " << fixed << setprecision(2) << vClients[idx].balance << "\n";
    } while (confirmAction("Would you like to see another client's total balance?"));
    
}

void transactionMenu()
{
    cout << "\t[1] Deposit\n";
    cout << "\t[2] Withdraw\n";
    cout << "\t[3] Total Balance\n";
    cout << "\t[4] Main Menu\n";
    cout << "===============================================\n";
}

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
            goBackToMenu();
    } while (option != enMainMenu);
}

#pragma endregion

#pragma region PrintingUsers

void printSingleUserRecord(const stUser& user)
{
    cout << "\n-----------[ User Data ]-----------\n";
    cout << setw(15) << left << "Username:" << ": " << user.userName << "\n";
    cout << setw(25) << left << "Password" << ": " << user.passWord << "\n";
    cout << setw(15) << left << "Permissions" << ": " << user.permissions << "\n";
    cout << "-------------------------------------\n";
}

void printUserRow(const stUser& user)
{
    cout << "| " << setw(15) << left << user.userName
        << "| " << setw(25) << left << user.passWord
        << "| " << setw(3) << left << user.permissions
        << "\n";
}

void printAllUserssData(const vector<stUser>& vUsers)
{
    system("cls");
    cout << "\n\t\t\t(" << vUsers.size() << ") User(s)\n";
    cout << "===========================================================\n";
    cout 
        << "| " << left << setw(15) << "Username"
        << "| " << left << setw(25) << "Password"
        << "| " << left << setw(3) << "Permissions"
        << "\n";
    cout << "===========================================================\n";

    for (const stUser& user : vUsers)
        if (!user.markedForDeletion)
            printUserRow(user);

    cout << "===========================================================\n";
}

#pragma endregion



#pragma region UserManagementStubs

short getuUserIndexByUsername(const vector<stUser>& vUsers, const string& username)
{
	for (size_t i = 0; i < vUsers.size(); ++i)
	{
		if (stringToLower(vUsers[i].userName) == stringToLower(username) && !vUsers[i].markedForDeletion)
		{
			return i;
		}
	}
	return -1;
}

short getValidUserIndex(const vector<stUser>& vUsers)
{
	string username;
	short idx;
	do
	{
		username = readString("Enter Username:\n");
		idx = getuUserIndexByUsername(vUsers, username);
		if (idx == -1)
			cout << "User with username '" << username << "' was NOT found. Try again.\n";
	} while (idx == -1);
	return idx;
}

stUser readUserData(const vector<stUser>& vUsers)
{
	stUser user;
	string username;

	while (true)
	{
		username = readString("Enter Username:\n");
		if (getuUserIndexByUsername(vUsers, username) == -1)
		{
			user.userName = username;
			break;
		}
		else
			cout << "A user with username '" << username << "' already exists or is reserved. Try again.\n";
	}

	user.passWord = readString("Enter Password:\n");

    cout << "\nPermissions\n";
    user.permissions += (confirmAction("1- Show Clients List") ? 2 : 0);
    user.permissions += (confirmAction("2- Add New Clients") ? 4 : 0);
    user.permissions += (confirmAction("3- Delete Clients") ? 8 : 0);
    user.permissions += (confirmAction("4- Update Clients") ? 16 : 0);
    user.permissions += (confirmAction("5- Find Clients") ? 32 : 0);
    user.permissions += (confirmAction("6- Manage Users") ? 64 : 0);


	return user;
}
void listUsers(const vector<stUser>& vUsers)
{
    printAllUserssData(vUsers);
}

void addUser(vector<stUser>& vUsers)
{
    do
    {
        printScreenHeader("Add User");
		stUser user = readUserData(vUsers);

		cout << "\nYou entered:\n";
		printSingleUserRecord(user);

		if (confirmAction("Do you want to add this user?"))
		{
			vUsers.push_back(user);
			cout << "\nUser was added successfully!\n";
		}
		else
		{
			cout << "\nAdding user canceled.\n";
		}
    } while (confirmAction("Do you want to add another new user?"));
}

void deleteUser(vector<stUser>& vUsers)
{
    do
    {
        printScreenHeader("Delete User");

        short idx = getValidUserIndex(vUsers);
        printSingleUserRecord(vUsers[idx]);

        if (confirmAction("Do you want to remove this user?"))
        {
            vUsers[idx].markedForDeletion = true;
            cout << "\nUser was deleted successfully!\n";
        }
        else
        {
            cout << "\nDeletion canceled.\n";
        }
    } while (confirmAction("Do you want to delete another user?"));
}

void updateUserData(stUser& user)
{
    user.passWord = readString("Enter new Password:\n");

    cout << "\nPermissions\n";
    user.permissions = 0; // Reset permissions
    user.permissions += (confirmAction("1- Show Clients List") ? 2 : 0);
    user.permissions += (confirmAction("2- Add New Clients") ? 4 : 0);
    user.permissions += (confirmAction("3- Delete Clients") ? 8 : 0);
    user.permissions += (confirmAction("4- Update Clients") ? 16 : 0);
    user.permissions += (confirmAction("5- Find Clients") ? 32 : 0);
    user.permissions += (confirmAction("6- Manage Users") ? 64 : 0);
}

void updateUser(vector<stUser>& vUsers)
{
    do
    {
        printScreenHeader("Update User");

        short idx = getValidUserIndex(vUsers);
        printSingleUserRecord(vUsers[idx]);

        if (confirmAction("Do you want to update this user?"))
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
    } while (confirmAction("Do you want to update another user?"));
}

void findUser(const vector<stUser>& vUsers)
{
    do
    {
        printScreenHeader("Find User");
        short idx = getValidUserIndex(vUsers);
        cout << "\n\nUser Found!\n\n";
        printSingleUserRecord(vUsers[idx]);
    } while (confirmAction("Do you want to find another user?"));
}

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
            goBackToMenu("Go back to manage users menu");
    } while (option != enMainMenuUsers);
}

#pragma endregion

#pragma region AuthenticationAndPermissions

bool hasPermission(const stUser& user, enPermissions perm)
{
    return ((user.permissions & perm) != 0);
}

bool isLoginValid(const vector<stUser>& vUsers, const string& username, const string& password, short& idx)
{
    for (size_t i = 0; i < vUsers.size(); ++i)
    {
        if ((stringToLower(vUsers[i].userName) == stringToLower(username)) &&
            vUsers[i].passWord == password)
        {
            idx = i;
            return true;
        }
    }

    return false;
}


stUser loginUser(const vector<stUser>& vUsers)
{
    short idx = 0;
    bool firstAttempt = true;
    while (true)
    {
        system("cls");
        printScreenHeader("Login");

        if (!firstAttempt)
        {
            cout << "\nInvalid Username OR Password! Try Again.\n\n";
        }

        string username = readString("Username:\n");
        string password = readString("Password:\n");
        if (isLoginValid(vUsers, username, password, idx))
        {
            return vUsers[idx];
        }
        else
            firstAttempt = false;
    }
}

#pragma endregion

#pragma region MainMenu

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

void bank()
{
    vector<stClient> vClients = loadClientsDataFromFile();
    vector<stUser> vUsers = loadUsersDataFromFile();

    stUser currentUser = loginUser(vUsers);

    short option = 0;
    do
    {
        printMainMenu();

        option = readOption(1, 8);

        switch (option)
        {
        case enShowAllClients:
            if (hasPermission(currentUser, permShowClients))
                printAllClientsData(vClients);
            else
                cout << "\nPermission Denied: Cannot view clients.\n";
            break;

        case enAddNewClient:
            if (hasPermission(currentUser, permAddClient))
                addNewClient(vClients);
            else
                cout << "\nPermission Denied: Cannot add new client.\n";
            break;

        case enDeleteClient:
            if (hasPermission(currentUser, permDeleteClient))
                deleteClient(vClients);
            else
                cout << "\nPermission Denied: Cannot delete client.\n";
            break;

        case enUpdateClient:
            if (hasPermission(currentUser, permUpdateClient))
                updateClient(vClients);
            else
                cout << "\nPermission Denied: Cannot update client.\n";
            break;

        case enFindClient:
            if (hasPermission(currentUser, permFindClient))
                findClient(vClients);
            else
                cout << "\nPermission Denied: Cannot find client.\n";
            break;

        case enTransactions:
            if (hasPermission(currentUser, permTransactions))
                transactions(vClients);
            else
                cout << "\nPermission Denied: Cannot perform transactions.\n";
            break;

        case enManageUsers:
            if (hasPermission(currentUser, permManageUsers))
                manageUsers(vUsers);
            else
                cout << "\nPermission Denied: Cannot manage users.\n";
            break;

        case enLogout:
            // Save clients on logout
            saveClientsToFile(vClients);
            // Save users if any changes were made
            saveUsersToFile(vUsers);
            break;
        }

        if (option != enLogout && option != enManageUsers && option != enTransactions)
            goBackToMenu("Go Back to Main Menu");

    } while (option != enLogout);
}

#pragma endregion

int main()
{
    bank();
    cout << endl << endl;
    cout << "Thank you for using the Bank Management System!\n";
    cout << "Goodbye!\n";
    system("pause>0");
    return 0;
}