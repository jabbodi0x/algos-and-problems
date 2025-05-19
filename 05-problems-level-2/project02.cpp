#include <iostream>
#include <string>

using namespace std;

enum enQuestionLevel
{
	easy = 1,
	medium = 2,
	hard = 3,
	mixLevel = 4
};

enum enOperationType
{
	addition = 1,
	subtraction = 2,
	multiplication = 3,
	division = 4,
	mixOperation = 5
};

struct stQuestion {
	short num1;
	short num2;
	float correctAnswer;
	float userAnswer;
	enOperationType operation;
	enQuestionLevel difficulty;
	bool isCorrect;
};

int getRandomNumber(int fromNumber, int toNumber)
{
	return (rand() % (toNumber - fromNumber + 1) + fromNumber);
}

short readQuestionsAmount()
{

	short questions = 0;
	do
	{
		cout << "Enter the number of questions you want to answer: ";
		cin >> questions;
	} while (questions < 0);

	return questions;
}

enQuestionLevel readQuestionLevel()
{
	short questionLevel = 0;

	do
	{
		cout << "Enter questions level: [1] Easy   [2] Medium   [3] Hard   [4] Mix:  ";
		cin >> questionLevel;
	} while (questionLevel < 1 || questionLevel > 4);

	return (enQuestionLevel)questionLevel;
}

enOperationType readOperationType()
{
	short operationType = 0;

	do
	{
		cout << "Enter Operation Type: [1] Addition   [2] Subtraction   [3] Multiplication   [4] Division   [5] Mix:  ";
		cin >> operationType;
	} while (operationType < 1 || operationType > 5);

	return (enOperationType)operationType;
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

int generateNumberToOperate(const enQuestionLevel questionLevel)
{
	switch (questionLevel)
	{
	case enQuestionLevel::easy:
		return getRandomNumber(1, 9);
		break;
	case enQuestionLevel::medium:
		return getRandomNumber(10, 30);
		break;
	case enQuestionLevel::hard:
		return getRandomNumber(31, 99);
		break;
	case enQuestionLevel::mixLevel:
		return getRandomNumber(1, 99);
		break;
	}
}

float getAnswer(int number1, int number2, const enOperationType& operationType)
{
	switch (operationType)
	{
	case enOperationType::addition:
		return number1 + number2;
		break;
	case enOperationType::subtraction:
		return number1 - number2;
		break;
	case enOperationType::multiplication:
		return number1 * number2;
		break;
	case enOperationType::division:
		return (float)number1 / number2;
		break;
	case enOperationType::mixOperation:
		return getAnswer(number1,number2,(enOperationType)getRandomNumber(1, 4));
	}
}

float readUserAnswer()
{
	float answer = 0;

	return answer;

}

string getOperationString(const enOperationType& operationType)
{
	switch (operationType)
	{
	case enOperationType::addition:
		return "Addition";
	case enOperationType::subtraction:
		return "Subtraction";
	case enOperationType::multiplication:
		return "Multiplication";
	case enOperationType::division:
		return "Division";
	case enOperationType::mixOperation:
		return "Mix";
	default:
		return "Unknown";
	}
}

char getOperationSymbol(const enOperationType& operationType)
{
	switch (operationType)
	{
	case enOperationType::addition:
		return '+';
	case enOperationType::subtraction:
		return '-';
	case enOperationType::multiplication:
		return '*';
	case enOperationType::division:
		return '/';
	case enOperationType::mixOperation:
		return '?';
	default:
		return '?';
	}
}

string getDifficultyString(const enQuestionLevel questionLevel)
{
	switch (questionLevel)
	{
	case enQuestionLevel::easy:
		return "Easy";
	case enQuestionLevel::medium:
		return "Medium";
	case enQuestionLevel::hard:
		return "Hard";
	case enQuestionLevel::mixLevel:
		return "Mix";
	}
}

enQuestionLevel getRandomQuestionLevel()
{
	return (enQuestionLevel)getRandomNumber(1, 3);
}

enOperationType getRandomOperationType()
{
	return (enOperationType)getRandomNumber(1, 4);
}

void checkAnswer(stQuestion& q)
{
	cin >> q.userAnswer;

	if (q.userAnswer == q.correctAnswer)
	{
		cout << "Right Answer!\n";
		system("color 2F");
		q.isCorrect = true;
	}
	else
	{
		cout << "Wrong Answer! Correct is: " << q.correctAnswer << "\n";
		system("color 4F");
		q.isCorrect = false;
	}
	cout << "===========================\n";
}

void printQuestion(const stQuestion& q, int current, int total)
{
	cout << "\n\n===========================\n";
	cout << "Question [" << current << "/" << total << "]\n";
	cout << q.num1 << endl << q.num2 << " " << getOperationSymbol(q.operation);
	cout <<endl << "-------\n";
}

stQuestion generateQuestion(enQuestionLevel selectedLevel, enOperationType selectedOp)
{
	stQuestion q;

	q.difficulty = (selectedLevel == mixLevel) ? getRandomQuestionLevel() : selectedLevel;
	q.operation = (selectedOp == mixOperation) ? getRandomOperationType() : selectedOp;

	q.num1 = generateNumberToOperate(q.difficulty);
	q.num2 = generateNumberToOperate(q.difficulty);
	q.correctAnswer = getAnswer(q.num1, q.num2, q.operation);

	return q;
}

void changeScreenColorBasedOnRightAnswers(int right, int wrong)
{
	if (right > wrong)
		system("color 2F");
	else if (wrong > right)
		system("color 4F");
	else
		system("color 6F");
}

void printFinalResults(int right, int wrong, enQuestionLevel level, enOperationType op)
{
	cout << "\n\n\n=========== Final Results ===========";
	cout << "\nTotal Questions: " << right + wrong << "\n";
	cout << "\nCorrect Answers: " << right << "\n";
	cout << "\nWrong Answers  : " << wrong << "\n";
	cout << "\n=====================================";

	cout << "\nDifficulty     : " << getDifficultyString(level);
	cout << "\nOperation Type : " << getOperationString(op);
	cout << "\n=====================================\n\n\n";
}

void playQuizGame()
{
	do
	{
		system("color 0F");
		system("cls");

		short totalQuestions = readQuestionsAmount();
		enQuestionLevel level = readQuestionLevel();
		enOperationType op = readOperationType();

		stQuestion questions[100];
		short correctCount = 0, wrongCount = 0;

		for (short i = 0; i < totalQuestions; ++i)
		{
			questions[i] = generateQuestion(level, op);
			printQuestion(questions[i], i + 1, totalQuestions);
			checkAnswer(questions[i]);

			if (questions[i].isCorrect)
				correctCount++;
			else
				wrongCount++;
		}

		printFinalResults(correctCount, wrongCount,level,op);

	} while (readPlayAgain());
}



int main()
{
	srand((unsigned)time(NULL));

	playQuizGame();

	return 0;
}