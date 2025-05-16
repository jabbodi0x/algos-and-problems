#include <iostream>

using namespace std;



int getRandomNumber(int fromNumber, int toNumber)
{
	return (rand() % (toNumber - fromNumber + 1) + fromNumber);
}



int main()
{
	srand((unsigned)time(NULL));

	cout << getRandomNumber(1, 5000);

}