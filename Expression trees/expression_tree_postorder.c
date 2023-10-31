#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack.c"

// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to perform an operation on 2 operands
float perform_operation(char op, float left, float right){
    switch (op) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            if (right != 0) {
                return left / right;
            } else {
                fprintf(stderr, "Error: Division by zero\n");
                exit(EXIT_FAILURE);
            }
        default:
            fprintf(stderr, "Error: Unknown operator %c\n", op);
            exit(EXIT_FAILURE);
    }
}

// TODO: To be completed
ExprTreeNode *create_node(OpType op_type, Data data){
    ExprTreeNode* node = (ExprTreeNode*) malloc(sizeof(ExprTreeNode));
    node->type = op_type;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// TODO: To be completed
// NOTE: Use the stack 'display' in this function to display stack state right after a given character in the expression has been processed.
// Do this for all characters of the expression string
ExprTreeNode *create_ET_from_postfix(char *postfix_expression){
    Stack* stack = initialize_stack(100);
    ExprTreeNode* root;
    int i = 0;
    while(postfix_expression[i] != '\0'){
        if(isOperator(postfix_expression[i])){
            Data data;
            data.operation = postfix_expression[i];
            ExprTreeNode* node = create_node(OPERATOR, data);
            node->right = pop(stack);
            node->left = pop(stack);
            push(stack, node);
            root = node;
        }
        else{
            Data num;
            num.operand = postfix_expression[i] - '0';
            ExprTreeNode* node = create_node(OPERAND, num);
            push(stack, node);
        }
        i++;
    }
    display(stack);
    return root;
}

// TODO: To be completed
float evaluate_ET(ExprTreeNode* root){
    if(root == NULL) exit(EXIT_FAILURE);
    if(root->type == OPERAND){
        return root->data.operand;
    }
    else{
        float left = evaluate_ET(root->left);
        float right = evaluate_ET(root->right);
        return perform_operation(root->data.operation, left, right);
    }
    return 0;
}

int main(){
    char* array = "6324+-*";
    ExprTreeNode* root = create_ET_from_postfix(array);
    printf("%c", root->data.operation);
    printf("\nfinal ans is : %f", evaluate_ET(root));
    return 0;
}