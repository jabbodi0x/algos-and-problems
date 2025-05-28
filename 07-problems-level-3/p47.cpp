#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

struct stClient
{
    string accountNumber, name, phone, pinCode;
    float balance;
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
    cin >> client.balance;

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

void addRecordLineToFile(string recordLine, string fileName = "clients.txt")
{
    fstream myFile;
    myFile.open(fileName, ios::out | ios::app);

    if (myFile.is_open())
    {
        myFile << recordLine << endl;
    }
    myFile.close();
}

void addNewClient()
{
    stClient client = readClientData();
    addRecordLineToFile(convertClientRecordToData(client));
}

void addClientsToFile(string fileName="clients.txt")
{
    char answer = 'y';

    do 
    {
        system("cls");
        
        addNewClient();
        
        cout << "\n\nClient Added Successfully, Do you want to add more: [y/n]: ";
        cin >> answer;
    } while (tolower(answer) == 'y');
}

int main()
{
    
    addClientsToFile();
    


    cout << endl;
    system("pause>0");

    return 0;
}