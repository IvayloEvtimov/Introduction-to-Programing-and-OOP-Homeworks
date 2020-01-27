#ifndef CHARARRAY_H_INCLUDED
#define CHARARRAY_H_INCLUDED

//Used for taking a text file and serializing it into a 2d char array

class CharArray
{
public:
	CharArray(const char*);
	CharArray(const CharArray&);
	CharArray& operator=(const CharArray&);
	~CharArray();


	int getLine() const; 
	const char* getPath() const;
	const char* getText(const int&);

	void addLine(const char*);  //Used for user input 
	void removeLine(const int&); //Removes a given line
	void modifyLine(const int&,const char*); //Modifies a given  line 
	bool checkLine(const int&) const; 
private:
	void loadFromFile(); //Used for determining how many lines there are
	void fillStr(); //Used for serializing the textArr var
	void clean(); //Deletes any memory allocated by textArr var
private:
	char* path; //Stores the path from which the content is taken
	int line; 
	char** textArr;
};

#endif // !CHARARRAY_H_INCLUDED
