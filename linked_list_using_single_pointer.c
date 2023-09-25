// In this linked list implementation the head points to the node that stores the first element of the linked list

// Create a Linked List ADT using the Struct 'Node'. 
// The Linked List should support all operations that are listed as functions in this file

#include<string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data; 
    struct Node *next;
    } Node;


// create a LinkedList node with 'data'
Node* create_node(int dt){
    Node* new=(Node*)malloc(sizeof(Node));
    new->data=dt;
    new->next=NULL;
    return new;
}

// pos=-1 indicates insert at end
// pos=0 indicates add at beginning
// This creates a new LinkedList node and inserts it at position 'pos' in the current linked list originating from head
void insert_at_pos(Node *head, int pos, int data){
    if(head->next == NULL)
    {
        Node* temp=create_node(data);
        head->next=temp;
        // head->data=temp->data;
        // printf("in insert\n");
        //head=create_node(data);
    }
    else if(pos==0)
    {
        Node* temp=create_node(data);
        temp->next=head->next;
        head->next=temp;
    }
    else if(pos==-1)
    {
        Node* temp=create_node(data);
        Node* search=head->next;
        while(search->next != NULL)
            search=search->next;
        search->next=temp;
    }
    else
    {
        Node* temp=create_node(data);
        Node* search=head->next;
        Node* prev;
        for(int i=1;i<pos;i++)
        {
            prev=search;
            search=search->next;
            if(search==NULL)
            {
                printf("Position not found\n");
                return;
            }
        }
        prev->next=temp;
        temp->next=search;
    }
}

// pos=-1 indicates delete last node
// pos=0 indicates delete first node
// This deletes the LinkedList node at position 'pos' in the current linked list originating from head
void delete_at_pos(Node *head, int pos){
    if(head->next==NULL)
        printf("The linked list is empty.\n");
    else if(pos==0)
    {
        Node* temp=head->next;
        head->next=temp->next;
        temp->next=NULL;
    }
    else if(pos==-1)
    {
        Node* search=head;
        while(search->next->next != NULL)
            search=search->next;
        search->next=NULL;
    }
    else
    {
        Node* search=head->next;
        Node* prev;
        for(int i=1;i<pos;i++)
        {
            prev=search;
            search=search->next;
            if(search==NULL)
            {
                printf("Position not found\n");
                return;
            }
        }
        prev->next=search->next;
        search->next=NULL;
    }
}

// delete linkedlist node with first occurrence of given value from linked list originating from 'head'
void delete_by_value(Node *head, int value){
    Node* search=head->next;
    if(search->data == value)
    {
        head->next=search->next;
        search->next=NULL;
        return;
    }
    while(search->next->data != value)
    {
        search=search->next;
        if(search->next == NULL)
        {
            printf("Element not found\n");
            return;
        }
    }
    Node* temp=search->next;
    search->next=temp->next;
    temp->next=NULL;
}


// gets the node at position 'pos' in linkedlist originating from 'head'
// return 'NULL' if no node found along with informative message
Node* get_node_at_pos(Node *head, int pos){
    Node* search = head->next;
    for(int i=1;i<pos;i++)
    {
        if(search->next == NULL && i!=pos)
        {
            printf("Node not found");
            return NULL;
        }
        else
            search=search->next;
    }
    return search;
}

// Return the node with the first occurrence of value
// return 'NULL' if no node found along with informative message
Node* find_first(Node *head, int value){
    Node* search=head->next;
    while(search->data != value)
    {
        if(search->next == NULL)
        {
            printf("Node not found");
            return NULL;
        }
        else
            search=search->next;
    }
    return search;
}

// display entire linked list, starting from head, in a well-formatted way
void display(Node *head){
    Node* disp=head->next;
    while(disp->next != NULL)
    {
        printf("%d ",disp->data);
        disp=disp->next;
    }
    if(disp->next == NULL)
        printf("%d ",disp->data);
    printf("\n");
}


// deallocate the memory being used by the entire linkedlist, starting from head
void free_linkedlist(Node *head){
    Node* fr=head->next;
    while(fr->next != NULL)
    {
        free(fr);
        fr=fr->next;
    }
}

// reverse a linkedlist - reverse a given linked list
Node* reverse(Node *head){
    Node* search=head->next->next;
    Node* prev=head->next;
    prev->next=NULL;
    Node* temp;
    while(search->next != NULL)
    {
        temp=search->next;
        search->next=prev;
        prev=search;
        search=temp;
    }
    head->next=search;
    search->next=prev;
    return head;
}

int main()
{
    int choice;
    Node* head=(Node*)malloc(sizeof(Node));
    head->data=0;
    head->next=NULL;
    insert_at_pos(head,0,5);
    insert_at_pos(head,0,10);
    insert_at_pos(head,-1,15);
    insert_at_pos(head,-1,25);
    insert_at_pos(head,0,100);
    display(head);
    delete_by_value(head,35);
    display(head);
    Node* test=reverse(head);
    printf("\n%d ",test->data);
    delete_by_value(head,10);
    printf("%d ",head->data);
    display(test);
}
