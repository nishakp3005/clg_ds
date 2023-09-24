#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

struct Queue {
    int front, rear;
    unsigned size;
    char* array;
};

struct Queue* createQueue(unsigned size){
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
    queue->rear = queue->front = -1;
    queue->size = size;
    queue->array = (char*)malloc(size * sizeof(char));
}

int isFull(struct Queue * queue){
    if((queue->front == 0 && queue->rear == queue->size-1) || ((queue->rear+1) % queue->size == queue->front)) return 1;
    else return 0;
}

int isEmpty(struct Queue * queue){
    return (queue->size == 0);
}

int enqueue(struct Queue* queue, char item){
    if(isFull(queue))
        printf("queue full");
    else if(queue->front == -1){
        queue->front = queue->rear = 0;
        queue->array[queue->rear] = item;
    }
    else if(queue->rear == queue->size-1 && queue->front != 0){
        queue->rear = 0;
        queue->array[queue->rear] = item;
    }
    else{
        queue->rear++;
        queue->array[queue->rear] = item;
    }
    return 0;
}

void dequeue(struct Queue* queue){
    char c;
    if(isEmpty(queue)){
        printf("queue is empty");
    }
    c = queue->array[queue->front];
    queue->array[queue->front] = -1;
    if(queue->front == queue->rear){
        queue->front = -1;
        queue->rear = -1;
    }
    else if(queue->front = queue->size-1){
        queue->front = 0;
    }
    else {
        queue->front++;
    }
}

int display(struct Queue * queue){
    if (queue->front == -1)
    {
        printf("\nQueue is Empty");
        return 0;
    }
    printf("\nElements in Circular Queue are: ");
    if (queue->rear >= queue->front)
    {
        for (int i = queue->front; i <= queue->rear; i++)
            printf("%c ",queue->array[i]);
    }
    else
    {
        for (int i = queue->front; i < queue->size; i++)
            printf("%c ", queue->array[i]);
 
        for (int i = 0; i <= queue->rear; i++)
            printf("%c ", queue->array[i]);
    }
    return 0;
}

int front(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}

int rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}

int main(){
    int size, n, a = 1;
    char c, c1;
    printf("enter the size of the queue  : ");
    scanf("%d", &size);
    struct Queue* queue = createQueue(size);
    printf("enter\n1. display\n2. isFull\n3. isEmpty\n4. enqueue\n5. dequeue\n6. front\n7. rear\n0. Exit\n");
    while (a == 1){
        scanf("%d", &n);
            switch (n){
        case 1:
            display(queue);
            printf("\n");
            break;

        case 2:
            if(isFull(queue)) printf("queue is full");
            else printf("no queue is not full");
            printf("\n");
            break;

        case 3:
            if(isEmpty(queue)) printf("the queue is empty");
            else printf("the queue is not empty");
            printf("\n");
            break;

        case 4:
            printf("Enter the character u want to enqueue : ");
            scanf("%c", &c1);
            scanf("%c", &c);
            enqueue(queue, c);
            printf("\n");
            break;

        case 5:
            dequeue(queue);
            printf("\n");
            printf("front element dequeued");
            printf("\n");
            break;

        case 6:
            printf("the front element is : %c", front(queue));    
            printf("\n");
            break;

        case 7:
            printf("the rear element is : %c", rear(queue));
            printf("\n");
            break;

        case 0 :
            return 0;
        }
    }
    
    // dequeue(queue);
    // enqueue(queue, 'a');
    // enqueue(queue, 'b');
    // enqueue(queue, 'c');
    // enqueue(queue, 'd');
    // display(queue);
    return 0;
}