/*
Умова: Напишіть гру в консолі «Хрестики-Нолики».
В цій грі має бути заставка, головне меню.
Також має бути вибір, чи гравець проти гравця, чи комп’ютер проти гравця.
В першому варіанті кожний гравець задає своє ім’я.
Перший гравець вибирає, чим буде ходити (хрестиками чи ноликами).
Другий гравець отримає те, що залишиться. Гра вибирає рандомно, хто перший ходить.
Реалізуйте логіку гри на полі 3 на 3.
Можлива ніч’я, тому результат гри також має бути у вигляді «виграв цей чи цей», або «нічья».
У випадку гри з комп’ютером реалізуйте штучний інтелект. Має бути 3 рівня складності:
Легкий: комп’ютер просто рандомно вибирає пусту клітинку;
Середній: комп’ютер аналізує, чи гравець зараз може виграти (стоїть два знаки і може бути третій в ряд/діагональ/стовпчик).
Якщо так – то ставить блок. Інакше вибирає рандомно.
Важкий: в комп’ютера виграти не можна, якщо ви ходите перші.
Якщо ходить він, то він грає лише по встановленій схемі, із якої ви можете вибратись максимум в нічью.
Врахувати всі можливі помилки зі сторони користувача (введе на ворожу клітинку чи на свою, введете за границі поля і т.д.).
Ви уже довго пишете функції і приблизно маєте уже розуміти, що якщо є алгоритм для виконання якоїсь дії, який складається з декількох рядків коду – то це має бути функція.
Прототипи функцій зберігайте в заголовковому файлі, їх реалізацію в .cpp файлі, а головний код (який викликає це все) в файлі main.cpp.
*/

#include <iostream>
#include <ctime>

using namespace std;

char playingField[9];

char ChoiceOfFigure(char* nameFirstPlayer);

void KeysToMove();

int GetMove(char* nameFirstPlayer, char* nameSecondPlayer, int turn);

void PlayingField();

void clearPlayingField();

bool WinsCombination(char chooseGoFirstPlayer);

char DeterminingTheWinner(char* nameFirstPlayer, char chooseGoFirstPlayer, char* nameSecondPlayer, char chooseGoSecondPlayer, int randTurn);

char DeterminingTheWinnerEasyLevel(char* namePlayer, char chooseGoPlayer, char* computer, char chooseGoComputer, int turn);

void Statistics(char winner, char* nameFirstPlayer, char* nameSecondPlayer);

void PlayerVsPlayer();

void ComputerVsPlayer();

void EasyLevel();

void MediumLevel();

void HardLevel();

int main()
{
	srand(unsigned(time(nullptr)));

	cout << "\n ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
	cout << " ~ Main menu                               ~\n";
	cout << " ~ Make the choice how you want to play:   ~\n";
	cout << " ~  1 - Player against player              ~\n";
	cout << " ~  2 - Computer against player            ~\n";
	cout << " ~  0 - Exit.                              ~\n";
	cout << " ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";

	int choiceInMenu;
	cout << "\nYour chice (enter only a number, for example: 1): ";
	cin >> choiceInMenu;

	do
	{
		if (choiceInMenu == 1 || choiceInMenu == 2 || choiceInMenu == 0)
			break;
		else
		{
			cout << "\nYou entered an invalid number, please try again.\n";
			cin >> choiceInMenu;
		}
	} while (choiceInMenu != 1 || choiceInMenu != 2 || choiceInMenu != 0);

	do
	{
		switch (choiceInMenu)
		{
		case 1:
			PlayerVsPlayer();
			break;
		case 2:
			ComputerVsPlayer();
			break;
		case 0:
			cout << "Goodbay!!!\n";
			break;
		default:
			cout << "Error, select an item from the menu\n";
			break;
		}
	} while (choiceInMenu != 0);
	return 0;
}

char ChoiceOfFigure(char* nameFirstPlayer)
{
	char figure;

	do
	{
		cout << "\nPlayer " << nameFirstPlayer << " choose what you want to go:\n  X - cross;\n  O - zero.\n";
		cout << "Your choice: ";
		cin >> figure;
		if (figure == 'X')
			return figure;
		else if (figure == 'O')
			return figure;
		else
			cout << "\nYou entered an invalid character, please try again.\n";
	} while (figure != 'X' || figure != 'O');
}

void KeysToMove()
{
	cout << "\n\tThe numbers used for the game.\n";
	cout << "\t-------------\n";
	cout << "\t| 7 | 8 | 9 |\n";
	cout << "\t-------------\n";
	cout << "\t| 4 | 5 | 6 |\n";
	cout << "\t-------------\n";
	cout << "\t| 1 | 2 | 3 |\n";
	cout << "\t-------------\n";
}

int GetMove(char* nameFirstPlayer, char* nameSecondPlayer, int turn)
{
	int move;
	if (turn % 2 == 0)
		cout << nameFirstPlayer << " enter a number to place your character: ";
	else
		cout << nameSecondPlayer << " enter a number to place your character: ";

	cin >> move;


	while (move > 9 || move < 1 || playingField[move - 1] != '-')
	{
		if (playingField[move - 1] != '-')
			cout << "There is already a symbol in this place.\n";
		else
			cout << "You have entered an incorrect number.\n";
		cout << "Please see what numbers you can use for the game and re-enter: ";
		cin >> move;
	}
	return move;
}

void PlayingField()
{
	cout << "\n\n\tPlaying field:\n";
	cout << "\t-------------" << endl;
	cout << "\t| " << playingField[6] << " | " << playingField[7] << " | " << playingField[8] << " |\n";
	cout << "\t-------------" << endl;
	cout << "\t| " << playingField[3] << " | " << playingField[4] << " | " << playingField[5] << " |\n";
	cout << "\t-------------" << endl;
	cout << "\t| " << playingField[0] << " | " << playingField[1] << " | " << playingField[2] << " |\n";
	cout << "\t-------------" << endl;
}

void clearPlayingField()
{
	for (int i = 0; i < 9; i++)
		playingField[i] = '-';

}

bool WinsCombination(char winPlayer)
{
	int winningСombinations[][3] = { {0,1,2},{3,4,5,}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6} };

	for (int i = 0; i < 8; i++)
	{
		int count = 0;
		for (int j = 0; j < 3; j++)
		{
			if (playingField[winningСombinations[i][j]] == winPlayer)
				count++;
		}
		if (count == 3)
			return true;
	}
	return false;
}

char DeterminingTheWinner(char* nameFirstPlayer, char chooseGoFirstPlayer, char* nameSecondPlayer, char chooseGoSecondPlayer, int turn)
{
	KeysToMove();
	do
	{
		int move = GetMove(nameFirstPlayer, nameSecondPlayer, turn);
		cout << "\nYour entered: " << move << endl;
		if (turn % 2 == 0)
		{
			playingField[move - 1] = chooseGoFirstPlayer;
			if (WinsCombination(chooseGoFirstPlayer))
			{
				cout << "Congratulations to the player -" << nameFirstPlayer << "- on winning.\n";
				return chooseGoFirstPlayer;
			}
		}
		else
		{
			playingField[move - 1] = chooseGoSecondPlayer;
			if (WinsCombination(chooseGoFirstPlayer))
			{
				cout << "Congratulations to the player -" << nameSecondPlayer << "- on winning.\n";
				return chooseGoSecondPlayer;
			}
		}
		turn++;
		PlayingField();

		if (turn == 10)
		{
			cout << "\nIt's a Draw.";
			return 'D';
		}
	} while (!WinsCombination(chooseGoFirstPlayer) && !WinsCombination(chooseGoSecondPlayer));
}

char DeterminingTheWinnerEasyLevel(char* namePlayer, char chooseGoPlayer, char* computer, char chooseGoComputer, int turn)
{
	KeysToMove();
	do
	{
		int move;
		if (turn % 2 == 0)
		{
			cout << namePlayer << " enter a number to place your character: ";
			cin >> move;
		}
		else
		{
			move = rand() % 9;
			cout << move;
			cout << computer << " entered a number: " << move << endl;
		}

		while (move > 9 || move < 1 || playingField[move - 1] != '-')
		{
			if (playingField[move - 1] != '-')
				cout << "There is already a symbol in this place.\n";
			else
				cout << "You have entered an incorrect number.\n";
			cout << "Please see what numbers you can use for the game and re-enter: ";

			if (turn % 2 == 0)
			{
				cout << namePlayer << " enter a number to place your character: ";
			}
			else
			{
				cout << computer << " enter a number to place your character: ";
				move = rand() % 10;
				cout << move << endl;
			}
		}


		cout << "\nYour entered: " << move << endl;
		if (turn % 2 == 0)
		{
			playingField[move - 1] = chooseGoPlayer;
			if (WinsCombination(chooseGoPlayer))
			{
				cout << "Congratulations to the player -" << namePlayer << "- on winning.\n";
				return chooseGoPlayer;
			}
		}
		else
		{
			playingField[move - 1] = chooseGoComputer;
			if (WinsCombination(chooseGoPlayer))
			{
				cout << "Congratulations to the player -" << computer << "- on winning.\n";
				return chooseGoComputer;
			}
		}
		turn++;
		PlayingField();

		if (turn == 10)
		{
			cout << "\nIt's a Draw.";
			return 'D';
		}
	} while (!WinsCombination(chooseGoPlayer) && !WinsCombination(chooseGoComputer));
}

void Statistics(char winner, char* nameFirstPlayer, char* nameSecondPlayer)
{
	int xWins = 0, oWins = 0, draws = 0;
	switch (winner)
	{
	case 'X':
		xWins++;
		break;
	case 'O':
		oWins++;
		break;
	case 'D':
		draws++;
		break;
	default:
		break;
	}

	cout << "Players " << nameFirstPlayer << " wins: " << xWins << "; Players " << nameSecondPlayer << " wins: " << oWins << "; Draws: " << draws << ";\n";
}

void PlayerVsPlayer()
{
	cout << "\nPlayer against player\n";

	char nameFirstPlayer[20];
	cout << "\nEnter the name of the first player\n";
	cin >> nameFirstPlayer;

	char nameSecondPlayer[20];
	cout << "\nEnter the name of the second player\n";
	cin >> nameSecondPlayer;

	cout << "\nName first player  - " << nameFirstPlayer << endl;
	cout << "Name second player - " << nameSecondPlayer << endl;

	char chooseGoFirstPlayer, chooseGoSecondPlayer;

	chooseGoFirstPlayer = ChoiceOfFigure(nameFirstPlayer);
	if (chooseGoFirstPlayer == 'X')
		chooseGoSecondPlayer = 'O';
	else if (chooseGoFirstPlayer == 'O')
		chooseGoSecondPlayer = 'X';

	cout << "\nThe player " << nameFirstPlayer << " has chosen " << chooseGoFirstPlayer << endl;
	cout << "The player " << nameSecondPlayer << " will walk " << chooseGoSecondPlayer << endl;

	cout << "\nNow Rand will choose who will go first.\n";

	int randTurn;

	randTurn = rand() % 2;
	cout << randTurn << endl;
	if (randTurn == 0)
		cout << "The player " << nameFirstPlayer << " walks first.\n";
	else if (randTurn == 1)
		cout << "The player " << nameSecondPlayer << " walks first.\n";

	char playAgain = 'y';
	while (playAgain == 'y')
	{
		clearPlayingField();
		char winner = DeterminingTheWinner(nameFirstPlayer, chooseGoFirstPlayer, nameSecondPlayer, chooseGoSecondPlayer, randTurn);

		cout << "The final field of the game:\n";
		PlayingField();

		Statistics(winner, nameFirstPlayer, nameSecondPlayer);

		cout << "\nWant to play playAgain? (yes - y, no - n): ";
		cin >> playAgain;
		while (playAgain != 'y' && playAgain != 'n')
		{
			cout << "\nYou hove entered an incorrect character. Please try playAgain: ";
			cin >> playAgain;
		}
	}
}

void ComputerVsPlayer()
{
	cout << "\nComputer against player\n";

	cout << "\n ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";
	cout << " ~ Select the level of complexity of the computer: ~\n";
	cout << " ~  1 - Easy level.                                ~\n";
	cout << " ~  2 - Medium level.                              ~\n";
	cout << " ~  3 - Hard level.                                ~\n";
	cout << " ~  0 - Exit to the main menu.                     ~\n";
	cout << " ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n";

	int choiceDifficultyLevel;
	cout << "\nYour chice: ";
	cin >> choiceDifficultyLevel;
	do
	{
		switch (choiceDifficultyLevel)
		{
		case 1:
			EasyLevel();
			break;
		case 2:
			MediumLevel();
			break;
		case 3:
			HardLevel();
			break;
		case 0:
			break;
		default:
			cout << "Error, select an item from the submenu.\n";
			break;
		}
	} while (choiceDifficultyLevel != 0);
}

void EasyLevel()
{
	cout << "\nEasy level.\n";
	char namePlayer[20], computer[20] = { "Computer" };
	cout << "\nEnter your name: ";
	cin >> namePlayer;

	char chooseGoPlayer, chooseGoComputer;

	chooseGoPlayer = ChoiceOfFigure(namePlayer);
	if (chooseGoPlayer == 'X')
		chooseGoComputer = 'O';
	else if (chooseGoPlayer == 'O')
		chooseGoComputer = 'X';

	cout << "\nThe player " << namePlayer << " has chosen " << chooseGoPlayer << endl;
	cout << "Computer  will walk " << chooseGoComputer << endl;

	cout << "\nNow Rand will choose who will go first.\n";

	int randTurn;

	randTurn = rand() % 2;
	cout << randTurn << endl;
	if (randTurn == 0)
		cout << "The player " << namePlayer << " walks first.\n";
	else if (randTurn == 1)
		cout << "The player " << computer << " walks first.\n";

	int xWins = 0, oWins = 0, draws = 0;

	char playAgain = 'y';
	while (playAgain == 'y')
	{
		clearPlayingField();
		char winner = DeterminingTheWinnerEasyLevel(namePlayer, chooseGoPlayer, computer, chooseGoComputer, randTurn);

		cout << "The final field of the game:\n";
		PlayingField();

		switch (winner)
		{
		case 'X':
			xWins++;
			break;
		case 'O':
			oWins++;
			break;
		case 'D':
			draws++;
			break;
		default:
			break;
		}

		cout << "Players " << chooseGoPlayer << " wins: " << xWins << "; Players " << chooseGoComputer << " wins: " << oWins << "; Draws: " << draws << ";\n";

		cout << "\nWant to play playAgain? (yes - y, no - n): ";
		cin >> playAgain;
		while (playAgain != 'y' && playAgain != 'n')
		{
			cout << "\nYou hove entered an incorrect character. Please try playAgain: ";
			cin >> playAgain;
		}
	}
}

void MediumLevel()
{

}

void HardLevel()
{

}
