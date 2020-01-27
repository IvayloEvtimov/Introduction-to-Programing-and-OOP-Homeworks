#include <iostream>

#include "Helper.h"
#include "System.h"

void start()
{
	char action[MAX],
		content[MAX],
		choice = 0;

	char actor[MAX],
		commReciever[MAX],
		description[MAX];
	int num = 0;

	bool valid = false;
	bool exit = false;

	while (!valid)
	{
		try
		{
			inputAdmin(actor, num, valid);
			valid = true;
		}
		catch (const std::invalid_argument& ia)
		{
			std::cerr << ia.what() << std::endl;
		}
	}

	Admin admin(actor, num);
	System S1(admin);

	while (!exit)
	{
		std::cout << "Enter command: \n";
		try
		{
			inputFirst(actor, choice);

			if (choice == 'q')
				exit = true;
			else if (choice == 'f')
				S1.statistic();
			else
			{
				inputSecond(action);
				findCommand(action, choice, commReciever, content, description, num);
				switch (choice)
				{
				case'u': //Regular User
					S1.newUser(actor, commReciever, num, 'r');
					break;
				case 'm': //Moderator
					S1.newUser(actor, commReciever, num, 'm');
					break;
				case 'b': //Block
					S1.blockUser(actor, commReciever);
					break;
				case 'n': //Unblock
					S1.unblockUser(actor, commReciever);
					break;
				case 'r': //Remove User
					S1.removeUser(actor, commReciever);
					break;
				case 'i': //Image post
					S1.newPost(actor, content,nullptr,choice);
					break;
				case 'l': //Link Post
					S1.newPost(actor, content,description, choice);
					break;
				case 't': //Text Post
					S1.newPost(actor, content,nullptr ,choice);
					break;
				case 'p': //Remove Post
					S1.removePost(actor, num);
					break;
				case 'v': //View Post
					S1.viewPost(actor, num);
					break;
				case 'w': //View All Posts
					S1.viewAll(actor, commReciever);
					break;
				case 'c':
					S1.changeNickname(actor, commReciever);
					break;
				}
			}
			choice = 0;
		}
		catch (const std::invalid_argument &ia)
		{
			std::cerr << ia.what() << std::endl;
		}
		catch (const std::logic_error& le)
		{
			std::cerr << le.what() << std::endl;
		}
		catch (const std::bad_alloc& ba)
		{
			std::cerr << "Memory allocation failure" << std::endl;
		}
	}
}

void inputAdmin(char *actor, int &num, bool &valid)
{
	std::cout << "Enter system admin's name and age: ";

	int count = 0;
	for (count = 0; actor[count - 1] != ' ' && actor[count - 1] != '\n'&& actor[count-1]!='\t'; ++count)
		std::cin.get(actor[count]);

	if (actor[count - 1] == '\n')
		throw std::invalid_argument("Wrong input!");

	actor[count - 1] = 0;
	std::cin >> num;

	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(MAX, '\n');
		throw std::invalid_argument("Wrong input!");
	}
	std::cin.ignore(MAX, '\n');
}

void inputFirst(char *actor,char& choice)
{
	int countActor = 0;
	for (countActor = 0; actor[countActor - 1] != ' ' && actor[countActor - 1] != '\n' && actor[countActor - 1] != '\t'; ++countActor)
		std::cin.get(actor[countActor]);

	if (actor[countActor - 1] == '\n')
	{
		actor[countActor - 1] = 0;
		if (strcmp(actor, "quit")==0)
			choice = 'q';
		else if (strcmp(actor, "info")==0)
			choice = 'f';
		else
			throw std::invalid_argument("Wrong input!");
	}

	actor[countActor - 1] = 0;
}

void inputSecond(char *action)
{
	int countAction = 0;
	for (countAction = 0; action[countAction - 1] != ' ' && action[countAction - 1] != '\n' && action[countAction - 1] != '\t'; ++countAction)
		std::cin.get(action[countAction]);

	if (action[countAction - 1] == '\n')
		throw std::invalid_argument("Wrong input!");

	action[countAction] = 0;

	if (action[countAction - 1] == '\t')
		action[countAction - 1] = ' ';

	if (strcmp(action, "post ") == 0 )
		do
		{
			std::cin.get(action[countAction]);
			++countAction;
		} while (action[countAction - 1] != ' ' &&action[countAction - 1] != '\n'&&action[countAction - 1] != '\t');

	if (action[countAction - 1] == '\n')
		throw std::invalid_argument("Wrong input!");

	action[countAction - 1] = 0;
}


void findCommand(const char *str, char& choice, char* commReciever, char* content, char* description, int& num)
{
	bool found = false;

	if (strlen(str) > 14 || strlen(str) < 4)  //If the entered command length is less than the smallest valid command
	{
		std::cin.ignore(MAX, '\n');
		throw std::invalid_argument("Invalid commnad");
	}

	if (strcmp(str, "add_user") == 0)
	{
		choice = 'u';
		found = true;
	}

	if (strcmp(str, "add_moderator") == 0)
	{
		choice = 'm';
		found = true;
	}

	if (strcmp(str, "block") == 0)
	{
		choice = 'b';
		found = true;
	}

	if (strcmp(str, "unblock") == 0)
	{
		choice = 'n';
		found = true;
	}

	if (strcmp(str, "remove_user") == 0)
	{
		choice = 'r';
		found = true;
	}

	if (strcmp(str, "post [image]") == 0)
	{
		choice = 'i';
		found = true;
	}

	if (strcmp(str, "post [link]") == 0)
	{
		choice = 'l';
		found = true;
	}

	if (strcmp(str, "post [text]") == 0)
	{
		choice = 't';
		found = true;
	}

	if (strcmp(str, "remove_post") == 0)
	{
		choice = 'p';
		found = true;
	}

	if (strcmp(str, "view_post") == 0)
	{
		choice = 'v';
		found = true;
	}

	if (strcmp(str, "view_all_posts") == 0)
	{
		choice = 'w';
		found = true;
	}

	if (strcmp(str, "rename")==0)
	{
		choice = 'c';
		found = true;
	}

	if (!found) //If no valid command has been found
	{
		std::cin.ignore(MAX, '\n');
		throw std::invalid_argument("Invalid commnad");
	}

	char ch;

	if (choice == 'u' || choice == 'm') //add user OR add moderator
	{
		int count = 0;
		for (count = 0; commReciever[count - 1] != ' ' && commReciever[count - 1] != '\n' && commReciever[count-1]!='\t'; ++count)
			std::cin.get(commReciever[count]);

		if (commReciever[count - 1] == '\n') //If last char is new line then the command is entered incorrect
			throw std::invalid_argument("Wrong input!"); //It is required an int to be entered to be a valid line 
		else
			commReciever[count - 1] = 0;

		std::cin >> num; 
		if (std::cin.fail()) //If the inputed is not an integer 
		{
			std::cin.clear();
			std::cin.ignore(MAX, '\n');
			throw std::invalid_argument("Wrong input!");
		}
		
		std::cin.get(ch); //Checks if there are any other inputs
		if (ch != '\n') 
		{
			std::cin.ignore(MAX, '\n');
			throw std::invalid_argument("Input Too Long!");
		}
	}

	if (choice == 'r' || choice == 'b' || choice == 'n') //remove user OR block OR unblock
	{
		std::cin >> commReciever;
		std::cin.get(ch);
		if (ch != '\n')
		{
			std::cin.ignore(MAX, '\n');
			throw std::invalid_argument("Input Too Long!");
		}
	}

	if (choice == 't' || choice == 'i') //text OR image
	{
		std::cin.getline(content,MAX,'\n');
	}

	if (choice == 'p' || choice == 'v') //remove post OR view post
	{
		std::cin >> num; //Use cin.fail()
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(MAX, '\n');
			throw std::invalid_argument("Wrong input!");
		}

		std::cin.get(ch);
		if (ch != '\n')
		{
			std::cin.ignore(MAX, '\n');
			throw std::invalid_argument("Input Too Long!");
		}

	}

	if (choice == 'w') //View all
	{
		std::cin >> commReciever;
		std::cin.get(ch);
		if (ch != '\n')
		{
			std::cin.ignore(MAX, '\n');
			throw std::invalid_argument("Input Too Long!");
		}
	}

	if (choice == 'l')  //Link
	{
		int count = 0;
		for (count = 0; content[count - 1] != ' ' && content[count - 1] != '\n',content[count-1]!='\t'; ++count)
			std::cin.get(content[count]);

		if (content[count - 1] == '\n')
			throw std::invalid_argument("Wrong input!");
		else
			content[count - 1] = 0;

		std::cin.getline(description, MAX, '\n');
	}

	if (choice == 'c')
		std::cin.getline(commReciever, MAX, '\n');

}

int numOfInts(int num)
{
	if (num < 10)
		return 1;

	int count = 0;
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	return count;
}

void intToStr(char *str, int num) //If a int is >9 it makes it into a string and combines it with the rest of char array
{
	char* numStr = new char[numOfInts(num) + 1];

	_itoa(num, numStr, 10);
	
	strcat(str, numStr);

	delete[] numStr;
}
