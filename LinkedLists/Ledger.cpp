#include "Ledger.h"

/*
 * The constructor method initializes the header (starting point) of the ledger (linked list).
 * It also sets the beginning number for each node's unique id (arbitrary as long as it doesn't start on 0).
 */
Ledger::Ledger() {
    // set header equal to a new node
    header = new Node;
    // set the next value equal to null (empty linked list)
    header->next = NULL;
    // set the starting point of the unique id
    newID = 100;
}

/*
 * The decontructor removes all nodes and deletes the header.
 */
Ledger::~Ledger() {
    Clear();
    delete header;
}

/*
 * AddExternalMoney creates a new node and populates it with a unique id, receiver, and amount.
 * The header then points to the new node and the new node points to what the header was previous pointing to.
 */
int Ledger::AddExternalMoney(string r, int a) {
    // create a new node
    Node *newNode = new Node;
    
    // fill the new node with values
    newNode->uniqueID = newID++;
    newNode->sender = "";
    newNode->receiver = r;
    newNode->amount = a;
    
    // point the new node to whatever the header is pointing to
    newNode->next = header;
    
    // point the header to the new node
    header = newNode;
    
    // add the name to the name list as long as they don't already exist
    if (!checkName(r)) {
        names.push_back(r);
    }
    
    // return the unique id
    return newNode->uniqueID;
}

/*
 * AddPayment creates a new node that tracks who is sending n amount of money and who is receiving that money.
 * This data is saved in a new node with a unique id.
 */
int Ledger::AddPayment(string s, string r, int a) {
    // create a new node
    Node *newNode = new Node;
    
    // fill the new node with information
    newNode->uniqueID = newID++;
    newNode->sender = s;
    newNode->receiver = r;
    newNode->amount = a;
    
    // point the new node to whatever the header is pointing to
    newNode->next = header;
    
    // point the header to the new node
    header = newNode;
    
    // add the name to the name list as long as they don't already exist
    if (!checkName(r)) {
        names.push_back(r);
    }
    if (!checkName(s)) {
        names.push_back(s);
    }
    
    // return the unique id
    return newNode->uniqueID;
}

/*
 * RefundPayment(int) searches for the unique id on the ledger and removes it.
 * If the unique id isn't found on a node within the ledger, -1 is returned.
 */
int Ledger::RefundPayment(int uID) {
    // check that uID exists
    if (!checkID(uID))
        return -1;
    
    // get the previous node
    Node *p = getPrevious(uID);
    
    if (p->uniqueID == uID) {
        Node *deletedNode = header;
        Node *temp = header->next;
        delete deletedNode;
        header = temp;
    } else {
        // set node to be deleted
        Node *deletedNode = p->next;
        
        // set the previous node to point to the next node
        if (p->next->next->uniqueID == 0) {
            p->next = NULL;
        } else {
            p->next = p->next->next;
        }
        
        // delete the node
        delete deletedNode;
    }
    return 1;
}

/*
 * RefundPayment(string, string, int) searches for matching sender, receiver, and amount on the ledger and removes it.
 * If all of the values aren't absolutely matching, -1 is returned.
 */
int Ledger::RefundPayment(string s, string r, int a) {
    // create a pointer
    Node *p = header;
    
    // check that sender, receiver, and amount are equal to parameters
    while (p->uniqueID != 0) {
        if (p->sender == s && p->receiver == r && p->amount == a) {
            RefundPayment(p->uniqueID);
            return 1;
        }
        p = p->next;
    }
    return -1;
}

/*
 * Clear removes all nodes on the ledger.
 * This does not delete the header.
 */
void Ledger::Clear() {
    // clear the names vector
    names.clear();
    
    // remove each node
    while (!isEmpty()) {
        Node *node = findByIndex(0);
        RefundPayment(node->uniqueID);
    }
}

/*
 * Print the id, sender, receiver, and amount of each node to the console.
 */
void Ledger::Print() {
    // create pointer
    Node *p = header;
    
    // iterate through list
    while (p != NULL && p->uniqueID != 0) {
        // print
        if (p->sender != "") {
            cout << "ID: " << p->uniqueID << " Sender: " << p->sender << " Receiver: " << p->receiver << " Amount: " << p->amount << endl;
        } else {
            cout << "ID: " << p->uniqueID << " Receiver: " << p->receiver << " Amount: " << p->amount << endl;
        }
        
        // go to next node
        p = p->next;
    }
}

/*
 * Print(string) only returns the id, sender, receiver, and amount of a node that contains a matching name.
 */
void Ledger::Print(string name) {
    // create pointer
    Node *p = header;
    
    // iterate through list
    while (p->uniqueID != 0) {
        // print only if the name is in the node sender or receiver
        if (p->receiver == name || p->sender == name) {
            cout << "ID: " << p->uniqueID << " Sender: " << p->sender << " Receiver: " << p->receiver << " Amount: " << p->amount << endl;
        }
        
        // go to next node
        p = p->next;
    }
}

/*
 * Returns the name and total amount of each user who added to the ledger.
 */
void Ledger::Settle() {
    // create pointer
    Node *p = header;
    
    // save the total amount per person
    int totalAmount = 0;
    
    // go through each name
    for (int i = 0; i < names.size(); i++) {
        // iterate through list
        while (p->uniqueID != 0) {
            // check if the name is a receiver or sender and add to total
            if (p->receiver == names[i]) {
                totalAmount += p->amount;
            } else if (p->sender == names[i]) {
                totalAmount -= p->amount;
            }
            
            // go to next node
            p = p->next;
        }
        
        // print only if the name is in the node sender or receiver
        cout << "Name: " << names[i] << " Amount: " << totalAmount << endl;
       
        // reset total amount
        totalAmount = 0;
        
        // set pointer back to header
        p = header;
    }
}

/*
 * Prints a list of all users who have a positive total amount or 0 in their account.
 */
void Ledger::InTheBlack() {
    // create pointer
    Node *p = header;
    
    // save the total amount per person
    int totalAmount = 0;
    
    // go through each name
    for (int i = 0; i < names.size(); i++) {
        // iterate through list
        while (p->uniqueID != 0) {
            // check if the name is a receiver or sender and add to total
            if (p->receiver == names[i]) {
                totalAmount += p->amount;
            } else if (p->sender == names[i]) {
                totalAmount -= p->amount;
            }
            
            // go to next node
            p = p->next;
        }
        
        // print only if the name is in the node sender or receiver and greater than or equal to 0
        if (totalAmount >= 0) {
            cout << "Name: " << names[i] << " Amount: " << totalAmount << endl;
        }
            
        // reset total amount
        totalAmount = 0;
        
        // set pointer back to header
        p = header;
    }
}

/*
 * Prints a list of all users who have a negative total amount in their account.
 */
void Ledger::InTheRed() {
    // create pointer
    Node *p = header;
    
    // save the total amount per person
    int totalAmount = 0;
    
    // go through each name
    for (int i = 0; i < names.size(); i++) {
        // iterate through list
        while (p->uniqueID != 0) {
            // check if the name is a receiver or sender and add to total
            if (p->receiver == names[i]) {
                totalAmount += p->amount;
            } else if (p->sender == names[i]) {
                totalAmount -= p->amount;
            }
            
            // go to next node
            p = p->next;
        }
        
        // print only if the name is in the node sender or receiver and less than 0
        if (totalAmount < 0) {
            cout << "Name: " << names[i] << " Amount: " << totalAmount << endl;
        }
        
        // reset total amount
        totalAmount = 0;
        
        // set pointer back to header
        p = header;
    }
}

// helper methods
/*
 * Checks if a name has already been used on a ledger.
 * This is a flaw in the system because if there are 2 people named "alice", then the system would count that as 1 person.
 */
bool Ledger::checkName(string n) {
    // go through the names array
    for (int i = 0; i < names.size(); i++) {
        // if the name exists, return true
        if (names[i] == n) {
            return true;
        }
    }
    // if not, return false
    return false;
}

/*
 * Returns the previous node in the ledger (linked list)
 */
Node *Ledger::getPrevious(int uID) {
    // create a pointer
    Node *p = header;
    // check if the pointer's id is equal to the inputed id
    // if the header is the position, return the header
    if (header->uniqueID == uID) {
        return p;
    } else {
        // otherwise, check if the next node has equal unique ids and return the current pointer
        while (p->next->uniqueID != uID) {
            p = p->next;
        }
        return p;
    }
}

/*
 * Checks whether a unique id exists within the ledger (linked list).
 */
bool Ledger::checkID(int uID) {
    // create a pointer
    Node *p = header;
    // as long as the unique id of the nodes aren't equal, go to the next node
    while (p->uniqueID != 0) {
        // if it finds equal ids, it returns true
        if (p->uniqueID == uID) {
            return true;
        }
        p = p->next;
    }
    // otherwise return false
    return false;
}

bool Ledger::isEmpty() const {
    // check if the header is empty (null)
    return header->next == NULL;
}

/*
 * Finds a node by index.
 */
Node *Ledger::findByIndex(int index) const {
    // if index isn't negative, return null
    if (index < 0)
        return NULL;
    
    // create a pointer that looks at header
    Node *ptr = header;
    // iterate as long as the pointer isn't null
    for (int i = 0; ptr != NULL; ptr = ptr->next, i++)
        // break once the pointer reaches the index
        if (i == index)
            break;
    // return the pointer
    return ptr;
}
