#ifndef Ledger_h
#define Ledger_h

#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int uniqueID;
    string sender;
    string receiver;
    int amount;
    Node* next;
};

class Ledger
{
public:
    Ledger(); // Constructor
    ~Ledger(); // Destructor
    
    int AddExternalMoney(string, int);
    int AddPayment(string, string, int);
    int RefundPayment(int);
    int RefundPayment(string, string, int);
    
    void Clear();
    
    void Print();
    void Print(string);
    void Settle();
    void InTheBlack();
    void InTheRed();
private:
    int newID;
    Node* header;
    vector<string> names;
    
    // helper methods
    bool checkName(string);
    Node *getPrevious(int);
    bool checkID(int);
    bool isEmpty() const;
    Node *findByIndex(int) const;
};

#endif /* Ledger_h */
