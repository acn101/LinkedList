#include "Ledger.h"

// constructor
Ledger::Ledger() {
    header = new Node;
    header->next = NULL;
    newID = 100;
}

// destructor
Ledger::~Ledger() {
    // todo
}

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

void Ledger::Clear() {
    while (!isEmpty()) {
        Node *node = findByIndex(0);
        RefundPayment(node->uniqueID);
    }
}

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
bool Ledger::checkName(string n) {
    for (int i = 0; i < names.size(); i++) {
        if (names[i] == n) {
            return true;
        }
    }
    return false;
}

Node *Ledger::getPrevious(int uID) {
    Node *p = header;
    if (header->uniqueID == uID) {
        return p;
    } else {
        while (p->next->uniqueID != uID) {
            p = p->next;
        }
        return p;
    }
}

bool Ledger::checkID(int uID) {
    Node *p = header;
    while (p->uniqueID != 0) {
        if (p->uniqueID == uID) {
            return true;
        }
        p = p->next;
    }
    return false;
}

bool Ledger::isEmpty() const {
    return header->next == NULL;
}

Node *Ledger::findByIndex(int index) const {
    if (index < 0)
        return NULL;
    
    Node *ptr = header;
    for (int i = 0; ptr != NULL; ptr = ptr->next, i++)
        if (i == index)
            break;
    return ptr;
}
