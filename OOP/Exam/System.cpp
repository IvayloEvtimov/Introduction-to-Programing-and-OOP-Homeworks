#include "System.h"
#include "Constant.h"

#include <iostream>
#include <fstream>

System::System():messages()
{
}

void System::load(const char *filename)
{
	std::ifstream input(filename);

	if (!input.is_open())
		throw std::invalid_argument("Wrong file");

	char buffer[MAX_SIZE];

	bool eof = false;

	while (!eof)
	{
		int countBuffer = 0;
		while (true)
		{
			input.get(buffer[countBuffer++]);
			if (buffer[countBuffer - 1] == '\n')
				break;

			if (input.eof())
			{
				eof = true;
				break;
			}
		}
		buffer[countBuffer-1] = 0;

		messages.newMessage(buffer);

		if (input.eof())
			break;
	}
}

void System::printHash() const
{
	std::cout << "-- Hashtags:" << std::endl;
	messages.printHash();
}

Message System::operator[](const char *toCompare) const
{
	return messages.compare(toCompare);
}
