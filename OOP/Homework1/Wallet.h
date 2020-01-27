#ifndef WALLET_HDR
#define WALLET_HDR

#include "Transaction.h"

using namespace std;

struct Wallet {
	char owner[256];
	unsigned id = 0;
	double fiatMoney;
};


void changeContent(const Wallet&);  //Changes the content of a certain wallet
void add_wallet(const char*, const double&); //Adds another wallet to the wallet.dat file 
void StartUpCheck(); //Checks how many walleta ate there in wallet.dat 
int countWallet(); //Returns the size of wallet.dat
bool findId(const unsigned&); //Checks if the ID entered is valid
Wallet& getWallet(const unsigned&); //Returns a wallet struct by entering ID
void Print();
void walletInfo(const unsigned&); //Print a wallet by enetering ID
int countNum(unsigned); //Counts how many numbers there are
void attractInvestors(); //Print the top 10 most wealthy wallets
bool existingID(const unsigned&, const Wallet*, const int&); //Checks if Id exist

#endif // !WALLET_HDR


