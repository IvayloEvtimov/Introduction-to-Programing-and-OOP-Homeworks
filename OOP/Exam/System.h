#ifndef SYSTEM_H
#define SYSTEM_H

#include "MessageContainer.h"

class System
{
public:
	System();
	System(const System&) = delete;
	System& operator=(const System&) = delete;

	void load(const char*);
	void printHash() const;
	Message operator[](const char*) const;

private:
	MessageContainer messages;
};

#endif // !SYSTEM_H
