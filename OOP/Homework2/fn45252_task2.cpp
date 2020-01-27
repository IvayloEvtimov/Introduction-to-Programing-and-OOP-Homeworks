///////////////////////////
//Author: Ivaylo Evtimov
//FN: 45252
//Group: 5
//Task: 2
////////////////////////////


#include <iostream>
#include <fstream>

#include "Transformation.h"
#include "Helper.h"
#include "Constants.h"


void start(int argc,char* argv[])
{

	if (checkFilePath(argv[1]) == 0)  
	{
		std::cout << "Wrong file path entered.\n";
		return;
	}

 	Transformation TF(argv[1]);  //Initializes an object with the inputed path from command line argument

	char command[MAX], 
		lineContent[MAX],
		choice = 0;

	int line = 0,
		from = 0,
		to = 0;

	bool valid = true, //Used for validating commmand
		exit = false; //Used if exit commanad is entered

	int count = 0;

	while (!exit)
	{
		std::cout << "Enter command: \n";
		for (count = 0; command[count - 1] != ' ' && command[count - 1] != '\n' && command[count - 1] != 0; count++)
		{
			std::cin.get(command[count]);  //Puts chars in commnad array
			//until whitespace or end of line or terminating char is met
		}
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
				std::cout << "Exiting....\n";
				exit = true;
				break;
			}
		}
		else
			std::cout << "Invalid command entered\n";

		if (choice != 'a' && choice != 'e')
			std::cin.ignore(MAX, '\n');

		if (valid != true)
		{
			std::cin.clear(MAX);
			std::cin.ignore(MAX, '\n');
		}
	
		valid = true;
	}
}


int main(int argc,char* argv[])
{
	start(argc,argv);

	return 0;
}

