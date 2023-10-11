#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the circular queue
struct QueueNode {
    int data;
    struct QueueNode* next;
};

// Structure to represent the circular queue
struct CircularQueue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

// Function to create an empty circular queue
struct CircularQueue* createQueue() {
    struct CircularQueue* queue = (struct CircularQueue*)malloc(sizeof(struct CircularQueue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to enqueue a person into the circular queue
void enqueue(struct CircularQueue* queue, int data) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = data;
    if (queue->rear == NULL) {
        newNode->next = newNode; // If the queue is empty, set the next pointer to itself
        queue->front = queue->rear = newNode;
    } else {
        newNode->next = queue->front; // Make the new node point to the front
        queue->rear->next = newNode; // Update the rear's next to point to the new node
        queue->rear = newNode; // Update the rear to the new node
    }
}

// Function to dequeue and eliminate every k-th person until one person remains
int josephus(struct CircularQueue* queue, int k) {
    struct QueueNode* current = queue->front;
    struct QueueNode* previous = NULL;

    while (queue->front->next != queue->front) {
        int count = 1;
        while (count < k) {
            previous = current;
            current = current->next;
            count++;
        }

        if (previous != NULL) {
            previous->next = current->next;
            queue->front = previous->next;
        } else {
            queue->rear = NULL;
            queue->front = NULL;
        }

        free(current);
        current = queue->front;
    }

    return current->data;
}

int main() {
    int n, k;
    printf("Enter the number of people: ");
    scanf("%d", &n);
    printf("Enter the counting interval (k): ");
    scanf("%d", &k);

    struct CircularQueue* queue = createQueue();

    for (int i = 1; i <= n; i++) {
        enqueue(queue, i);
    }

    int survivor = josephus(queue, k);
    printf("The last person standing is at position: %d\n", survivor);

    free(queue); // Free allocated memory

    return 0;
}
