#ifndef Ledger_h
#define Ledger_h

#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int uniqueID; // Unique identifier for the current node.
    string sender; // Tracks who sent money.
    string receiver; // Tracks who received money.
    int amount; // Tracks how much money was sent/received.
    Node* next; // Tracks the next transaction.
};

class Ledger
{
public:
    Ledger(); // Creates a new, empty linked list.
    ~Ledger(); // Cleans up all of the allocated memory.
    
    int AddExternalMoney(string, int); // Adds Amount money to the system in the name of ToName
    int AddPayment(string, string, int); // enters a transfer from FromName to ToName in the amount of Amount. FromName now has Amount less money and ToName now has Amount more money. Returns the transaction Id.
    int RefundPayment(int); // Deletes the node referred to by the Node Id. If the node isn't found, returns ­1.
    int RefundPayment(string, string, int); // Deletes the node referred to by the exact match of FromName, ToName, and Amount. If the node isn't found, returns ­1.
    
    void Clear(); // Removes all of the transactions.
    
    void Print(); // Prints the entire ledger.
    void Print(string); // Prints the ledger for only a specific user.
    void Settle(); // Prints the name and balance of each user.
    void InTheBlack(); // Prints the name and balance of each user who has positive money.
    void InTheRed(); // Prints the name and balance of each user who has negative money.
private:
    int newID; // Dictates the unique id.
    Node* header; // Node header.
    vector<string> names; // Saves a list of users who were a part of the ledger.
    
    // helper methods
    bool checkName(string); // Used to check if a name exists in the ledger.
    Node *getPrevious(int); // Gets the previous node of a specified node in the ledger.
    bool checkID(int); // Checks if a node unique id exists in the ledger.
    bool isEmpty() const; // Checks if the ledger is empty.
    Node *findByIndex(int) const; // Find a node by index.
};

#endif /* Ledger_h */
