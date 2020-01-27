#include <iostream>

using namespace std;

const int MAX = 100000;

//const int length = 17;

void EmptyTemp(char* temp,int length)
{
	for (int count = 0; count<length; count++)
	{
		temp[count] = 0;
	}
}

void print(char* temp,int numRepeat)
{
	int i=0;
	do
	{
		cout<<temp;
		i++;
	} while (i < numRepeat);
}

int Bracket2Bracket(char* compress,char* temp,int count)
{
	count++;
	int openBracket=1,
	closeBracket=0;
	
	int tempInt=0;
	
	while(closeBracket<openBracket)
	{
		if(compress[count]==')')
		{
			closeBracket++;
		}
		
		if(compress[count]=='(')
		{
			openBracket++;
		}
		
		if (closeBracket != openBracket)
		{
		temp[tempInt]=compress[count];
		count++;
		tempInt++;
		}
	}
	return count;
}

void Compression(char* compress,char* temp,char* temp1,int length)
{
    int count=0,
     tempInt =0,
     mul=1,
     numRepeat=0;

	bool flag = false;

		while(true)
        {
		if(compress[count]>=65 && compress[count]<=90)
		{
			flag = false;
			temp[tempInt]=compress[count];
			tempInt++;
			mul=1;
		}
		
		if(compress[count]>=48 && compress[count]<=57)
		{
			if(flag==false)
			{
				if(numRepeat==0)
				{
					print(temp,1);           //First time print before any num
					EmptyTemp(temp,length);
					tempInt = 0;
					flag=true;
				}else{
					print(temp,numRepeat);
					EmptyTemp(temp,length);
					tempInt = 0;
					flag=true;
					numRepeat=0;
				}

			}
				numRepeat= numRepeat*mul+ (compress[count]-48);
				mul*=10;
		}
		
		if(compress[count]==40)
		{
			count = Bracket2Bracket(compress, temp, count);
			for(int i=0;i<numRepeat;i++)
			{
				Compression(temp, temp1,temp1,length);
			}
			EmptyTemp(temp1,length);
			EmptyTemp(temp,length);
			numRepeat=0;
			mul=1;
		}

		if(compress[count+1]=='\0')
		{
			if (compress[count] == ')')
			{
				break;
			}
			print(temp, numRepeat);
			break;
		}
		count++;
	}
}


void Program(char* text)
{
	int length = strlen(text) + 1;

	char* compress = new (nothrow) char[length];
	char* temp = new (nothrow) char[length];
	char* temp1 = new (nothrow) char[length];

	if (compress && temp&& temp1)
	{
	EmptyTemp(temp,length);
	EmptyTemp(temp1,length);

	strcpy(compress,text);

	Compression(compress,temp,temp1,length);

	delete[] compress;
	delete[] temp;
	delete[] temp1;

	cout << endl;
	}
	else
	{
		cout << "ERROR\n";
	}

}


int main()
{
	char text[MAX];
	cin >> text;
	
	Program(text);

	system("pause");
	return 0;
}