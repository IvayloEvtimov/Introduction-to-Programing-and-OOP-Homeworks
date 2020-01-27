#ifndef MESSAGECONTAINER_H
#define MESSAGECONTAINER_H

#include "Message.h"

class MessageContainer
{
public:
	MessageContainer();
	MessageContainer(const MessageContainer&);
	MessageContainer& operator=(const MessageContainer&);
	~MessageContainer();

	void newMessage(const char*);
	void printHash() const;
	Message compare(const char*) const;

private:
	void copy(const Message**);

	void clean(const int&);
	void resize();

private:
	int size;
	int maxSize;
	Message** messages;
};

#endif // !MESSAGECONTAINER_H
