#include <iostream>
#include <string>
using namespace std;


enum enEncryption { enEncrypt = 1, enDecrypt = 2 };

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

string readString(string message = "Enter a string: ")
{
	string myString = "";
	cout << message;

	getline(cin, myString);

	return myString;
}

string encryptText(string text,short encryptionKey)
{
	for (char &c : text)
	{
		c = c + encryptionKey;
	}

	return text;
}

string decryptText(string text,short encryptionKey)
{
	for (char &c : text)
	{
		c = c - encryptionKey;
	}

	return text;
}

void encryption()
{
	string textToOperate = readString("Enter a string to encrypt/decrypt: ");
	short choice = readPositiveNumber("Enter 1 to Encrypt, or 2 to Decrypt: ");
	short encryptionKey = readPositiveNumber("Enter encryption key: ");

	switch (choice)
	{
	case enEncrypt:
		cout << "\nEncrpyted text: " << encryptText(textToOperate, encryptionKey) << endl;
		break;
	case enDecrypt:
		cout << "\nDecrpyted text: " << decryptText(textToOperate, encryptionKey) << endl;
		break;
	}

}

int main()
{
	encryption();
}