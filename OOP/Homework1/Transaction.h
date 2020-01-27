#ifndef  TRANSACTION_HDR
#define TRANSACTION_HDR



struct Transaction {
	long long time;
	unsigned senderId;
	unsigned receiverId;
	double fmiCoins;
};

int countTransaction(); //Returns the size of transaction.dat file
void makeTransactionsV2(const long long&, const unsigned&, const unsigned&, const double&); //Make Transaction and save it in transactions.dat file
double calcCoins(const unsigned&); //Calculates coins by counting past transactions for the entered ID
void printTrans();
void firstAndLastTrans(const unsigned&); //Finds what the first and last transaction of the entered ID is

#endif // ! TRANSACTION_HDR
