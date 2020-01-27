#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

const int MAX = 256;

void start();
void inputAdmin(char*,int&,bool&);
void inputFirst(char*, char&);
void inputSecond(char*);
void findCommand(const char*, char&, char*, char*, char*, int&);
int numOfInts(int);
void intToStr(char*, int);

#endif // !INPUT_H_INCLUDED
