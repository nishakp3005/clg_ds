#include <stdio.h>
#include<stdlib.h>
struct stack{
    int top;
    int size;
    char* arr;
};

int isfull(struct stack* stk){
    if(stk->size-1==stk->top)
        return 1;
    else
        return 0;
}

int isempty(struct stack* stk){
    if(stk->top==-1)
        return 1;
    else
        return 0;
}

void push(struct stack* stk, char value){
    if(!isfull(stk)){
        stk->top++;
        stk->arr[stk->top]=value;
    }
    else{
        printf("STACK OVERFLOW\n");
    }
}
void pop(struct stack* stk){
    if(!isempty(stk)) {
        stk->top--;
        return;
    }
    else{
        printf("STACK IS UNDERFLOW:\n");
        return ;
    }
}

char peek(struct stack* stk){
    char a=stk->arr[stk->top];
    return a;
}

void display(struct stack* stk){
    if(stk->top==-1){
        printf("stack is empty:\n");
        return;
    }
    else{ 
        for(int i=0;i<peek(stk);i++){
            printf("%c",stk->arr[i]);}
            printf("\n\n");
        return;
    }
}

int main(){
    char c;
    struct stack* stk;
    struct stack* stk1;
    stk =(struct stack*)malloc(sizeof(struct stack));
    printf("Enter the size of stack\n");
    int sizeinpinput=0;
    scanf("%d",&sizeinpinput);
    getchar();
    stk->size=sizeinpinput;
    stk->arr=(char*)malloc(stk->size*sizeof(char));
    stk1->arr=(char*)malloc(5*sizeof(char));
    stk->top=-1;
    int flag=1;
    int option=-1;
    while(flag){
        printf("Enter 1 for push:\nEnter 2 for pop:\nEnter 3 for peek:\nEnter 4 to check is empty or not:\nEnter 5 reverse a string\nEnter 6 to display:\nEnter 0 to stop:\n");
        scanf("%d",&option);
        switch(option){
            case 0 : 
                flag = 0;
            break;
            
            case 1 :
                scanf("%c",&c);
                printf("Enter the element to push:\n");
                scanf("%c",&c);
                push(stk,c);
                printf("\n");
            break;

            case 2 :
                pop(stk);
                printf("\n");
            break;

            case 3 :
                printf("Element at the top of the stack is %s\n", peek(stk));
                printf("\n");
            break;

            case 4 :
                if(isempty(stk)){
                    printf("Stack is empty:\n");
                    printf("\n");
                }
                else{
                    printf("Stack is not empty:");
                    printf("\n");
                }
            break;

            case 5 :
                while(!isempty(stk)){
                    char reverse=peek(stk);
                    printf("%s ",&reverse);
                    pop(stk);
                }
                printf("\n");
            break;

            case 6 :
                display(stk);
            break;
        }
    }
    return 0;
}