#ifndef LOCATION_H_INCLUDED
#define LOCATION_H_INCLUDED

class Location
{
public:
	Location();
	Location(const char*);
	Location(const Location&);
	Location& operator=(const Location&);
	~Location();

	void loadFromFile();

	const char* getPath();
	int getLine() const;
private:
	char* path;
	int line;
};


#endif // !LOCATION_H_INCLUDED
