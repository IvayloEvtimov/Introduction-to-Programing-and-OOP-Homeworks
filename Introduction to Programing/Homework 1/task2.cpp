#include <iostream>
//#include <time.h>

using namespace std;

void Info(const double pHealth,const double pDamage,const double pArmour,const double pLuck,const double pPotion,const double mHealth,const double mDamage,const double mArmour,const double mLuck)
{
	cout<<"Player:"<<endl;
	cout<<"Health: "<<pHealth<<endl;
	cout<<"Damage: "<<pDamage<<endl;
	cout<<"Armour: "<<pArmour<<endl;
	cout<<"Luck: "<<pLuck<<endl;

	cout<<"__________________"<<endl;

	cout<<"Monster"<<endl;
	cout<<"Health: "<<mHealth<<endl;
	cout<<"Damage: "<<mDamage<<endl;
	cout<<"Armour: "<<mArmour<<endl;
	cout<<"Luck: "<<mLuck<<endl;
}

void Attack(double pHealth,double pDamage,double pArmour,double pLuck,double pPotion,double mHealth,double mDamage,double mArmour,double mLuck,char id,double pAttackSum,double mAttackSum)
{
	double reduce =0,
		chance=0;
	bool doubleDamage=false;

	if(id == 'p')
	{
		reduce=(mArmour/10)*0.05;
		chance = (pLuck/10)*0.5;
		pAttackSum+=chance;

		if(pAttackSum>=1)
		{
			doubleDamage=true;
			pAttackSum=0;
		}

		if(doubleDamage==true)
		{
			mHealth=mHealth -(pDamage-reduce)*2;
			cout<<"You have dealt "<< (pDamage-reduce)*2 <<" damage."<<endl;
		}else
		{
			mHealth=mHealth -(pDamage-reduce);
			cout<<"You have dealt "<< (pDamage-reduce) <<" damage "<<endl;
		}
	}

	doubleDamage= false;

	if(id=='m')
	{
		reduce=(pArmour/10)*0.05;
		chance = (mLuck/10)*0.5;
		mAttackSum+=chance;

		if(mAttackSum>=1)
		{
			doubleDamage=true;
			mAttackSum=0;
		}
		if(doubleDamage==true)
		{
			pHealth=pHealth -(mDamage-reduce)*2;
			cout<<"The Monster has dealt "<< (mDamage-reduce)*2 <<" damage."<<endl;
		}else
		{
			pHealth=pHealth -(mDamage-reduce);
			cout<<"The Monster has dealt "<< (mDamage-reduce) <<" damage."<<endl;
		}
	}
}


void Potion(double pHealth,double pPotion,double currentHealth)
{
	pHealth=currentHealth;
	pPotion--;
}

void AssignPoints(double pHealth,double pDamage,double pArmour,double pLuck,int points)
{
	char choice;
	while(points>0)
	{
		cout<<"Assign POINT to "<<endl;
		cin>>choice;
		switch(choice)
		{
		case 'H':
			pHealth++;
			points--;
			cout<<"You have increased HEALTH";
			break;
		case 'A':
			pArmour++;
			points--;
			break;
		case 'D':
			pDamage++;
			points--;
			break;
		case 'L':
			pLuck++;
			points--;
			break;
	}
}


void Start()
{
	double pHealth=100,
		pDamage=10,
		pArmour=25,
		pLuck=5,
		pPotion=5;

	double currentHealth=pHealth;

	double mHealth=50,
		mDamage = 5,
		mArmour=5,
		mLuck=0;

	double pAttackSum=0,
		pDefendSum=0;

	double mAttackSum=0,
		mDefendSum=0;

	bool flag = true,
		pDefence=false,
		mDefence=false,
		pDeath=false,
		mDeath=false;

	char pChoice,
		id='p';

	int points=0;

	while(flag==true)
	{
		cin>>pChoice;

		if(pChoice =='I'|| pChoice =='A' || pChoice =='D' || pChoice =='P' || pChoice =='X')
		{
			id='p';
			switch(pChoice)
		{
			case 'I':
				Info(pHealth,pDamage,pArmour,pLuck,pPotion,mHealth,mDamage,mArmour,mLuck);
				break;
			case 'A':
				if(mDefence==true)
				{
					Attack(pHealth,(pDamage/2),pArmour,pLuck,pPotion,mHealth,mDamage,mArmour,mLuck,id,pAttackSum,mAttackSum);
					mDefence=false;
				}else
				{
					Attack(pHealth,pDamage,pArmour,pLuck,pPotion,mHealth,mDamage,mArmour,mLuck,id,pAttackSum,mAttackSum);
				}
				
				break;
			case 'D':
				pDefence = true;
				break;
			case 'P':
				Potion(pHealth,pPotion,currentHealth);
				break;
			case 'X':
				flag = false;
				break;
			}
			
			if(mHealth <=0)
			{
				cout<<"You have defeated a Monster"<<endl;
				points=5;
				AssignPoints(pHealth,pDamage,pArmour,pLuck,points);
			}

			int mChoice = rand()%2;

			if(flag==true)
			{
				id='m';
				switch(mChoice)
				{
				case 0:
					if(pDefence==true)
					{
						Attack(pHealth,pDamage,pArmour,pLuck,pPotion,mHealth,(mDamage/2),mArmour,mLuck,id,pAttackSum,mAttackSum);
						pDefence=false;
					}else
					{
						Attack(pHealth,pDamage,pArmour,pLuck,pPotion,mHealth,mDamage,mArmour,mLuck,id,pAttackSum,mAttackSum);
					}
					break;
				case 1:
					mDefence=true;
					break;
				}
			}	
		}else
		{
			cout<<"ERROR"<<endl;
		}

		
	}

}




int main()
{
	Start();


	system("pause");
	return 0;
}