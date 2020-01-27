#ifndef PUBLICATION_H_INCLUDED
#define PUBLICATION_H_INCLUDED

#include <fstream>

class Publication
{
public:
	Publication(const char*);
	Publication(const Publication&);
	Publication& operator=(const Publication&);
	virtual ~Publication();

	unsigned int getId() const;

	virtual void saveToHTML(std::ostream&) const=0;

	virtual Publication* clone() const = 0;

protected:
	char* content;
	unsigned int id;
private:
	static unsigned int unique;
};

#endif // !PUBLICATION_H_INCLUDED
