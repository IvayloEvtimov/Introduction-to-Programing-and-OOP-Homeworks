#ifndef HASHTAG_H
#define HASHTAG_H

#include "Word.h"

class Hashtag : public Word
{
public:
	Hashtag(const char*);

	char getType() const;
	double compare(const Word&) const;
	Word* clone() const;
};

#endif // !HASGTAH_H
