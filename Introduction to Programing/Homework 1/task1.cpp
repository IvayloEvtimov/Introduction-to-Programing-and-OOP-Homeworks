#include <iostream>

using namespace std;

bool check(int l,int m,int r)
{
	if(m>=r  && m>=l)
	{
		return true;
	}else if(m<=r && m<=l)
	{
		return true;
	}else 
	{
		return false;
	}
}


int main()
{
	int a=0,
		b=0,
		c=0;
	bool flag = true;
	int N=0;

	cin>>N;

	if(N<1000000000)
	{
		if(N<3)
		{
		cout<<"yes\n"<<endl;
		}else 
		{
			cin>>a>>b;
			for(int i=3;i<=N;i++)
			{
				cin>>c;
				if(a<1000000 && b<1000000 && c<1000000)
				{
					if(check(a,b,c)==0)
					{
						cout<<"no\n";
						flag = false;
						break;
					}
					a=b;
					b=c;
				
					if(flag==true)
					{
						cout<<"yes\n";
					}

				}else
				{
					break;
				}
			}
		}
	}
	system("pause");
	return 0;
}