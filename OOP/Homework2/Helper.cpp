#include "Helper.h"
#include "Constants.h"

#include <iostream>
#include <fstream>

bool checkFilePath(const char *path)
{
	bool correct = false;

	std::ifstream input(path);
	if (input.is_open())
		correct = true;

	input.close();
	return correct;
}

void findCommand(const char *str, char& choice, int& line, int& from, int& to, char* lineContent, bool& valid)
{
	int count = 0;

	bool checkHeading = true,
		checkItalic = true,
		checkBold = true,
		checkCombine = true,
		checkAdd = true,
		checkRemove = true,
		checkExit = true;

	char heading[] = { "makeHeading" },
		italic[] = { "makeItalic" },
		bold[] = { "makeBold" },
		combine[] = { "makeCombine" },
		add[] = { "addLine" },
		remove[] = { "remove" },
		exit[] = { "exit" };

	if (strlen(str) > 11 || strlen(str) < 4) //If the entered command length is less than the smallest valid command
	{
		valid = false;
		return;
	}

	while (str[count] != ' ' && str[count] != 0)
	{
		if (checkHeading && str[count] != heading[count])
			checkHeading = false;

		if (checkItalic && str[count] != italic[count])
			checkItalic = false;

		if (checkBold && str[count] != bold[count])
			checkBold = false;

		if (checkCombine && str[count] != combine[count])
			checkCombine = false;

		if (checkAdd && str[count] != add[count])
			checkAdd = false;

		if (checkRemove && str[count] != remove[count])
			checkRemove = false;

		if (checkExit && str[count] != exit[count])
			checkExit = false;

		if (!checkHeading && !checkItalic && !checkBold && !checkCombine && !checkAdd && !checkRemove && !checkExit)
			break;

		if (str[count] == 0) //If terminating char is met then the commnad isn't completely entered
		{
			valid = false;
			break;
		}

		count++;
	}

	if (!valid)
		return;

	if (checkItalic || checkBold || checkCombine)
	{
		std::cin >> line >> from >> to;  //Takes 3 int variables 

		if (!from || !to) //and if they are == 0 or are invalid input
			valid = false; 

		if (checkItalic)
			choice = 'i';
		else if (checkBold)
			choice = 'b';
		else if (checkCombine)
			choice = 'c';
	}

	if (checkHeading || checkRemove)
	{
		std::cin >> line;

		if (!line)
			valid = false;

		if (checkHeading)
			choice = 'h';
		else if (checkRemove)
			choice = 'r';
	}

	if (checkAdd)
	{
		std::cin.getline(lineContent, MAX, '\n'); 

		if (checkAdd)
			choice = 'a';
	}

	if (checkExit)
		choice = 'e';
}
