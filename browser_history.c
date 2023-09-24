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


// this creates a browser history
BrowserHistory* browserHistoryCreate(char * homepage) {
    
}


// this visits a URL
void browserHistoryVisit(BrowserHistory* obj, char * url) {
  
}


// this moves back a number of 'steps' in history 
char * browserHistoryBack(BrowserHistory* obj, int steps) {
  
}

// this moves forward a number of 'steps' in history 
char * browserHistoryForward(BrowserHistory* obj, int steps) {
  
}

// this cleans up the browser history and releases memory
void browserHistoryFree(BrowserHistory* obj) {
    
}

/**
 * Your BrowserHistory struct will be instantiated and called as such:
 * BrowserHistory* obj = browserHistoryCreate(homepage);
 * browserHistoryVisit(obj, url);
 
 * char * param_2 = browserHistoryBack(obj, steps);
 
 * char * param_3 = browserHistoryForward(obj, steps);
 
 * browserHistoryFree(obj);
*/