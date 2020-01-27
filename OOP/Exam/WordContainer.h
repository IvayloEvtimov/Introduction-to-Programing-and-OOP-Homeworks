#ifndef WORDCONTAINER_H
#define WORDCONTAINER_H

#include "Date.h"
#include "Hashtag.h"
#include "Simple.h"

class WordContainer
{
public:
	WordContainer();
	WordContainer(const WordContainer&);
	WordContainer& operator=(const WordContainer&);
	~WordContainer();


	void newWord(const Word&);
	double compare(const Word&) const;

	void printHash() const;

private:
	void copy(const Word**);
	void clean(const int&);
	void resize();

private:
	int size = 0;
	int maxSize = 0;
	Word** words;
};

#endif // !WORDCONTAINER_H
