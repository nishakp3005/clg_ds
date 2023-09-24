#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

void insert(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    if (head == NULL)
        head = newNode;
    else {
        newNode->next = head;
        head = newNode;
    }
}

struct Node* detectLoop() {
    if (head == NULL || head->next == NULL) {
        return NULL;
    }

    struct Node* slowPointer = head;
    struct Node* fastPointer = head;

    while (slowPointer != NULL && fastPointer != NULL && fastPointer->next != NULL) {
        slowPointer = slowPointer->next;
        fastPointer = fastPointer->next->next;
        if (slowPointer == fastPointer)
            break;
    }

    if (slowPointer != fastPointer)
        return NULL;

    slowPointer = head;
    while (slowPointer != fastPointer) {
        slowPointer = slowPointer->next;
        fastPointer = fastPointer->next;
    }

    return slowPointer;
}

int main() {
    // Inserting new values
    insert(10);
    insert(20);
    insert(30);
    insert(40);
    insert(50);

    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;
        
    temp->next = head;

    struct Node* loopStart = detectLoop();
    if (loopStart == NULL)
        printf("Loop does not exist\n");
    else {
        printf("Loop does exist and starts from %d\n", loopStart->data);
    }

    return 0;
}
