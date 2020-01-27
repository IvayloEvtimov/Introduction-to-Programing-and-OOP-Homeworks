#include <iostream>

using namespace std;


long long Dec2Bin(long x)
{
	long long bin=0,
		remainder=0;
	long long i=1;
	while(x!=0)
	{
		remainder=x%2;
		bin= bin+remainder*i;
		x/=2;
		i*=10;
	}
	return bin;
}

long long CountNum(long long x)
{
	long long temp=x,
		counter=0;
	while (temp!=0)
	{
		counter++;
		temp/=10;
	}
	return counter;
}


long long Convert(long long x)
{
	long long div=1,
		n=0,
		temp=0;

	long long NewX=0;

	for(long j=1;j<CountNum(x);j++)
	{
		div*=10;

	}

	int ten=10;

	for(long i=0;i<CountNum(x);i++)
	{
		if(i==0)
		{
			temp=x/div;
		}else
		{
			temp = (x/div)%10;
		}

		if(div==1 && (CountNum(x)-i==1))
		{
			NewX=NewX*ten+ x%10;
			break;
		}

		n = x / (div / 10) % 10;

		if(temp==n)
		{
			if(temp==1)
			{
				NewX = NewX*ten + 1;
				NewX = NewX*ten + 0;
				div/=100;
				i++;

			}else if(temp==0)
			{
				NewX = NewX*ten + 0;
				NewX = NewX*ten + 1;
				div/=100;
				i++;
			}
		}else 
		{
			NewX = NewX*ten + temp;
			div/=10;
		}
	}

	return NewX;
}

long long Bin2Dec(long long x)
{
	long long temp =0,
		pow=1,
		dec=0;

	while(x>0)
	{
		temp = x % 10;
		dec = dec + (temp*pow);
		pow*=2;
		x/=10;
	}
	return dec;

}


int main()
{

	long x=0;
	cin>>x;
	if(x<=999999999)
	{
		long long Bin = Convert(Dec2Bin(x));
		cout<<Bin2Dec(Bin)<<endl;
	}
	

	system("pause");
	return 0;
}