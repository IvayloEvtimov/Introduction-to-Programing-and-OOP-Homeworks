#include <iostream>

using namespace std;

const char * Words[] = { "apple", "orange", "month", "vehicle" };
const unsigned int WordsCount = 4;
const int N = 5;


int Throw(int X)
{
	return rand() % X;
}

int HeadTail() { return rand() % 2; }

int strlen(char* Words[])
{
	int count = 0;
	for (int i = 0; *Words[i] != 0; i++)
	{
		count++;
	}
	return count;
}

void FillEmptyWord(char* GuessWord,int count)
{
	for (int i = 0; i <= count; i++)
	{
		GuessWord[i] = '_';
		if (i == count)
		{
			GuessWord[i] = '\0';
		}
	}
}

bool CheckLetter(char* WordToGuess, char letter,int count,int &posCount)
{
	for (int i = 0; i < count; i++)
	{;
		if (letter == WordToGuess[i])
		{
			posCount = i;
			return true;
		}
	}
	return false;
}

void FillEmptyHistory(char* History)
{
	for (int i = 0; i < 26; i++)
	{
		History[i] = ' ';
	}
	History[26] = '\0';
}

bool CheckHistory(char* History, char letter)
{
	for (int i = 0; i < 26; i++)
	{
		if (letter == History[i])
		{
			return true;
		}
	}
	return false;
}

void Print(char* Word)
{
	for (int i = 0; Word[i] != '\0'; i++)
	{
		cout << Word[i] << " ";
	}
}

void NormalGame()
{
	int res = Throw(WordsCount);
	cout << res << endl;
	cout << strlen(Words[res]) << endl;
	cout << Words[res] << endl;
	int count = strlen(Words[res]),
		corretGuesses = 0,
		incorrectGuesses = 0;

	int posCount = 0;
	
	char *GuessWord = new char[strlen(Words[res]) + 1];
	char *WordToGuess = new char[count+1];
	char* History= new char [27];
	int historyCount = 0;
	char letter;

	if (GuessWord && History && WordToGuess)
	{
		FillEmptyWord(GuessWord, count);
		FillEmptyHistory(History);
		strcpy(WordToGuess, Words[res]);

		while (true)
		{
			cout << "[" << incorrectGuesses << "/" << N << "] ";
			Print(GuessWord);
			cout  << "  " << "History ";
			Print(History);


			if (incorrectGuesses == N)
			{
				cout << "Game Over" << endl;
				break;
			}
			else if (corretGuesses == count)
			{
				cout << "YOU WIN\n";
				break;
			}
			cout << "Choose a letter: ";
			cin >> letter;

			if ((letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122))
			{

				if (CheckHistory(History, letter) == 1)
				{
					cout << "You have already chosen that letter. \n";
				}
				else
				{
					if (CheckLetter(WordToGuess, letter, count,posCount) == 1)
					{
						cout << "OK\n";
						History[historyCount] = letter;
						GuessWord[posCount] = letter;
						corretGuesses++;
						historyCount++;
					}
					else
					{
						cout << "No such letter! \n";
						History[historyCount] = letter;
						incorrectGuesses++;
						historyCount++;
					}
				}

			}
		}
	}

	delete[] WordToGuess;
	delete[] GuessWord;
	delete[] History;
}


void ComputerOnly()
{
	int res = Throw(WordsCount);
	cout << res << endl;
	cout << strlen(Words[res]) << endl;
	cout << Words[res] << endl;
	int count = strlen(Words[res]),
		corretGuesses = 0,
		incorrectGuesses = 0;

	int posCount = 0;

	char *GuessWord = new char[strlen(Words[res]) + 1];
	char *WordToGuess = new char[count + 1];
	char* History = new char[27];
	int historyCount = 0;
	char letter;

	bool correctLetter = true;



	if (GuessWord && History && WordToGuess)
	{
		FillEmptyWord(GuessWord, count);
		FillEmptyHistory(History);
		strcpy(WordToGuess, Words[res]);

		while (true)
		{

			if (HeadTail() == 1)
			{
				correctLetter = true;
				letter = WordToGuess[rand() % count];
			}
			else
			{
				correctLetter = false;
				letter = 97 + rand() % 26;
			}


			if (CheckHistory(History, letter) == 1 && correctLetter == true)
			{
				letter = WordToGuess[rand() % count];
			}
			else if ((letter >= 65 && letter <= 90) || (letter >= 97 && letter <= 122))
			{
				cout << "[" << incorrectGuesses << "/" << N << "] ";
				Print(GuessWord);
				cout << "  " << "History ";
				Print(History);

				if (incorrectGuesses == N)
				{
					cout << "Game Over" << endl;
					break;
				}
				else if (corretGuesses == count)
				{
					cout << "YOU WIN\n";
					break;
				}


				cout << "Choose a letter: " << letter << endl;

				if (CheckHistory(History, letter) == 1 && correctLetter == false)
				{
					cout << "You have already chosen that letter. \n";
				}
				else if (CheckHistory(History, letter) == 0)
				{
					if (CheckLetter(WordToGuess, letter, count, posCount) == 1)
					{
						cout << "OK\n";
						History[historyCount] = letter;
						GuessWord[posCount] = letter;
						corretGuesses++;
						historyCount++;
					}
					else
					{
						cout << "No such letter! \n";
						History[historyCount] = letter;
						incorrectGuesses++;
						historyCount++;
					}
				}

			}

		}

		delete[] History;
		delete[] WordToGuess;
		delete[] GuessWord;
	}
}


int  main()
{
	char choice;

	cout << "Choose game mode: \n[N]ormal game \n[C]omputer only \n";
	cin >> choice;


	switch (choice)
	{
	case 'N':
		NormalGame();
		break;
	case 'C':
		ComputerOnly();
		break;
	}

	system("pause");
	return 0;
}