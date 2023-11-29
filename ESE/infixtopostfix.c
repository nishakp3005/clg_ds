#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct stack{
    char *arr;
    int top;
    int size;
} stack;

stack* init(int size){
    stack* s = (stack*)malloc(sizeof(stack));
    s->top = -1;
    s->arr = (char*)malloc(sizeof(char) * size);
    s->size = size;
    return s;
}

int isfull(stack* s){
    if(s->size-1 == s->arr[s->top]) return 1;
    return 0;
}

void push(stack* s, char element){
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

char pop(stack* s){
    char temp;
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

int isOperator(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/'){
        return 1;
    }
    return 0;
}

int precedence(char c){
    if(c == '+' || c == '-') return 1;
    else if(c == '*' || c == '/') return 2;
    else if(c == '^') return 3;
    return 0;
}

char* infixtopostfix(char infix[]){
    char* postfix = (char*)malloc(sizeof(char) * strlen(infix) + 1);
    int posind = 0;
    stack* s = init(10);
    for (int i = 0; i < strlen(infix); i++){
        if(isOperator(infix[i])){
            while(!isempty(s) && precedence(infix[i])<precedence(s->arr[s->top])){
                postfix[posind++] = pop(s);
            }
            push(s, infix[i]);
        }
        else if(infix[i] == '('){
            push(s, infix[i]);
        }
        else if(infix[i] == ')'){
            while(s->arr[s->top] != '('){
                postfix[posind++] = pop(s);
            }
            pop(s);
        }
        else{
            postfix[posind++] = infix[i];
        }
    }
    while(!isempty(s)){
        postfix[posind++] = pop(s);
    }
    return postfix;
}

int main(){
    char infix[10];
    printf("%s", infix);
    gets(infix);
    char* ans = infixtopostfix(infix);
    printf("%s",ans);
    return 0;
}