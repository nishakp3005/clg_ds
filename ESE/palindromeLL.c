#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack{
    int *arr;
    int top;
    int size;
} stack;

stack* init(int size){
    stack* s = (stack*)malloc(sizeof(stack));
    s->top = -1;
    s->arr = (int*)malloc(sizeof(int) * size);
    s->size = size;
    return s;
}

int isfull(stack* s){
    if(s->size-1 == s->top) return 1;
    return 0;
}

void push(stack* s, int element){
    if(isfull(s) == 1){
        printf("stack is full\n");
        return;
    }
    s->arr[++s->top] = element;
}

int isempty(stack* s){
    if(s->top == -1) return 1;
    return 0;
}

int pop(stack* s){
    int temp;
    if(isempty(s)){
        printf("stack is empty\n");
        return '\0';
    }
    else{
        temp = s->arr[s->top];
        s->top--;
    }
    return temp;
}

typedef struct Node{
    int data;
    struct Node* next;
} Node;

Node* create_node(int data){
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    return n;
}

void insert_node(Node* head, int data){
    Node* new_node = create_node(data);
    Node* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = new_node;
}

void display_node(Node* head){
    Node* temp = head;
    if(head == NULL){
        printf("empty node\n");
        return;
    }
    while(temp != NULL){
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

int isPalindrome(Node* head){
    printf("is palindrome begins\n");
    stack* s = init(10); 
    Node* temp = head;
    while(temp != NULL){
        push(s, temp->data);
        temp = temp->next;
    }   
    temp = head;
    while(temp != NULL){
        if(temp->data != pop(s)){
            printf("0");
            return 0;
        }
        temp = temp->next;
    }
    printf("1");
    return 1;
}   

int main(){
    Node* head = create_node(10);
    insert_node(head, 20);
    insert_node(head, 30);
    insert_node(head, 20);
    insert_node(head, 10);
    display_node(head);
    int ans = isPalindrome(head);
    printf("%d", ans);
    return 0;
}