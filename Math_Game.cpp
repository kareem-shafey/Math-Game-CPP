#include <iostream>
#include <string>
#include<cstdlib>
using namespace std;

enum enLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enType { Add = 1, Sub = 2, Mul = 3, Div = 4, MIX = 5 };
enum enPassOrFail { Pass = 1, Fail = 2 };

struct stQizz
{
	short GameRounds = 0;
	string Level;
	string OpType;
	short Right = 0;
	short Wrong = 0;
};

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

short HowManyQuestions()
{
	short Number = 0;
	cout << "How Many Questions do you want to answer? ";
	cin >> Number;
	return Number;
}

enLevel GameLevel()
{
	int Number = 0;
	do
	{
		cout << "Enter Questions Level [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix? ";
		cin >> Number;
	} while (Number < 1 || Number > 4);

	return (enLevel)Number;
}

enType OperationType()
{
	int Number = 0;
	do
	{
		cout << "Enter Operation Type [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix? ";
		cin >> Number;
	} while (Number < 1 || Number > 5);

	return (enType)Number;
}

char DetermineType(enType Type)
{
	if (Type == enType::Add)
		return '+';
	else if (Type == enType::Sub)
		return '-';
	else if (Type == enType::Mul)
		return '*';
	else if (Type == enType::Div)
		return '/';
}

string GameLevel(enLevel Level)
{
	string arrGameLevel[] = { "Easy", "Med", "Hard", "Mix" };
	return arrGameLevel[Level - 1];
}

short DetermineThelevel(enLevel Level)
{
	if (Level == enLevel::Easy)
		return RandomNumber(1, 10);
	else if (Level == enLevel::Med)
		return RandomNumber(11, 50);
	else if (Level == enLevel::Hard)
		return RandomNumber(51, 100);
	else if (Level == enLevel::Mix)
		return RandomNumber(1, 100);

}

string GameOpType(enType Type)
{
	string OpType[] = { "+", "-", "*", "/", "Mix" };
	return OpType[Type - 1];
}

short SumNumbers(short Number1, short Number2, char Op)
{
	switch (Op)
	{
	case '+':
		return Number1 + Number2;
	case '-':
		return Number1 - Number2;
	case '*':
		return Number1 * Number2;
	case '/':
		return Number1 / Number2;
	}
}

stQizz FillGameResult(short HowManyQuestions, enLevel Level, enType Type, short Right, short Wrong)
{
	stQizz Qizz;
	Qizz.GameRounds = HowManyQuestions;
	Qizz.Level = GameLevel(Level);
	Qizz.OpType = GameOpType(Type);
	Qizz.Right = Right;
	Qizz.Wrong = Wrong;
	return Qizz;
}

short ReadQuestionAnswer()
{
	short Answer = 0;
	cin >> Answer;
	return Answer;
}


void SetColorOnScreen(stQizz Qizz)
{
	if (Qizz.Right > Qizz.Wrong)
		system("color 2F");
	else
		system("color 4F");
}

stQizz PlayGame(short HowManyQuestions)
{
	short RightAnswer = 0, WrongAnswer = 0, answer = 0;
	enLevel Level = GameLevel();
	enType Type = OperationType();
	char Op = DetermineType(Type);
	short Number1 = 0, Number2 = 0;

	for (short i = 1; i <= HowManyQuestions; i++)
	{
		if (Type == enType::MIX)
		{
			char Operation[] = { '+', '-', '*', '/' };
			Op = Operation[RandomNumber(0, 3)];
		}
		cout << "\nQuestion [" << i << "/" << HowManyQuestions << "]\n\n";
		Number1 = DetermineThelevel(Level);
		Number2 = DetermineThelevel(Level);

		cout << Number1 << "\n" << Number2 << " " << char(Op) << endl;
		cout << "------------\n";
		answer = ReadQuestionAnswer();

		short QuestionsAnswer = SumNumbers(Number1, Number2, Op);
		if (QuestionsAnswer == answer)
		{
			RightAnswer++;
			cout << "Right Answer :-)\n";
			system("color 2F");
		}
		else
		{
			WrongAnswer++;
			cout << "Wrong Answer :-(\n";
			cout << "The right answer is: " << QuestionsAnswer << endl;
			system("color 4F");
			cout << "\a";
		}
	}
	return FillGameResult(HowManyQuestions, Level, Type, RightAnswer, WrongAnswer);
}

enPassOrFail CheckPassOrFail(stQizz Qizz)
{
	if (Qizz.Right > Qizz.Wrong)
		return enPassOrFail::Pass;
	else
		return enPassOrFail::Fail;
}

void ShowPassOtFailOnScreen(stQizz Qizz)
{
	cout << "\n\n--------------------------------\n";
	cout << "  Final Result Is ";
	if (CheckPassOrFail(Qizz) == enPassOrFail::Pass)
		cout << "PASS  :-)";
	else
		cout << "FAIL  :-(";
	cout << "\n--------------------------------\n";
}

void ShowFinalGameResult(stQizz Qizz)
{
	cout << "Number Of Questions   : " << Qizz.GameRounds << endl;
	cout << "Questions Level       : " << Qizz.Level << endl;
	cout << "OpType                : " << Qizz.OpType << endl;
	cout << "Number Of Right Answer: " << Qizz.Right << endl;
	cout << "Number Of Wrong Answer: " << Qizz.Wrong << endl;
	cout << "--------------------------------\n";
	SetColorOnScreen(Qizz);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char ReadMore = 'Y';
	do
	{
		ResetScreen();
		stQizz Qizz = PlayGame(HowManyQuestions());

		ShowPassOtFailOnScreen(Qizz);
		ShowFinalGameResult(Qizz);

		cout << "Do you want play again [Y/N]? ";
		cin >> ReadMore;
	} while (ReadMore == 'y' || ReadMore == 'Y');
}

int main()
{
	//Seeds the random number generator in C++, called only once

	srand((unsigned)time(NULL));

	StartGame();

	system("pause >0");
}