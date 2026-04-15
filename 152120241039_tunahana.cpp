#include <iostream>
using namespace std;

#define MAX 100

// --- STACK IMPLEMENTATION (DO NOT MODIFY) ---
struct Stack {
    int arr[MAX];
    int top;
};

void initStack(Stack* s) { s->top = -1; }
bool isStackEmpty(Stack* s) { return s->top == -1; }
void push(Stack* s, int val) {
    if (s->top < MAX - 1) {
        s->arr[++(s->top)] = val;
    }
}
int pop(Stack* s) {
    if (!isStackEmpty(s)) {
        return s->arr[(s->top)--];
    }
    return -1; // Error or Empty
}
void printStack(Stack* s) {
    if (isStackEmpty(s)) {
        cout << "Stack is empty." << endl;
        return;
    }
    cout << "[Top] ";
    for (int i = s->top; i >= 0; i--) {
        cout << s->arr[i] << " ";
    }
    cout << "[Bottom]" << endl;
}

// --- QUEUE IMPLEMENTATION (DO NOT MODIFY) ---
struct Queue {
    int arr[MAX];
    int front;
    int rear;
};

void initQueue(Queue* q) { q->front = -1; q->rear = -1; }
bool isQueueEmpty(Queue* q) { return q->front == -1 || q->front > q->rear; }
void enqueue(Queue* q, int val) {
    if (q->rear < MAX - 1) {
        if (q->front == -1) q->front = 0;
        q->arr[++(q->rear)] = val;
    }
}
int dequeue(Queue* q) {
    if (!isQueueEmpty(q)) {
        return q->arr[(q->front)++];
    }
    return -1; // Error or Empty
}

// ==========================================
// LAB TASK: IMPLEMENT THIS FUNCTION
// ==========================================
void transferStack(Stack* source, Stack* destination) {
    Queue tempQueue;
    initQueue(&tempQueue);

    while (!isStackEmpty(source)) {
        enqueue(&tempQueue, pop(source));
    }

    while (!isQueueEmpty(&tempQueue)) {
        push(destination, dequeue(&tempQueue));
    }

    Stack tempStack;
    initStack(&tempStack);

    while (!isStackEmpty(destination)) {
        push(&tempStack, pop(destination));
    }

    while (!isStackEmpty(&tempStack)) {
        int val = pop(&tempStack);
        push(source, val);
        push(destination, val);
    }
}
// ==========================================

int main() {
    Stack stackA, stackB;
    initStack(&stackA);
    initStack(&stackB);

    cout << "Please enter 5 integers for Stack A:" << endl;
    for (int i = 0; i < 5; i++) {
        int val;
        cin >> val;
        push(&stackA, val);
    }

    cout << "\nOriginal Stack A: ";
    printStack(&stackA);

    transferStack(&stackA, &stackB);

    cout << "After transfer, Stack A: ";
    printStack(&stackA);

    cout << "After transfer, Stack B: ";
    printStack(&stackB);

    return 0;
}