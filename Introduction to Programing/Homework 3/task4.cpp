#include <iostream>

using namespace std;

const int MAX=41;

void MakeMatrix(int K,char** matrix)
{
    int length=0;
    char word[MAX];

	for (int i = 0; i < K; i++)
	{
        cin>>word;
        length=strlen(word);
		matrix[i] = new (nothrow) char[length+1];
		for (int j = 0; j < length; j++)
		{
			matrix[i][j] = word[j];
		}
		matrix[i][length] = '\0';
	}

}

void MakeCrossWord(char** crossword,int M,int N)
{
    for(int count=0;count<M;count++)
    {
        crossword[count] = new(nothrow) char[N+1];
    }
}

void FillCrossword(char** crossword,int M,int N)
{
	for (int i = 0; i<M; i++)
	{
		for (int j = 0; j<N; j++)
		{
			cin >> crossword[i][j];
		}
		crossword[i][N] = '\0';
	}
}

void EmptyChar(char* ch,int num)
{
    for(int count=1;count<=num;count++)
    {
        ch[count]='\0';
    }

}

bool CheckLetterByLetter(char** matrix,char* buff,int row)
{
    for(int j=0;matrix[row][j]!=0;j++)
    {
        if(matrix[row][j]!=buff[j])
        {
            return false;
			break;
        }
    }
    return true;
}

bool CheckCrossword(char** matrix,char* buff,int M)
{
    for(int row=0;row<M;row++)
    {
        if(CheckLetterByLetter(matrix,buff,row)==1)
        {
            return true;
        }
    }
    return false;
}

void ClearChar(char* buff, int size)
{
	delete[] buff;
	buff = new char[size];

}

bool SearchCrosswordByRow(char** matrix,char** crossword,int M,int N,int K)
{
    char* buff = new(nothrow) char [N+1];


    int countBuff=0;

    int buffWord =0;
    int buffCorrectWords=0;

    if(buff)
    {
        for(int row=0;row<M;row++)
        {
            for(int column=0;column<N;column++)
            {
                if(crossword[row][column]!=42)
                {
                    buff[countBuff]=crossword[row][column];
                    countBuff++;
                } 

				if (crossword[row][column]==42 || column+1==N)
                {
					buff[countBuff] = '\0';
                    if(strlen(buff)>=2)
                    {
                        buffWord++;
                        if(CheckCrossword(matrix,buff,K)==1)
                        {
                            buffCorrectWords++;
                        }
                    }
						//EmptyChar(buff, N);
						ClearChar(buff, N+1);

                    countBuff=0;
                }
            }
        }
		delete[] buff;
		return (buffWord == buffCorrectWords) ? true : false;
       
	}
	else
	{
		cout << "ERROR\n";
		return 0;
	}
}

bool SearchCrosswordByCollumn(char** matrix,char** crossword,int M,int N,int K)
{
    char* buff = new char [M+1];
	
    int countBuff=0;

    int buffWord =0;
    int buffCorrectWords=0;

    if(buff)
    {
        for(int column=0;column<N;column++)
        {
            for(int row=0;row<M;row++)
            {
                if(crossword[row][column]!=42)
                {
                    buff[countBuff]=crossword[row][column];
                    countBuff++;
                }

				if (crossword[row][column]==42 || row+1==N)
                {
					buff[countBuff] = '\0';
                    if(strlen(buff)>=2)
                    {
                        buffWord++;
                        if(CheckCrossword(matrix,buff,K)==1)
                        {
                            buffCorrectWords++;
                        }
                    }
                    //EmptyChar(buff,M);
					ClearChar(buff, M + 1);
                    countBuff=0;
                }
            }
        }
        delete[] buff;
        return (buffWord == buffCorrectWords) ? true : false;
    }
}

void Delete2dChar (char** matrix,int num)
{
        for(int count =0;count<num;count++)
        {
            delete[] matrix[count];
        }
        delete[] matrix;

}

void PrintMatrix(int M, int N,char** matrix)
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << matrix[i][j];
		}
		cout << endl;
	}
}

int main()
{
    int K=0;
    cin>>K;

    int M=0,
    N=0;

    char** matrix = new(nothrow) char* [K+1];

    MakeMatrix(K,matrix);
    if(matrix)
    {
        cin>>M>>N;

        char** crossword = new(nothrow) char*[M];

        MakeCrossWord(crossword,M,N);
        if(crossword)
        {
            FillCrossword(crossword,M,N);
			cout << endl;
            if(SearchCrosswordByRow(matrix,crossword,M,N,K)==1)
            {
                (SearchCrosswordByCollumn(matrix, crossword, M, N,K) == 1) ? cout<<"True\n" : cout<<"False\n";
            }else
            {
                cout<<"False\n";
            }

        }

        Delete2dChar(matrix,K);
        Delete2dChar(crossword,M);

    }


	system("pause");

    return 0;
}
