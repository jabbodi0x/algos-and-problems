#include <iostream>

using namespace std;

void printHeaderOfTable(int from, int to)
{
	cout << "\n\t\t\tMultiplication Table: From " << from << " to " << to << "\n\n";

	cout << "\t";

	for (int i = 1; i <= 10; i++)
	{
		cout << i << "\t";
	}
	cout << "\n-------------------------------------------------------------------------------------\n";
}

string ColumnSeperator(int i)
{
	if (i < 10)
		return "   |";
	else
		return "  |";
}

void printMultiplicationTableFrom1To10(int from, int to)
{
	printHeaderOfTable(from,to);
	
	for (int i = from; i <= to; i++)
	{
		cout << i << ColumnSeperator(i) << "\t";

		for (int j = 1; j <= 10; j++)
		{
			cout << i * j << "\t";
		}
		cout << endl;
	}
	cout << "-------------------------------------------------------------------------------------\n";
}

int main()
{
	printMultiplicationTableFrom1To10(5,15);
	return 0;
}