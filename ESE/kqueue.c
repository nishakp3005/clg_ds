#include<stdlib.h>
#include<stdio.h>
#include "queue.c"

typedef struct queues{
    int *front ;
    int *rear;
    unsigned total_queues;
    unsigned size_per_queue;
    struct Queue *array[50];
} queues;

struct queues *createNQueues(unsigned size, int n){
    queues *qs = (struct queues*)malloc(sizeof(struct queues));
    qs->total_queues = n;
    qs->size_per_queue = size;

    for(int i=0 ; i<n;i++){
        qs->array[i]=initialize_queue(size);
    }
    return qs;
}

void enqueueN(struct queues *q, int x, int qn){
    if(qn > q->total_queues-1 || qn < 0){
        printf("Invalid Queue number\n");
        return;
    }
    enqueue(q->array[qn],x);
}
int dequeueN(struct queues *q,int qn){
    if(qn > q->total_queues-1 || qn < 0){
        printf("Invalid Queue number\n");
        return -1;
    }
    int a ;
    a = dequeue(q->array[qn]);
    return a;
}
void displayq(struct queues *q,int qn){
    if(qn > q->total_queues-1 || qn < 0){
        printf("Invalid Queue number\n");
        return ;
    }
    display(q->array[qn]);
}
void display_all(struct queues *q){
    for(int i=0; i<q->total_queues; i++){
        int q_temp = i + 1;
        printf("Displaying Queue %d:\n", q_temp);
        display(q->array[i]);

    }
}
int main(){
    struct queues *Nq = createNQueues(10,2);
    enqueueN(Nq,3,0);
    enqueueN(Nq,2,0);
    enqueueN(Nq,11,0);
    enqueueN(Nq,41,0);
    enqueueN(Nq,25,0);
    enqueueN(Nq,3,1);
    enqueueN(Nq,2,1);
    enqueueN(Nq,11,1);
    enqueueN(Nq,41,1);
    enqueueN(Nq,25,1);
    displayq(Nq,0);
    dequeueN(Nq,0);
    printf("Display all queues:\n");
    display_all(Nq);
}