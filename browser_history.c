#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BrowserNode{
    char* url;
    // Pointer to the previous node
    struct BrowserNode* prev;  
    // Pointer to the next node
    struct BrowserNode* next;  
} BrowserNode;
    

typedef struct BrowserHistory{
    // Pointer to the current node
    BrowserNode* current;  
} BrowserHistory;

BrowserNode* createNode(char* url) {
    BrowserNode* newNode = (BrowserNode*)malloc(sizeof(BrowserNode));
    newNode->url = strdup(url);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// this creates a browser history
BrowserHistory* browserHistoryCreate(char * homepage) {
    BrowserHistory* history = (BrowserHistory*)malloc(sizeof(BrowserHistory));
    history->current = createNode(homepage);
    return history;
}


// this visits a URL
void browserHistoryVisit(BrowserHistory* obj, char * url) {
    while(obj->current->next != NULL){
        BrowserNode* temp = obj->current->next;
        obj->current->next = NULL;
        free(temp->url);
        free(temp);
    }
    BrowserNode* newNode = createNode(url);
    newNode->prev = obj->current;
    obj->current->next = newNode;
    obj->current = newNode;

}

// this moves back a number of 'steps' in history 
char * browserHistoryBack(BrowserHistory* obj, int steps) {
    while(steps>0 && obj->current->prev != NULL){
        obj->current = obj->current->prev;
        steps--;
        // printf("\n%d\n", steps);
    }
    return obj->current->url;
}

// this moves forward a number of 'steps' in history 
char * browserHistoryForward(BrowserHistory* obj, int steps) {
    while(steps>0 && obj->current->next != NULL){
        obj->current = obj->current->next;
        steps--;
        // printf("\n%d\n", steps);
    }
    return obj->current->url;
}

// // this cleans up the browser history and releases memory
void browserHistoryFree(BrowserHistory* obj) {
    while(obj->current->prev != NULL){
        BrowserNode* temp = obj->current;
        obj->current = obj->current->prev;
        free(temp->url);
        free(temp);
    }
    free(obj);
}

int main(){
    char* homepage = "google.com";
    BrowserHistory* h1 = browserHistoryCreate(homepage);
    browserHistoryVisit(h1, "linkedin.com");
    browserHistoryVisit(h1, "wikipedia.org");
    browserHistoryVisit(h1, "leetcode.com");
    browserHistoryVisit(h1, "meet.google.com");
    printf(browserHistoryBack(h1, 2));
    printf("\n");
    printf(h1->current->url);
    printf("\n");
    printf(browserHistoryForward(h1, 2));
    printf("\n");
    printf(h1->current->url);
    free(h1);
    printf("\n");
    printf(h1->current->url); // garbage value
}