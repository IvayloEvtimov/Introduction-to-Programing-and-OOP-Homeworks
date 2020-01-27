#include <iostream>
#include <fstream>

#include "Transformation.h"
#include "Helper.h"
#include "Constants.h"


void start(int argc,char* argv[])
{
	char path[MAX];
	do
	{
		std::cout << "Enter the path to file\n";
		std::cin.getline(path, 1024, '\n');
		

	} while (checkFilePath(path) == 0);

	//if (checkFilePath(argv[1]) == 0)
	//{
	//	std::cout << "Wrong file path entered.\n";
	//	return;
	//}

	Transformation TF(path);

	//Transformation TF(argv[1]);

	char command[MAX],
		lineContent[MAX],
		choice = 0;

	int line = 0,
		from = 0,
		to = 0;

	bool valid = true,
		exit = false;

	char ch;
	int count = 0;

	while (!exit)
	{
		std::cout << "Enter command: \n";
		std::cin >> command;
		std::cin.getline(command, MAX, ' ');
		for (count = 0; command[count - 1] != ' ' && command[count - 1] != '\n' && command[count-1]!=0; count++)
		{
			std::cin.get(command[count]);
		}
		ch = command[count - 1];
		command[count - 1] = 0;
		findCommand(command, choice, line, from, to, lineContent, valid);
		if (valid)
		{
			switch (choice)
			{
			case 'h':
				TF.makeHeading(line);
				break;
			case 'i':
				TF.makeItalic(line, from, to);
				break;
			case 'b':
				TF.makeBold(line, from, to);
				break;
			case 'c':
				TF.makeCombine(line, from, to);
				break;
			case 'a':
				TF.addLine(lineContent);
				break;
			case 'r':
				TF.removeLine(line);
				break;
			case 'e':
				TF.exit();
				exit = true;
				break;
			}
		}
		else
			std::cout << "Invalid command entered\n";

		valid = true;
		if (choice != 'a' && choice!='e')
				std::cin.ignore(MAX, '\n');
			//else
			//	std::cin.ignore(MAX, ' ');
	}
}


int main(int argc,char* argv[])
{
	start(argc,argv);

//	system("pause");
	return 0;
}

