#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BrowserNode {
    char* url;
    struct BrowserNode* prev;
    struct BrowserNode* next;
} BrowserNode;

typedef struct BrowserHistory {
    BrowserNode* current;
} BrowserHistory;

// Function to create a new BrowserNode
BrowserNode* createNode(char* url) {
    BrowserNode* newNode = (BrowserNode*)malloc(sizeof(BrowserNode));
    newNode->url = strdup(url);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to create a browser history with a given homepage
BrowserHistory* browserHistoryCreate(char* homepage) {
    BrowserHistory* history = (BrowserHistory*)malloc(sizeof(BrowserHistory));
    history->current = createNode(homepage);
    return history;
}

// Function to visit a URL and add it to the history
void browserHistoryVisit(BrowserHistory* obj, char* url) {
    // Remove all nodes after the current node (forward history)
    while (obj->current->next != NULL) {
        BrowserNode* temp = obj->current->next;
        obj->current->next = NULL;
        free(temp->url);
        free(temp);
    }

    // Create a new node for the visited URL
    BrowserNode* newNode = createNode(url);
    newNode->prev = obj->current;
    obj->current->next = newNode;
    obj->current = newNode;
}

// Function to move back a number of 'steps' in history
char* browserHistoryBack(BrowserHistory* obj, int steps) {
    while (steps > 0 && obj->current->prev != NULL) {
        obj->current = obj->current->prev;
        steps--;
    }
    return obj->current->url;
}

// Function to move forward a number of 'steps' in history
char* browserHistoryForward(BrowserHistory* obj, int steps) {
    while (steps > 0 && obj->current->next != NULL) {
        obj->current = obj->current->next;
        steps--;
    }
    return obj->current->url;
}

// Function to free the memory allocated for the browser history
void browserHistoryFree(BrowserHistory* obj) {
    while (obj->current != NULL) {
        BrowserNode* temp = obj->current;
        obj->current = obj->current->prev;
        free(temp->url);
        free(temp);
    }
    free(obj);
}

int main() {
    BrowserHistory* obj = browserHistoryCreate("https://www.example.com");
    browserHistoryVisit(obj, "https://www.google.com");
    browserHistoryVisit(obj, "https://www.wikipedia.org");

    printf("Current URL: %s\n", obj->current->url);
    printf("Back 1 step: %s\n", browserHistoryBack(obj, 1));
    printf("Forward 1 step: %s\n", browserHistoryForward(obj, 1));

    browserHistoryFree(obj);
    return 0;
}
