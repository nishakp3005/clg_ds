#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

// Structure to represent a stack
struct Stack {
    int arr[MAX_SIZE];
    int top;
};

// Function to initialize a stack
void initStack(struct Stack* stack) {
    stack->top = -1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return (stack->top == -1);
}

// Function to check if the stack is full
int isFull(struct Stack* stack) {
    return (stack->top == MAX_SIZE - 1);
}

// Function to push an element onto the stack
void push(struct Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack is full. Cannot push.\n");
        return;
    }
    stack->arr[++(stack->top)] = value;
}

// Function to pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot pop.\n");
        return -1;
    }
    return stack->arr[(stack->top)--];
}

// Structure to represent a Banker's Queue using two stacks
struct BankersQueue {
    struct Stack stack1;  // Rear stack for enqueue
    struct Stack stack2;  // Front stack for dequeue
};

// Function to enqueue an element into the Banker's Queue
void enqueue(struct BankersQueue* queue, int value) {
    if (isFull(&(queue->stack1)) || isFull(&(queue->stack2))) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    
    while (!(isEmpty(&(queue->stack2)))) {
        push(&(queue->stack1), pop(&(queue->stack2)));
    }
    
    push(&(queue->stack1), value);
}

// Function to dequeue an element from the Banker's Queue
int dequeue(struct BankersQueue* queue) {
    if (isEmpty(&(queue->stack1)) && isEmpty(&(queue->stack2))) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }
    
    while (!(isEmpty(&(queue->stack1)))) {
        push(&(queue->stack2), pop(&(queue->stack1)));
    }
    
    return pop(&(queue->stack2));
}

int main() {
    struct BankersQueue queue;
    initStack(&(queue.stack1));
    initStack(&(queue.stack2));

    enqueue(&queue, 1);
    enqueue(&queue, 2);
    enqueue(&queue, 3);

    printf("Dequeued element: %d\n", dequeue(&queue)); // Output: Dequeued element: 1

    enqueue(&queue, 4);

    printf("Dequeued element: %d\n", dequeue(&queue)); // Output: Dequeued element: 2

    return 0;
}
