#ifndef WORD_H
#define WORD_H

class Word
{
public:
	Word(const char*);
	Word(const Word&);
	Word& operator=(const Word&);
	~Word();

	const char* getWord() const;
	virtual char getType() const=0;
	virtual double compare(const Word&)const=0;
	virtual Word* clone() const = 0;
protected:
	char toLower(const char&) const;
	char toHigher(const char&) const;
	void copy(const char*);
protected:
	char* word;
};

#endif // !WORD_H
