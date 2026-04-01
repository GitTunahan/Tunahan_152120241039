#include <iostream>
#include <string>

using namespace std;



struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3]; // [0]: 100s, [1]: 50s, [2]: 20s
    MoneyBundle* next;
};

struct Customer {
    string customerName;
    string transactionType;
};


class MoneyStack {
private:
    MoneyBundle* top;

public:
    MoneyStack() : top(nullptr) {}

    void push(string sn, string type, int c100, int c50, int c20) {
        MoneyBundle* newNode = new MoneyBundle;
        newNode->serialNumber = sn;
        newNode->currencyType = type;
        newNode->billCounts[0] = c100;
        newNode->billCounts[1] = c50;
        newNode->billCounts[2] = c20;
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) return;
        MoneyBundle* temp = top;
        top = top->next;
        delete temp;
    }

    bool isEmpty() { return top == nullptr; }

    void display() {
        if (isEmpty()) {
            cout << "Safe is empty (No money bundles)." << endl;
            return;
        }
        cout << "\n--- MONEY IN SAFE (Stack - Top to Bottom) ---" << endl;
        MoneyBundle* curr = top;
        while (curr) {
            cout << "SN: " << curr->serialNumber << " | Type: " << curr->currencyType
                << " | Bills: [100s:" << curr->billCounts[0] << ", 50s:" << curr->billCounts[1]
                << ", 20s:" << curr->billCounts[2] << "]" << endl;
            curr = curr->next;
        }
    }
};


class CircularQueue {
private:
    Customer queue[5];
    int front, rear, count;
    const int capacity = 5;

public:
    CircularQueue() : front(0), rear(-1), count(0) {}

    bool isFull() { return count == capacity; }
    bool isEmpty() { return count == 0; }

    void enqueue(string name, string type) {
        if (isFull()) {
            cout << "Queue is Full! Customer cannot be added." << endl;
            return;
        }
        rear = (rear + 1) % capacity;
        queue[rear].customerName = name;
        queue[rear].transactionType = type;
        count++;
    }

    void dequeue() {
        if (isEmpty()) return;
        front = (front + 1) % capacity;
        count--;
    }

    Customer getFront() { return queue[front]; }

    void display() {
        if (isEmpty()) {
            cout << "No customers waiting in line." << endl;
            return;
        }
        cout << "\n--- CUSTOMER QUEUE (Circular) ---" << endl;
        int index = front;
        for (int i = 0; i < count; i++) {
            cout << "[" << i + 1 << "] Name: " << queue[index].customerName
                << " | Action: " << queue[index].transactionType << endl;
            index = (index + 1) % capacity;
        }
    }
};


int main() {
    MoneyStack safe;
    CircularQueue line;
    int choice;

    while (true) {
        cout << "\n=== BANK BRANCH MANAGEMENT SYSTEM ===" << endl;
        cout << "1. Receive Money (Push to Stack)" << endl;
        cout << "2. New Customer (Enqueue to Circular Queue)" << endl;
        cout << "3. Process Transaction (Pop & Dequeue)" << endl;
        cout << "4. Display All" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            string sn, type;
            int c100, c50, c20;
            cout << "Serial Number: "; cin >> sn;
            cout << "Currency Type (TL/USD): "; cin >> type;
            cout << "Count of 100s, 50s, 20s: "; cin >> c100 >> c50 >> c20;
            safe.push(sn, type, c100, c50, c20);
            cout << "Money bundle added successfully." << endl;

        }
        else if (choice == 2) {
            string name, trans;
            cout << "Customer Name: "; cin >> name;
            cout << "Transaction Type (Withdraw/Deposit): "; cin >> trans;
            line.enqueue(name, trans);

        }
        else if (choice == 3) {
            if (line.isEmpty()) {
                cout << "Error: No customers in line!" << endl;
            }
            else if (safe.isEmpty()) {
                cout << "Error: No money bundles in safe to process transaction!" << endl;
            }
            else {
                Customer c = line.getFront();
                cout << "Processing " << c.customerName << "'s " << c.transactionType << " transaction..." << endl;
                line.dequeue();
                safe.pop();
                cout << "Transaction completed. Customer removed and money bundle used." << endl;
            }

        }
        else if (choice == 4) {
            line.display();
            safe.display();

        }
        else if (choice == 5) {
            cout << "Exiting system..." << endl;
            break;

        }
        else {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
