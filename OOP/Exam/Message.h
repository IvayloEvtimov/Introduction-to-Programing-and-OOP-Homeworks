#ifndef MESSAGE_H
#define MESSAGE_H

#include <fstream>

#include "WordContainer.h"

class Message
{
public:
	Message(const char*);
	Message(const Message&);
	Message& operator=(const Message&);
	~Message();

	void printHash() const;
	double compare(const char*) const;

	Message* clone() const;

	friend std::ostream& operator<<(std::ostream&, const Message&);
private:
	void addWords();

	void getCharUntil(int&, char*) const;
	bool validChar(const char&) const;
	char findType(const char*) const;

private:
	char* wholeMessage;
	WordContainer words;
};

#endif // !MESSAGE_H
