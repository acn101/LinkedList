#include <iostream>
#include "Ledger.h"

using namespace std;

int main () {

	Ledger myLedger;

	// test adding money
	myLedger.AddExternalMoney("alice", 100);
	myLedger.AddExternalMoney("bob", 10);
	myLedger.AddExternalMoney("fred", 50);
	
	myLedger.AddPayment("alice", "fred", 50);
	myLedger.AddPayment("bob", "fred", 100);
	myLedger.AddPayment("sam", "alice", 100);
	int cd50Id = myLedger.AddPayment("carol", "dawn", 50);
	myLedger.AddPayment("alice", "fred", 30);
	myLedger.AddPayment("fred", "bob", 2);

	myLedger.RefundPayment(cd50Id);
	cout << myLedger.RefundPayment(35480) << endl;  // this should return -1
	myLedger.RefundPayment("fred", "bob", 2);

	myLedger.AddPayment ("fred", "carol", 5);

	cout << endl << endl;
	myLedger.Print();
	cout << endl << endl;
	myLedger.Print("sam");
	cout << endl << endl;
	myLedger.Settle();
	cout << endl << endl;
	myLedger.InTheBlack();
	cout << endl << endl;
	myLedger.InTheRed();

	myLedger.Clear();
	myLedger.Print();






	return 0;
}
