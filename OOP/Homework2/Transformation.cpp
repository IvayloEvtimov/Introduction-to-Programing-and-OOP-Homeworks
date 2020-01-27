#include "Transformation.h"

#include <iostream>
#include <fstream>

Transformation::Transformation(const char *path) : file(path)
{

}

void Transformation::makeHeading(const int &line)
{
	if (!file.checkLine(line))
	{
		std::cout << "Invalid line entered\n";
		return;
	}

	charHeadingV3(line);
}

void Transformation::makeItalic(const int &lineToFind, const int &from, const int &to)
{
	if (!file.checkLine(lineToFind))
	{
		std::cout << "Invalid line entered\n";
		return;
	}

	char key = 'i';
	transformV4(lineToFind, from, to, key);
}

void Transformation::makeBold(const int &lineToFind, const int &from, const int &to)
{
	if (!file.checkLine(lineToFind))
	{
		std::cout << "Invalid line entered\n";
		return;
	}
	char key = 'b';
	transformV4(lineToFind, from, to, key);
}

void Transformation::makeCombine(const int &lineToFind, const int &from, const int &to)
{
	if (!file.checkLine(lineToFind))
	{
		std::cout << "Invalid line entered\n";
		return;
	}
	char key = 'c';
	transformV4(lineToFind, from, to, key);
}

void Transformation::addLine(const char *content)
{
	file.addLine(content);
}

void Transformation::removeLine(const int &lineToRemove)
{
	if (!file.checkLine(lineToRemove))
	{
		std::cout << "Invalid line entered\n";
		return;
	}
	file.removeLine(lineToRemove-1);
}

void Transformation::exit()
{
	char* newPath = new char[strlen(file.getPath())];
	int count = 0;
	while (count < strlen(file.getPath()) - 3)
	{
		newPath[count] = file.getPath()[count];
		count++;
	}
	newPath[count++] = 'm';
	newPath[count++] = 'd';
	newPath[count] = 0;

	std::ofstream output(newPath, std::ios::trunc);
	if (!output)
		std::cout << "File not open\n";

	for (int lineCount = 0; lineCount < file.getLine(); lineCount++)
	{
		if (lineCount == 0) //Puts std::endl on every line except on the first
			output << file.getText(lineCount);
		else
			output << std::endl << file.getText(lineCount);
	}
	output.close();

	delete[] newPath;
}

void Transformation::findStr(const int &from, const int &to, const char *currLine, int *wordsPos)
{
	int firstLetter = 0,
		lastLetter = 0;

	int countWords = 0;
	int count = 0;

	bool newWord = false;
	bool wordFound = false;
	bool sharp = false;

	while (true)
	{
		if (currLine[count] == '#') //Ingores # char because it is reserved for headings
			sharp = true;


		if (currLine[count] == 0 || currLine[count] == ' ' && newWord == false)
		{
			if (sharp == false)
			{
				countWords += 1;
				if (countWords == from) //If countWord is the same as from var 
					wordsPos[0] = firstLetter; //save the index pos of the words

				lastLetter = count;
				newWord = true;  
			}
			else
				sharp = false;
		}
		else if (newWord == true && currLine[count] != ' ')  //Signalizes the end of the word
		{
			firstLetter = count;
			newWord = false;
		}

		if (currLine[count] == ' ' && currLine[count + 1] != ' ') 
			firstLetter = count + 1;

		if (countWords == to)
		{
			wordsPos[1] = lastLetter; //If the second word is found, stops the search
			wordFound = true; 
			break;
		}

		if (currLine[count] == 0)
			break;
		count++;
	}

	if (!wordFound)
		return;
}

void Transformation::charHeadingV3(const int &lineToFind)
{
	int count = 0,
		countTemp = 0;

	char* temp = NULL;

	if (file.getText(lineToFind - 1)[0] == '#') //If the selected line is already a heading
	{
		temp = new char[strlen(file.getText(lineToFind - 1)) + 2];
		temp[0] = '#';
		countTemp = 1;
	}
	else
	{
		temp = new char[strlen(file.getText(lineToFind - 1)) + 3];
		temp[0] = '#';
		temp[1] = ' ';
		countTemp = 2;
	}

	while (file.getText(lineToFind - 1)[count] != 0)
	{
		temp[countTemp] = file.getText(lineToFind - 1)[count];
		count++;
		countTemp++;
	}
	temp[countTemp] = 0;

	file.modifyLine(lineToFind - 1, temp);
	delete[] temp;
}

void Transformation::transformV4(const int &lineToFind, const int &from, const int &to, char &key)
{
	int wordsPos[2] = { -1,-1 }; //If a word isn't found the value will remain -1
	findStr(from, to, file.getText(lineToFind - 1), wordsPos);

	if (wordsPos[0] == -1 || wordsPos[0] == -1) 
	{
		std::cout << "One or two of the entered words is invalid\n";
		return;
	}

	int asterBeg = 0,
		asterEnd = 0;

	if (checkAsterix(file.getText(lineToFind - 1), wordsPos, key) == 0)
	{
		std::cout << "Already formated or too many asterixes\n";
		return;
	}

	switch (key)
	{
	case 'i':
		asterBeg = 1;
		asterEnd = 1;
		break;
	case 'b':
		asterBeg = 2;
		asterEnd = 2;
		break;
	case 'c':
		asterBeg = 3;
		asterEnd = 3;
		break;
	}

	int countText = 0; //Used for the pos of file member object
	int countThis = 0; //Used for the pos of temp var

	bool notPause = true; //Used for pausing countText so that asterixes could be placed in temp var

	char* temp = new char[strlen(file.getText(lineToFind - 1))+asterBeg+asterEnd + 1];

	while (true)
	{
		if (countText == wordsPos[0])
		{
			notPause = false;
			temp[countThis] = '*';
			countThis++;
			asterBeg -= 1;
			if (asterBeg == 0) //If all asterixes are put in temp
				notPause = true; 
		}
		else if (countText == wordsPos[1])
		{
			notPause = false;
			temp[countThis] = '*';
			countThis++;
			asterEnd -= 1;
			if (asterEnd == 0)
				notPause = true;
		}

		if (notPause) //Resumes normal copying
		{
			temp[countThis] = file.getText(lineToFind-1)[countText];
			countText++;
			countThis++;
		}

		if (asterBeg==0&&asterEnd==0) 
			if(countText>=strlen(file.getText(lineToFind-1)))
				break;
	}
	if(temp[countThis-1]!=0)
		temp[countThis] = 0;

	file.modifyLine(lineToFind - 1, temp);

	delete[] temp;
}

bool Transformation::checkAsterix(const char *str, const int *wordsPos, char &key)
{
	int asterBeg = 0,
		asterEnd = 0;

	int sub = 0;

	if (key == 'i')
		sub = 1;
	if (key == 'b')
		sub = 2;
	if (key == 'c')
		sub = 3;

	int countFirst = wordsPos[0];
	while (str[countFirst] == '*')
	{
		asterBeg++;
		countFirst++;
	}

	int countLast = wordsPos[1] - 1;
	while (str[countLast] == '*')
	{
		asterEnd++;
		countLast--;
	}

	if (asterBeg == 1 && asterBeg == 1 && key == 'b') //If the  selected part is already italic
	{												 //It needs only another one asterix to be bold
		key = 'i';
		return true;
	}

	if (asterBeg == 1 && asterBeg == 1 && key == 'c') //If the  selected part is already italic
	{												 //It only needs another two asterixes to be combined
		key == 'b';
		return true;
	}

	if (asterBeg == 2 && asterBeg == 2 && key == 'c') //If the  selected part is already bold
	{												 //It only needs another one asterix to be combined
		key == 'i';
		return true;
	}

	if (asterBeg == 1 && asterBeg == 1 && key == 'i') //If the  selected part is already italic
		return false;				//And the enetered command is italic

	if (asterBeg == 2 && asterBeg == 2 && key == 'b') //If the  selected part is already bold
		return false;				//And the enetered command is bold

	if (asterBeg == 3 && asterBeg == 3 && key == 'c') //If the  selected part is already combined
		return false;				//And the enetered command is combined


	if (asterBeg + sub > 3 && asterEnd + sub > 3) //And the selecter part and the new command will have more than 3 asterixes
		return false;		//It won't be valid

	return true;
}