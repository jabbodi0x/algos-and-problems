#include <iostream>
#include <string>

using namespace std;

enum enResult
{
	player=1,
	computer=2,
	draw=3
};

enum enChoice
{
	rock=1,
	paper=2,
	scissors=3
};

struct stGameResult
{
	int roundNumber;
	enChoice playerChoice;
	enChoice computerChoice;
	enResult result;
};

string RESULTS[] = {"","Player","Computer","Draw"};
string CHOICES[] = { "", "Rock", "Paper","Scissors" };

short getRandomNumber(short fromNumber, short toNumber)
{
	return (rand() % (toNumber - fromNumber + 1) + fromNumber);
}

short readRounds()
{
	short rounds = 0;
	do
	{
		cout << "Enter the amount of rounds (1-10) : ";
		cin >> rounds;
	} while (rounds < 0 || rounds > 10);

	return rounds;
}

bool readPlayAgain()
{
    char answer = 'y';
    do
    {
        cout << "Do you want to play again? Y/N: ";
        cin >> answer;
        answer = tolower(answer);
    } while (answer != 'y' && answer != 'n');

    return (answer == 'y');
}

enChoice generateComputerChoice()
{
	return (enChoice)getRandomNumber(1, 3);
}

enChoice getUserChoice()
{
	short userChoice = 0;

	do
	{
		cout << "\nEnter your choice: [1]:Rock  [2]:Paper  [3]:Scissors:\t";
		cin >> userChoice;
	} while (userChoice <1 || userChoice > 3);

	return (enChoice)userChoice;
}

enResult getResultOfRound(enChoice userChoice, enChoice computerChoice)
{
	if (userChoice == computerChoice) return enResult::draw;
	if ((userChoice == enChoice::rock && computerChoice == enChoice::scissors) || (userChoice == enChoice::paper && computerChoice == enChoice::rock)) return enResult::player;
	if ((userChoice == enChoice::rock && computerChoice == enChoice::paper) || (userChoice == enChoice::paper && computerChoice == enChoice::scissors)) return enResult::computer;
}

void printRoundResults(const stGameResult& result)
{
	cout << "\n--------------------------------------------";
	cout << "\n\t Round (" << result.roundNumber << ")";
	cout << "\n--------------------------------------------";
	cout << "\nPlayer Choice   : " << CHOICES[result.playerChoice];
	cout << "\nComputer Choice : " << CHOICES[result.computerChoice];
	cout << "\nRound Winner    : " << RESULTS[result.result];
	cout << "\n--------------------------------------------\n";
}



short calculateWins(stGameResult results[10], short rounds, enResult who)
{
	short count = 0;
	for (short i = 0; i < rounds; i++)
	{
		count += (results[i].result == who) ? 1 : 0;
	}
	return count;
}


string getFinalWinner(short playerWins, short computerWins)
{
	return ((playerWins == computerWins) ? "No Winner" : (playerWins > computerWins) ? "Player" : "Computer");
}

void printGameResults(stGameResult results[10], short rounds)
{
	cout << "\n\n============================================";
	cout << "\n\t\t*** GAME OVER ***";
	cout << "\n============================================";

	cout << "\n\t\t[ Final Results ]\n";

	short playerWins = calculateWins(results, rounds, enResult::player);
	short computerWins = calculateWins(results, rounds, enResult::computer);
	short draws = calculateWins(results, rounds, enResult::draw);

	string finalWinner = getFinalWinner(playerWins, computerWins);

	cout << "Player Wins     : " << playerWins << "\n";
	cout << "Computer Wins   : " << computerWins << "\n";
	cout << "Draws           : " << draws << "\n";

	cout << "--------------------------------------------";
	cout << "\nFinal Winner    : " << finalWinner;
	cout << "\n============================================\n";
}



stGameResult playRound(short roundNumber)
{
	stGameResult result;
	result.roundNumber = roundNumber;
	result.playerChoice = getUserChoice();
	result.computerChoice = generateComputerChoice();
	result.result = getResultOfRound(result.playerChoice, result.computerChoice);
	return result;
}


void playGame()
{
	bool playAgain = true;
	stGameResult results[10];

	do
	{
		system("cls");
		cout << "\n============================================";
		cout << "\n\t Welcome to Rock, Paper, Scissors!";
		cout << "\n============================================\n";

		short rounds = readRounds();

		cout << "\n\n============================================";
		cout << "\n\t Starting Game: " << rounds << " Round(s)";
		cout << "\n============================================\n";

		for (short i = 0; i < rounds; i++)
		{
			results[i] = playRound(i + 1);
			printRoundResults(results[i]);
		}

		printGameResults(results, rounds);
		playAgain = readPlayAgain();

		if (playAgain)
		{
			cout << "\n\n============================================";
			cout << "\n\t Restarting Game...";
			cout << "\n============================================\n";
		}

	} while (playAgain);

	cout << "\n\n============================================";
	cout << "\n\t Thank you for playing!";
	cout << "\n============================================\n";
}



int main()
{
	srand((unsigned)time(NULL));
	playGame();
 	return 0;
}